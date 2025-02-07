#pragma once
#include <iomanip>
#include "clsInputValidate.h"

// Screens
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen
{
private:

    // Transactions Opt. Enum
    enum enTransactionsOptions {eDeposite = 1, eWithdraw = 2, eShowTotalBalance = 3, eTransfer = 4, eTransferLogs = 5, eShowMainMenu = 6};

    // Read Opt.
    static short ReadTransactionsOption() {
        cout << setw(37) << left << "" << "What's Next Step? [1 to 6] ? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number Between 1 to 6");
        return Choice;
    }

    // Show Deposit Screen
    static void _ShowDepositScreen() {
        clsDepositScreen::ShowDepositScreen();
    }

    // Show Withdraw Screen 
    static void _ShowWithdrawScreen() {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    // Show Total Balanaces Screen
    static void _ShowTotalBalancesScreen() {
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    // Show Transfer Screen
    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }

    // Show Transfer Logs Screen
    static void _ShowTransferLogsScreen() {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    // Back To Transactions Screen
    static void _GoBackToTransactionsMenu() {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsScreen();
    }


    // Preform Transactions Opt.
    static void _PreformTransactionsOptions(enTransactionsOptions Option) {
        switch (Option)
        {
        case clsTransactionsScreen::eDeposite:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case clsTransactionsScreen::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case clsTransactionsScreen::eShowTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenu();
            break;
        }

        case clsTransactionsScreen::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenu();
            break;

        case clsTransactionsScreen::eTransferLogs:
            system("cls");
            _ShowTransferLogsScreen();
            _GoBackToTransactionsMenu();
            break;


        case clsTransactionsScreen::eShowMainMenu:
            // Main Menu Screen Will Handle This!
            break;
        }

     
    }

public:
	static void ShowTransactionsScreen() {
        system("cls");

        if (!_CheckAccessPermissions(clsUser::enPermissions::pTransactions)) {
            return;
        }

        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n\n";
        cout << setw(37) << left << "" << "> [ 1 ] - Deposit                         |\n";
        cout << setw(37) << left << "" << "> [ 2 ] - Withdraw                        |\n";
        cout << setw(37) << left << "" << "> [ 3 ] - Total Balances                  |\n";
        cout << setw(37) << left << "" << "> [ 4 ] - Transfer Between                |\n";
        cout << setw(37) << left << "" << "> [ 5 ] - Transfer Logs                   |\n";
        cout << setw(37) << left << "" << "> [ 6 ] - Main Menu..                     |\n\n";
        cout << setw(37) << left << "" << "===========================================\n\n";

        _PreformTransactionsOptions((enTransactionsOptions)ReadTransactionsOption());

	}
};

