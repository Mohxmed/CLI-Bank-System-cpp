#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"
#include "clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login() {
		bool LoginFailed = false;
		short FailedTimes = 1;
		string Username, Password;

		do {

			if (LoginFailed) {
				cout << "\n\t\t\t\t     [ Error ] Invalid Username or Password!\n";
				cout << "\n\t\t\t\t     [ Warning ] Login Attempts " << FailedTimes++ << "/3 \n";
				cout << "\t\t\t\t     ___________________________________________\n";
			}

			if (FailedTimes == 4) {
				cout << "\n\t\t\t\t     System Locked!";
				return false;
			}

			// Username
			cout << "\n\t\t\t\t     [ Input ] Enter Username  : ";
			cin >> Username;
			// Password
			cout << "\n\t\t\t\t     [ Input ] Enter Password  : ";
			cin >> Password;

			CurrentUser = clsUser::Find(Username, Password);
			LoginFailed = CurrentUser.IsEmpty();


		} while (LoginFailed);

		
		// Add Login to Register Logs File
		CurrentUser.RegisterLogin();

		// Invoke Main Manu After Login
		clsMainScreen::ShowMainMenu();



	}

public:
	static bool ShowLoginScreen() {
		system("cls");

		cout << "\n\t\t    ____              _       _____ _                 _       _   _             " << endl;
		cout << "\t\t   |  _ \\            | |     / ____(_)               | |     | | (_)            " << endl;
		cout << "\t\t   | |_) | __ _ _ __ | | __ | (___  _ _ __ ___  _   _| | __ _| |_ _  ___  _ __  " << endl;
		cout << "\t\t   |  _ < / _` | '_ \\| |/ /  \\___ \\| | '_ ` _ \\| | | | |/ _` | __| |/ _ \\| '_ \\ " << endl;
		cout << "\t\t   | |_) | (_| | | | |   <   ____) | | | | | | | |_| | | (_| | |_| | (_) | | | |" << endl;
		cout << "\t\t   |____/ \\__,_|_| |_|_|\\_\\ |_____/|_|_| |_| |_|\__,_|_|\__,_|\\__|_|\\___/|_| |_|\n" << endl;
		cout << "\t\t   Created By Mhmd Amr, Welcome!\n\n";

		_DrawScreenHeader("\t      Login Screen");
		return _Login();
	}
};

