#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen
{

private:
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

public:
    static void ShowDeleteUserScreen()
    {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\n\t\t\t\t     [ Delete ] Enter Username : ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\n\t\t\t\t     [ Error ] User is NOT Found! : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        cout << "\n\t\t\t\t     [ OK? ] Delete This User? y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            if (User1.Delete())
            {
                cout << "\n\t\t\t\t     [#] User Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\n\t\t\t\t     [ Error ] Deleted Failed! \n";
            }
        }
    }

};

