#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"

class clsDepositScreen : protected clsScreen
{

public:
	static void ShowDepositScreen() {
		_DrawScreenHeader("\tDeposit Screen");

		cout << "\n\t\t\t\t     [ Deposit ]  Enter Account Number : ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n\t\t\t\t     [ Error ] Account Number Not Found! : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		PrintClient(Client);

		double Amount = 0;
		cout << "\n\t\t\t\t     [ Input ] Enter Deposit Amount : ";
		Amount = clsInputValidate::ReadDblNumber();

		char answer;
		cout << "\n\t\t\t\t     [ OK? ] Complete This Transaction? y/n? :";
		cin >> answer;

		if (tolower(answer) == 'y') {
			cout << "\n\t\t\t\t     [#] Transaction Has Been Done Successfully!\n";

			Client.Deposit(Amount);

			PrintClient(Client);
		}
		else {
			cout << "\n\t\t\t\t     [ Error ] Transaction Failed, Try Again.\n";
		}
	}
};

