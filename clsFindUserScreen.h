#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen :protected clsScreen
{

private:
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
public:

    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t  Find User Screen");

        string UserName;
        cout << "\n\t\t\t\t     [ Find ] Enter Username : ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\n\t\t\t\t     [ Error ] User is NOT Found! : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\n\t\t\t\t     [#] User Found !\n";
        }
        else
        {
            cout << "\n\t\t\t\t     [ Error ] User Is Not Found! \n";
        }

        _PrintUser(User1);

    }

};

