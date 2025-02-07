#pragma once
#include <iostream>
#include <iomanip>

// Classes
#include "clsBankClient.h"
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
private:
	static string OnScreenDate() {
		return clsDate::DateToString(clsDate::GetSystemDate());
	}
	static bool UserStatus() {
		if (CurrentUser.IsEmpty()) 
			return false;
		else 
			return true;
	}

protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {

		cout << setw(37) << left << "" << "___________________________________________\n\n";
		cout << setw(37) << left << "\t" << Title << "\n";
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle << "\n";
        }
		cout << setw(37) << left << "" << "___________________________________________\n";

		cout << "\n\t\t\t\t     User : ";
		if (UserStatus()) {
			cout << CurrentUser.Username << endl;
		}
		else {
			cout << "(Logged Out)" << endl;
		}
		cout << "\t\t\t\t     Date : " << OnScreenDate() << "\n\n";
    }

	static bool _CheckAccessPermissions(clsUser::enPermissions Permission) {
		if (!CurrentUser.CheckAccessPermissions(Permission)) {
			cout << "\t\t\t\t\t______________________________________";
			cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
			cout << "\n\t\t\t\t\t______________________________________\n\n";

			cout << "\t _   _       _____                    _         _              " << endl;
			cout << "\t| \\ | |     |  __ \\                  (_)       (_)            " << endl;
			cout << "\t|  \\| | ___ | |__) |__ _ __ _ __ ___  _ ___ ___ _  ___  _ __  " << endl;
			cout << "\t| . ` |/ _ \\|  ___/ _ \\ '__| '_ ` _ \\| / __/ __| |/ _ \\| '_ \\ " << endl;
			cout << "\t| |\\  | (_) | |  |  __/ |  | | | | | | \\__ \\__ \\ | (_) | | | |" << endl;
			cout << "\t|_| \\_|\\___/|_|   \\___|_|  |_| |_| |_|_|___/___/_|\\___/|_| |_|" << endl;

			return false;
		}
		else {
			return true;
		}
	}

	// Print Client Method
	static void PrintClient(clsBankClient Client)
	{
		cout << "\n\t\t\t\t     ___________________________________________\n";
		cout << "\n\t\t\t\t     Client Information Card ";
		cout << "\n\t\t\t\t     ___________________________________________\n";
		cout << "\n\t\t\t\t     [ @ ] Accout Number : " << Client.AccountNumber();
		cout << "\n\t\t\t\t     [ @ ] FirstName     : " << Client.FirstName;
		cout << "\n\t\t\t\t     [ @ ] LastName      : " << Client.LastName;
		cout << "\n\t\t\t\t     [ @ ] Full Name     : " << Client.FullName();
		cout << "\n\t\t\t\t     [ @ ] Email         : " << Client.Email;
		cout << "\n\t\t\t\t     [ @ ] Phone         : " << Client.Phone;
		cout << "\n\t\t\t\t     [ @ ] Password      : " << Client.PinCode;
		cout << "\n\t\t\t\t     [ @ ] Balance       : " << Client.AccountBalance;
		cout << "\n\t\t\t\t     ___________________________________________\n\n";

	}
	static void PrintClientBalance(clsBankClient Client)
	{
		cout << "\n\t\t\t\t     ___________________________________________\n";
		cout << "\n\t\t\t\t     Client Balance Card ";
		cout << "\n\t\t\t\t     ___________________________________________\n";
		cout << "\n\t\t\t\t     [ @ ] Accout Number : " << Client.AccountNumber();
		cout << "\n\t\t\t\t     [ @ ] Full Name     : " << Client.FullName();
		cout << "\n\t\t\t\t     [ @ ] Balance       : " << Client.AccountBalance;
		cout << "\n\t\t\t\t     ___________________________________________\n\n";

	}
};

