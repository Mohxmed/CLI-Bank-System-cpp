#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsString.h"
#include "clsPerson.h"
#include "clsDate.h"
#include "Global.h"

using namespace std;

// Inherits Person Class
class clsBankClient : public clsPerson
{
private:

	// Mode Enum
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	// Members
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	// Convert Transfer Record To Line
	string _ConvertTransferRecordToLine(float Amount, clsBankClient DestinationClient, string Username, string Seperator="#//#") {
		string DataLine = "";

		DataLine += clsDate::GetSystemDateTimeString() + Seperator;
		DataLine += AccountNumber() + Seperator;
		DataLine += DestinationClient.AccountNumber() + Seperator;
		DataLine += to_string(Amount) + Seperator;
		DataLine +=  to_string(AccountBalance) + Seperator;
		DataLine +=  to_string(DestinationClient.AccountBalance) + Seperator;
		DataLine += Username;

		return DataLine;
	}

	struct stTransferRecord;
	// Convert Line To Transfer Record
	static stTransferRecord _ConvertLineToTransferRecord(string Line, string Seperator = "#//#") {
		stTransferRecord Record;
		vector<string> vLine = clsString::Split(Line, Seperator);

		Record.DateTime = vLine[0];
		Record.SourceAccountNumber = vLine[1];
		Record.DestinationAccountNumber = vLine[2];
		Record.Amount = stof(vLine[3]);
		Record.srcBalanceAfter = stof(vLine[4]);
		Record.destBalanceAfter = stof(vLine[5]);
		Record.Username = vLine[6];

		return Record;
	}

	// Register Transfer Record Log
	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string Username) {
		string DataLine = _ConvertTransferRecordToLine(Amount, DestinationClient, Username);

		fstream MyFile;
		MyFile.open("FileStorage/TransferLogs.txt", ios::app | ios::out);

		if (MyFile.is_open()) {
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	// Convert Line To Object
	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator="#//#") {
		vector<string>vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stof(vClientData[6]));

	}

	// Convert Object To Line
	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator="#//#") {
		string DataLine ="";

		DataLine += Client.FirstName + Seperator;
		DataLine += Client.LastName + Seperator;
		DataLine += Client.Email + Seperator;
		DataLine += Client.Phone + Seperator;
		DataLine += Client.AccountNumber() + Seperator;
		DataLine += Client.PinCode+ Seperator;
		DataLine += to_string(Client.AccountBalance);

		return DataLine;
	}

	// Load Clients Data From File
	static vector<clsBankClient> _LoadClientsDataFromFile() {
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("FileStorage/Clients.txt", ios::in); // read

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return vClients;
	}

	// Save Clients Data To File
	static void _SaveClientsDataToFile(vector<clsBankClient> vClients) {
		fstream MyFile;
		MyFile.open("FileStorage/Clients.txt", ios::out); // Overwrite Mode
		string DataLine;

		if (MyFile.is_open()) {
			for (clsBankClient C : vClients) {
				if (C._MarkForDelete == false) {
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	// Update Client
	void _Update() {
		vector<clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}

	// Add New Client
	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	// Add Line To File
	void _AddDataLineToFile(string Line, string Seperator = "#//#") {
		fstream MyFile;
		MyFile.open("FileStorage/Clients.txt", ios::app | ios::out); // Append or Overwrite

		if (MyFile.is_open()) {
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	// Empty Client Object
	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}


public:
	// Transfer Records Structure
	struct stTransferRecord {
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string Username;
	};

	// constructor
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string AccountNumber, string PinCode, float AccountBalance) :
		// Pass To Person Constructor
		clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	// Empty?
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	// Read-only Acc. Number
	string AccountNumber() {
		return _AccountNumber;
	}

	// Set PinCode
	void setPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	// Get PinCode
	string getPinCode() {
		return _PinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	// Set Acc. Balance
	void setAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	// Get Acc. Balance
	float getAccountBalance() {
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	// Find By Account Number
	static clsBankClient Find(string AccountNumber) {
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("FileStorage/Clients.txt", ios::in); // read

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	// Find By Account Number & Pin Code
	static clsBankClient Find(string AccountNumber, string PinCode) {
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("FileStorage/Clients.txt", ios::in); // read

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	// Is Client Exist?
	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	// Get Add New Client
	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	// Delete Client
	bool Delete() {
		vector<clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient & C : vClients) {
			if (C.AccountNumber() == _AccountNumber) {
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();

		return true;
	}

	// Save Enum
	enum enSaveResult {svSaveFailedEmptyObject=0, svSaveSucceeded=1, svSaveFailedAccountNumberExist=2};

	// Update Based On Mode
	enSaveResult Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			{
				if (IsEmpty()) {
				return enSaveResult::svSaveFailedEmptyObject;
				}
			}
		
		case enMode::UpdateMode:
			{
			_Update();
			return enSaveResult::svSaveSucceeded;
			break;
			}

		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResult::svSaveFailedAccountNumberExist;
			}
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
			}
		}
		}
	}

	// Get Clients List
	static vector<clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	// Get Total Balances
	static double TotalBalances() {
		vector<clsBankClient> vClients = GetClientsList();

		double Total = 0;
		for (clsBankClient& C : vClients) {
			Total += C.AccountBalance;
		}
		return Total;
	}

	// Client Deposit
	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	// Client Withdraw
	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance) {
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	// Transfer
	bool Transfer(float Amount, clsBankClient& DestinationClient) {
		if (Amount > AccountBalance) {
			return false;
		}
		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, CurrentUser.Username);
		return true;
	}

	// Get Transfer Log List
	static vector <stTransferRecord> GetTransferLogList() {
		vector <stTransferRecord> vTranferRecords;

		fstream MyFile;
		MyFile.open("FileStorage/TransferLogs.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			stTransferRecord Record;
			while (getline(MyFile, Line)) {
				Record = _ConvertLineToTransferRecord(Line);
				vTranferRecords.push_back(Record);
			}
			MyFile.close();
			return vTranferRecords;
		}

	}
};

