#pragma once
#include <iostream>
#include <string>
using namespace std;

class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:
	// constructor
	clsPerson(string FirstName, string LastName, string Email, string Phone) {
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	// Set
	void setFirstName(string FirstName) {
		_FirstName = FirstName;
	}
	// Get
	string getFirstName() {
		return _FirstName;
	}

	__declspec(property(get = getFirstName, put = setFirstName)) string FirstName;

	// Set
	void setLastName(string LastName) {
		_LastName = LastName;
	}
	// Get
	string getLastName() {
		return _LastName;
	}

	__declspec(property(get = getLastName, put = setLastName)) string LastName;

	// Set
	void setEmail(string Email) {
		_Email = Email;
	}
	// Get
	string getEmail() {
		return _Email;
	}

	__declspec(property(get = getEmail, put = setEmail)) string Email;

	// Set
	void setPhone(string Phone) {
		_Phone = Phone;
	}
	// Get
	string getPhone() {
		return _Phone;
	}
	__declspec(property(get = getPhone, put = setPhone)) string Phone;

	string FullName() {
		return _FirstName + " " + _LastName;
	}
};

