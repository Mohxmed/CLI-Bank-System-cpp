#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"


class clsTransferScreen : protected clsScreen
{
private:
	static string _ReadAccountNumber() {
		string AccountNumber;

		cout << "\n\t\t\t\t     [ Input ] Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while(!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n\t\t\t\t     [ Error ] Client Not Found!";
			cout << "\n\t\t\t\t     [ Input ] Enter Another Account Number : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}
	static float _ReadTransferAmount(clsBankClient SourceClient) {
		float Amount;
		
		cout << "\n\t\t\t\t     [ Transfer ] Enter Amount : ";
		Amount = clsInputValidate::ReadFloatNumber();

		while (Amount > SourceClient.AccountBalance) {
			cout << "\n\t\t\t\t     [ Error ] Amount Exceeds the available Balance";
			cout << "\n\t\t\t\t     [ Transfer ] Enter Less Amount : ";
			Amount = clsInputValidate::ReadFloatNumber();
		}

		return Amount;
	}

public:
	static void ShowTransferScreen() {
		_DrawScreenHeader("\t    Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		PrintClientBalance(SourceClient);

		float Amount = _ReadTransferAmount(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

		char Answer;
		cout << "\n\t\t\t\t     [ OK? ] Sure To Apply? y/n? ";
		cin >> Answer;


		if (tolower(Answer) == 'y') {
			if (SourceClient.Transfer(Amount, DestinationClient)) {
				cout << "\n\t\t\t\t     [#] Transfer Done Successfully!";
			}
			else {
				cout << "\n\t\t\t\t     [ Error ] Transfer Failed";
			}
		}

		PrintClientBalance(SourceClient);
		PrintClientBalance(DestinationClient);
	}
};

