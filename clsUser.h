#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"

class clsUser : public clsPerson
{
private:
	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
	enMode _Mode;

	string _Username;
	string _Password;
	int _Permissions;
	bool _MarkForDelete = false;
	struct stLoginRegisterRecord;

	// Convert Log Register Line To Record
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;


		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2], 60);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;

	}

	// Convert File Line To User Object
	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#") {
		vector<string> LineData = clsString::Split(Line, Seperator);
		return clsUser(enMode::UpdateMode, LineData[0], LineData[1], LineData[2], LineData[3], LineData[4], clsUtil::DecryptText(LineData[5], 60), stoi(LineData[6]));
	}

	// Convert User Object To Line
	static string _ConvertUserObjectToLine(clsUser User, string Seperator="#//#") {
		string Line = "";
		Line += User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User.Username + Seperator;
		Line += clsUtil::EncryptText(User.Password, 60) + Seperator;
		Line += to_string(User.Permissions);
		//
		return Line;
	}

	// Load Users From File
	static vector<clsUser> _LoadUsersDataFromFile() {
		fstream MyFile;
		vector<clsUser> vUsers;
		MyFile.open("FileStorage/Users.txt", ios::in); // Read
		if (MyFile.is_open()) {
			string Line; 
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}

	// Save Users Data To File
	static void _SaveUsersDataToFile(vector<clsUser> vUsers) {
		fstream MyFile;
		MyFile.open("FileStorage/Users.txt", ios::out); // Overwrite

		if (MyFile.is_open()) {
			string DataLine;
			for (clsUser U : vUsers) {
				if (!U.MarkedForDelete()) {
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	// Update User
	void _Update() {
		vector<clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();
		// Loop for target
		for (clsUser& U : vUsers) {
			if (U.Username == Username) {
				U = *this;
				break;
			}
		}
		// Save After Edit
		_SaveUsersDataToFile(vUsers);
	}

	// Add New User
	void _AddNew() {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	// Add User Line To File
	void _AddDataLineToFile(string Line, string Seperator="#//#") {
		fstream MyFile;

		MyFile.open("FileStorage/Users.txt", ios::app | ios::out); // Append or Overwrite
		if (MyFile.is_open()) {
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	// Get Empty User Object
	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	// Create Log Register Line
	string _CreateLogRegisterLine(string Seperator="#//#") {
		string LogLine = "";

		LogLine += clsDate::GetSystemDateTimeString() + Seperator; 
		LogLine += Username + Seperator; 
		LogLine += clsUtil::EncryptText(Password, 60) + Seperator;
		LogLine += to_string(Permissions); 

		return LogLine;
	}

public:
	// Permissions
	enum enPermissions {eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, 
				pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegister = 128};

	// Login Register Structure
	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;

	};

	// contstructor
	clsUser(enMode Mode,string FirstName, string LastName, string Email, string Phone, 
		string Username, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	// Utils
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}
	bool MarkedForDelete() {
		return _MarkForDelete;
	}

	// Set Username
	void SetUsername(string Username) {
		_Username = Username;
	}
	// Get Username
	string GetUsername() {
		return _Username;
	}
	__declspec(property(get = GetUsername, put = SetUsername )) string Username;

	// Set Password
	void SetPassword(string Password) {
		_Password = Password;
	}
	// Get Password
	string GetPassword() {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	// Set Permessions
	void SetPermissions(int Permessions) {
		_Permissions = Permessions;
	}
	// Get Permessions
	int GetPermessions() {
		return _Permissions;
	}
	__declspec(property(get = GetPermessions, put = SetPermissions)) int Permissions;

	// Find User
	static clsUser Find(string Username) {
		fstream MyFile;

		MyFile.open("FileStorage/Users.txt", ios::in); // READ
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.Username == Username) {
					return User;
					break;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}
	static clsUser Find(string Username, string Password) {
		fstream MyFile;

		MyFile.open("FileStorage/Users.txt", ios::in); // READ
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if ((User.Username == Username) && (User.Password == Password)) {
					return User;
				}
			}
			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	// Save User
	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}

		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(_Username))
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
		}

	}

	// Is User Exist
	static bool IsUserExist(string UserName)
	{

		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	// Delete User
	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.Username == _Username)
			{
				U._MarkForDelete = true;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);

		*this = _GetEmptyUserObject();

		return true;

	}

	// Add New User Object
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	// Get Users List
	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	// Check Access Permissions
	bool CheckAccessPermissions(enPermissions Permission) {

		// Give All Permissions if ::eAll (-1) 
		if (this->Permissions == enPermissions::eAll)
			return true;

		// Bitwise Operatore (And) -> Check If Argument Permission is Included in User Permissions
		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	// Register Logins in Log File
	void RegisterLogin() {
		string LogLine = _CreateLogRegisterLine();

		fstream MyFile;
		MyFile.open("FileStorage/LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open()) {
			MyFile << LogLine << endl;
			MyFile.close();
		}
	}

	// Get Logs List
	static  vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("FileStorage/LoginRegister.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{

				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);

			}

			MyFile.close();

		}

		return vLoginRegisterRecord;

	}


};

