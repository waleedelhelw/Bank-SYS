#pragma once
#include<iostream>
#include"clsScreen.h"
#include"Global.h"

class clsCurrentUserScreen :protected clsScreen
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
	static void ShowCurrenUser()
	{
		UpScreen("\t  Current User ");
		_printUser(CurrentUser);
	}
};

