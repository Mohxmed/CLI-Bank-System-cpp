#pragma once

// Utils
#include <iostream>
#include "clsInputValidate.h"
#include "Global.h"

// Screens
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsLoginRegisterScreen.h"

// Sub Screens

// Transactions
#include "clsTransactionsScreen.h"

// Manage Users
#include "clsManageUsersScreen.h"

using namespace std;

class clsMainScreen :protected clsScreen
{


private:
    // Menu Opt. Enum
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eRegisterLogin = 8, eExit = 9
    };

    // Read Main Menu Opt. 1:8
    static short _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "What's Next Step? [1 to 9]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 9, "Enter Number between 1 to 8? ");
        return Choice;
    }

    // Back To Main Menu Method
    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";

        system("pause>0");
        ShowMainMenu();
    }

    // Client List Screen
    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();
    }

    // Add New Screen
    static void _ShowAddNewClientsScreen()
    {
        clsAddClientScreen::AddNewClient();
    }

    // Delete Screen
    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::DeleteClient();
    }

    // Update Screen
    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::UpdateClient();

    }

    // Find Screen
    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::FindClient();

    }

    // Sub. Transactions Screen
    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsScreen();
    }

    // Sub. Manage Screen
    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenu();

    }

    // Login Register Screen
    static void _ShowLoginRegisterScreen() {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    // End Screen
    static void _Logout()
    {
        cout << "\nYou Are About To Leave The System!\n";

        char answer = 'n';
        cout << "\nAre You Sure You Want to Logout? y/n? ";
        cin >> answer;

        CurrentUser = clsUser::Find("", "");

        if (tolower(answer) == 'y') {
            system("cls");
            cout << "-----------------------------------------\n";
            cout << "\nYou're Logged Out! Press Any Key To Login...";
            cout << "\n\n-----------------------------------------\n";
        }
        else {
            _GoBackToMainMenue();
        }

    }

    // Preform Main Menu Opt.
    static void _PerfromMainMenuOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eRegisterLogin:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _Logout();
            break;
        }

    }



public:

    static void ShowMainMenu()
    {
        system("cls");
        _DrawScreenHeader("\t      Main Screen");

        cout << setw(37) << left << "" << "===========================================\n\n";
        cout << setw(37) << left << "" << "> [ 1 ] - Show Client List                |\n";
        cout << setw(37) << left << "" << "> [ 2 ] - Add New Client                  |\n";
        cout << setw(37) << left << "" << "> [ 3 ] - Delete Client                   |\n";
        cout << setw(37) << left << "" << "> [ 4 ] - Update Client Info              |\n";
        cout << setw(37) << left << "" << "> [ 5 ] - Find Client                     |\n";
        cout << setw(37) << left << "" << "> [ 6 ] - Transactions Menu               |\n";
        cout << setw(37) << left << "" << "> [ 7 ] - Manage Users Menu               |\n";
        cout << setw(37) << left << "" << "> [ 8 ] - Login Registers                 |\n";
        cout << setw(37) << left << "" << "> [ 9 ] - Logout                          |\n\n";
        cout << setw(37) << left << "" << "===========================================\n\n";

        _PerfromMainMenuOption((enMainMenueOptions)_ReadMainMenuOption());
    }


};

