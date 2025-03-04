#pragma once
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include"clsUser.h"
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"Global.h"
#include"clsMainScreen.h"
#include"clsLoginRegestir.h"
using namespace std;
class clsLoginScreen: protected clsScreen
{
private:
	 
	static bool _Login()
	{
		bool failedLogin = false;
		string username, password;
		short tryTiems = 0;
		do
		{
			
			if (failedLogin)
			{
				system("cls");
				cout << "Invlid Username or password, please try again\n\n";
				tryTiems++;
			}

			if (tryTiems >= 3)
			{
				cout << "You have been blocked after [" << tryTiems << "] tiems \n";
				return false;
			}
			cout << "\nYou have a [" << 3 - tryTiems << "] tiems to login ether you will blocked\n";
			cout << "Enter user name  : ";
			username = clsInputValidate::ReadString();
			cout << "\nEnter password : ";
			password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(username, password);
			failedLogin = CurrentUser.IsEmpty();

		} while (failedLogin&&tryTiems<3);
		
		//clsLoginRegestir::AddToLoginLoginFile();
		CurrentUser.UserRegester();
		clsMainScreen::ShowMainMenue();

	    return true;
	}
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		UpScreen("\t    Login Screen ");
		

		return _Login();
	}
};

