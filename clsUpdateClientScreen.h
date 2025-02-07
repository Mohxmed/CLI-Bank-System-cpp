#pragma once
#include "clsBankClient.h";
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"

class clsUpdateClientScreen : protected clsScreen
{
private:
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
    static void UpdateClient() {

        if (!_CheckAccessPermissions(clsUser::enPermissions::pUpdateClient)) {
            return;
        }


        string AccountNumber = "";

        _DrawScreenHeader("\tUpdate Client Screen");

        cout << "\n\t\t\t\t     [ Update ] Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\n\t\t\t\t     [ Error ] No Account Found! \n";
            cout << "\t\t\t\t     ___________________________________________\n\n";
            cout << "\t\t\t\t     [ Update ] Enter Account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        PrintClient(Client);

        cout << "\t\t\t\t     Update Information \n";
        cout << "\t\t\t\t     ___________________________________________\n";

        _ReadClientInfo(Client);

        cout << "\t\t\t\t     ___________________________________________\n\n";

        clsBankClient::enSaveResult SaveResult;
        SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::svSaveFailedEmptyObject:
            cout << "\n\t\t\t\t     Error, Cannot Save Empty Account!";
            break;
        case clsBankClient::svSaveSucceeded:
            cout << "\n\t\t\t\t     [#] Account Updated Successfully :-)\n";

            PrintClient(Client);

            break;
        }
    }


};

