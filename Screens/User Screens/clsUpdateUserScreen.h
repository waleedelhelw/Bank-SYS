#pragma once
#include<iostream>
#include"core/clsBankClient.h"
#include "core/clsUser.h"
#include"clsMainScreen.h"
using namespace std;
class clsUpdateUserScreen:protected clsPerson
{
private:
    static void _printUser(clsUser &user)
    {
        cout << "First name : " << user.FirstName()<<endl;
        cout << "Last name  : " << user.LastName() << endl;
        cout << "Username   : " << user.UserName() << endl;
        cout << "Email      : " << user.Email() << endl;
        cout << "Phone      : " << user.PhoneNumber() << endl;
        cout << "permessions: " << user.Permissions() << endl;

    }

public:
    static void ShowUpdateUserScreen()
    {
        clsScreen::UpScreen("\t\tUpdate user screen");

        cout << "Enter username to Update: ";
        string username = "";
        username = clsInputValidate::ReadString();
        while (!clsUser::IsUserExit(username))
        {
            cout << "Un exit username try another one: ";
            username = clsInputValidate::ReadString();
        }

        cout << "\n\n----------------------\n\n";


        clsUser user = clsUser::Find(username);
        _printUser(user);
        cout << "-------------\n";
        cout << " Update Data\n";
        cout << "-------------\n";

        cout << "\n----------------------\n";
        user.Update();
        cout << "\n----------------------\n\n";

        clsUser::enSaveResults saveData;
        saveData = user.Save();


        switch (saveData)
        {
        case clsUser::svFaildEmptyObject:
            cout << "Fail to save data because you entered empty data.. !\n";
            break;
        case clsUser::svSucceeded:
            cout << "Data has saved succesfully . \n";
            _printUser(user);
            break;
        default:
            break;
        }

    }
    
};

