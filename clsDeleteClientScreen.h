#pragma once
#include <string>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"

class clsDeleteClientScreen : protected clsScreen
{
public:
	static void DeleteClient() {

        if (!_CheckAccessPermissions(clsUser::enPermissions::pDeleteClient)) {
            return;
        }

        string AccountNumber = "";

        _DrawScreenHeader("\tDelete Client Screen");

        cout << "\t\t\t\t     [ Delete ] Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        if (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\n\t\t\t\t     [ Error ] No Account Found! \n";
            cout << "\t\t\t\t     ___________________________________________\n\n";
            cout << "\t\t\t\t     [ Delete ] Enter Account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        PrintClient(Client);

        char answer = 'n';
        cout << "\n\t\t\t\t     Are You Sure You Want to Delete? y/n? : ";
        cin >> answer;

        if (tolower(answer) == 'y') {
            if (Client.Delete()) {
                cout << "\n\n\t\t\t\t     [#] Client Deleted Successfully!";
                PrintClient(Client);
            }
            else {
                return;
            }
        }

    }
};

