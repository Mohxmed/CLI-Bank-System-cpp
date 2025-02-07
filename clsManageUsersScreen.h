#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

// Screens
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:

	// Manage Users Menu Opt.
	enum enManageUsersOptions {eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenu = 6};

	// Read Menu Opt.
	static short ReadManageUsersMenuOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number Between 1 to 6");
		return Choice;
	}

    // List Users Screen
    static void _ShowListUsersScreen() {
        clsListUsersScreen::ShowUsersList();
    }

    // Add New User Screen
    static void _ShowAddNewUserScreen() {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    // Delete User Screen
    static void _ShowDeleteUserScreen() {
        clsDeleteUserScreen::ShowDeleteUserScreen();

    }

    // Update User Screen
    static void _ShowUpdateUserScreen() {
        clsUpdateUserScreen::ShowUpdateUserScreen();

    }

    // Find User Screen
    static void _ShowFindUserScreen() {
        clsFindUserScreen::ShowFindUserScreen();

    }

    // Back To Manage Users Menu Screen
    static void _BackToManageUsersMenu() {
        cout << "\n\nPress any key to go back to Manage Users Menu...";
        system("pause>0");
        ShowManageUsersMenu();
    }

    // Perform Manage Users Opt.
    static void _PerformManageUsersMenueOption(enManageUsersOptions Option)
    {
        switch (Option)
        {
        case clsManageUsersScreen::eListUsers:
        {
            system("cls");
            _ShowListUsersScreen();
            _BackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _BackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            _BackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _BackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eFindUser:
        {
            system("cls");
            _ShowFindUserScreen();
            _BackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eMainMenu:
        {
            // Main Menu Screen Will Handle This
            break;
        }
        }
    }

public:
    static void ShowManageUsersMenu()
    {

        if (!_CheckAccessPermissions(clsUser::enPermissions::pManageUsers)) {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n\n";
        cout << setw(37) << left << "" << "> [ 1 ] - List Users                      |\n";
        cout << setw(37) << left << "" << "> [ 2 ] - Add New User                    |\n";
        cout << setw(37) << left << "" << "> [ 3 ] - Delete User                     |\n";
        cout << setw(37) << left << "" << "> [ 4 ] - Update User                     |\n";
        cout << setw(37) << left << "" << "> [ 5 ] - Find User                       |\n";
        cout << setw(37) << left << "" << "> [ 6 ] - Main Menu..                     |\n\n";
        cout << setw(37) << left << "" << "===========================================\n\n";


        _PerformManageUsersMenueOption((enManageUsersOptions)ReadManageUsersMenuOption());
    }
};

