#pragma once

#include <iostream>
#include <iomanip>

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
private:
    // Read User
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\n\t\t\t\t     [ Input ] Enter First Name : ";
        User.FirstName = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Input ] Enter Last Name : ";
        User.LastName = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Input ] Enter Email : ";
        User.Email = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Input ] Enter Phone : ";
        User.Phone = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Input ] Enter Password : ";
        User.Password = clsInputValidate::ReadString();
        cout << "\n\t\t\t\t     [ Multi ] Select Permissions : ";
        User.Permissions = _ReadPermissionsToSet();
    }

    // Print User
    static void _PrintUser(clsUser User)
    {
        cout << "\n\t\t\t\t     ___________________________________________\n";
        cout << "\n\t\t\t\t     User Information Card ";
        cout << "\n\t\t\t\t     ___________________________________________\n";
        cout << "\n\t\t\t\t     [ @ ] Username      : " << User.Username;
        cout << "\n\t\t\t\t     [ @ ] FirstName     : " << User.FirstName;
        cout << "\n\t\t\t\t     [ @ ] LastName      : " << User.LastName;
        cout << "\n\t\t\t\t     [ @ ] Full Name     : " << User.FullName();
        cout << "\n\t\t\t\t     [ @ ] Email         : " << User.Email;
        cout << "\n\t\t\t\t     [ @ ] Phone         : " << User.Phone;
        cout << "\n\t\t\t\t     [ @ ] Password      : " << User.Password;
        cout << "\n\t\t\t\t     [ @ ] Permissions   : " << User.Permissions;
        cout << "\n\t\t\t\t     ___________________________________________\n\n";


    }

    // Read Permissions
    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\n\t\t\t\t     [ OK? ] Full Access Permissions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\n\t\t\t\t     [ OK? ] Do you want to give access to : \n ";

        cout << "\n\t\t\t\t     [ OK? ] Show Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\n\t\t\t\t     [ OK? ] Add New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\n\t\t\t\t     [ OK? ] Delete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\n\t\t\t\t     [ OK? ] Update Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClient;
        }

        cout << "\n\t\t\t\t     [ OK? ] Find Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\n\t\t\t\t     [ OK? ] Transactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTransactions;
        }

        cout << "\n\t\t\t\t     [ OK? ] Manage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\n\t\t\t\t     [ OK? ] Login Registers? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        return Permissions;

    }

public:
    // Show Screen
    static void ShowAddNewUserScreen()
    {

        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cout << "\n\t\t\t\t     [ New ] Enter Useruame : ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\n\t\t\t\t     [ Error ] This Username is Used! : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);
        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();
        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\n\t\t\t\t     [#] User Addeded Successfully! \n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\n\t\t\t\t     [ Error ] Empty User Data!";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\n\t\t\t\t     [ Error ] Username is Already in Use! \n";
            break;

        }
        }
    }
};

