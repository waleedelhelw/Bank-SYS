#pragma once
#include<iostream>
#include"core/clsBankClient.h"
#include "core/clsUser.h"
#include"clsMainScreen.h"
class clsDeleteUserScreen:protected clsScreen
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

	static void ShowDleteUserScreen()
	{
		UpScreen("\tDelete User Screen");

		string username = "";
		cout << "Enter Username to delete: ";
		username = clsInputValidate::ReadString();


		while (!clsUser::IsUserExit(username))
		{
			cout << "Un exit client with username [" << username << "] ,please try another one :";
			username = clsInputValidate::ReadString();
		}


		clsUser user = clsUser::Find(username);
		_printUser(user);


		string answer;
		cout << "\nDo you want to delete this user from the system (Y/N)? ";
		answer = clsInputValidate::ReadString();  

		if (answer == "Y" || answer == "y")
		{
			if (user.Delete())
			{
				cout << "User has been deleted successfully.\n";
			}
			else
			{
				cout << "Failed to delete the user.\n";
			}
		}

	}

	
};

