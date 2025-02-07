#pragma once
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"

class clsFindClientScreen : protected clsScreen
{
public:
	static void FindClient() {

		if (!_CheckAccessPermissions(clsUser::enPermissions::pFindClient)) {
			return;
		}

		string AccountNumber = "";

		_DrawScreenHeader("\t    Find Client Screen");

		cout << "\t\t\t\t     [ Find ] Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		if (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\t\t\t\t     [#] No Client With [" << AccountNumber << "] Found!";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		PrintClient(Client);
	}
};

