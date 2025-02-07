#pragma once
#include <iostream>
#include <string>

#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsUser.h"

class clsAddClientScreen : protected clsScreen
{
private:
    // Read Client
    static void _ReadClientInfo(clsBankClient& Client) {
        cout << "\n\t\t\t\t     [ Input ] Enter First Name : ";
        Client.FirstName = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Input ] Enter Last Name : ";
        Client.LastName = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Input ] Enter Email : ";
        Client.Email = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Input ] Enter Phone Number : ";
        Client.Phone = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Input ] Enter Pin Code : ";
        Client.PinCode = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Input ] Enter Account Balance : ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

public:
    static void AddNewClient() {
        // Check Permissions
        if (!_CheckAccessPermissions(clsUser::enPermissions::pAddNewClient)) {
            return;
        }
        _DrawScreenHeader("\tAdd New Client Screen");

        // Add New Client
        string AccountNumber = "";
        cout << "\t\t\t\t     [ Input ] Enter New Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\n\t\t\t\t     [ Error ] Account Number Is Already Used!\n";
            cout << "\t\t\t\t     ___________________________________________\n\n";
            cout << "\t\t\t\t     [ Input ] Enter New Account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        cout << "\n\t\t\t\t     ___________________________________________\n";
        cout << "\n\t\t\t\t     Client Information \n";
        cout << "\t\t\t\t     ___________________________________________\n\n";

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResult SaveResult;
        SaveResult = NewClient.Save();
        cout << "\n\t\t\t\t     [#] Client Added Successfully!";
        PrintClient(NewClient);
    }

};

