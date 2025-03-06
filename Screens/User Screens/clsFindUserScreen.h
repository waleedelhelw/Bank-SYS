#pragma once
#include<iostream>
#include"core/clsBankClient.h"
#include "core/clsUser.h"
#include"clsMainScreen.h"
using namespace std;
class clsFindUserScreen:protected clsScreen
{
private:
    static void _printUser(clsUser& user)
    {
        cout << "\n==================================\n";
        cout << "First name : " << user.FirstName() << endl;
        cout << "Last name  : " << user.LastName() << endl;
        cout << "Username   : " << user.UserName() << endl;
        cout << "Email      : " << user.Email() << endl;
        cout << "Phone      : " << user.PhoneNumber() << endl;
        cout << "permessions: " << user.Permissions() << endl;
        cout << "==================================\n";


    }

public:
    static void FindUserScreen()
    {
        clsScreen::UpScreen("\tSearch for User");

        string username = "";
        cout << "\nEnter username to search: ";
        username = clsInputValidate::ReadString();


        while (!clsUser::IsUserExit(username))
        {
            cout << "Un exist username [" << username << "], try anoter one: ";
            username = clsInputValidate::ReadString();
        }

        clsUser user = clsUser::Find(username);

        _printUser(user);

    }
};

