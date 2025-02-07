#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
{

public:
	static void ShowWithdrawScreen() {
		_DrawScreenHeader("\tWithdraw Screen");

		cout << "\n\t\t\t\t     [ Withdraw ] Enter Account Number : ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n\t\t\t\t     [ Error ] Account Number Not Found! : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		PrintClient(Client);

		double Amount = 0;
		cout << "\n\t\t\t\t     [ Input ] Enter Withdarw Amount : ";
		Amount = clsInputValidate::ReadDblNumber();

		char answer;
		cout << "\n\t\t\t\t     [ OK? ] Complete This Transaction? y/n? : ";
		cin >> answer;

		if (tolower(answer) == 'y') {

			double OldBalance = Client.AccountBalance;

			if (Client.Withdraw(Amount)) {
				cout << "\n\t\t\t\t     [#] Transaction Has Been Done Successfully!\n";
				PrintClient(Client);
			}
			else {
				cout << "\nError: Cannot Withdraw, Amout is More Than Balance! ";
			}
		}
		else {
			cout << "\nTransaction Failed, Try Again.\n";
		}
	}
};

