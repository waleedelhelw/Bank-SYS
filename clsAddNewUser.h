#pragma once
#include<iostream>
#include"clsBankClient.h"
#include "clsUser.h"
#include"clsMainScreen.h"
using namespace std; 
class clsAddNewUser :protected clsScreen
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
	static void ShowAddNewUserScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}

		UpScreen("Add New Client Screen");

		cout << "Enter a new Username: ";
		string username = "";
		username = clsInputValidate::ReadString();
		while (clsUser::IsUserExit(username))
		{
			cout << "You can,t use Username >> [" << username << "]\n Try another one : ";
			username = clsInputValidate::ReadString();
		}

		clsUser newUser= clsUser::AddNewUser(username);
		clsUser::ReadUsernfo(newUser);
		clsUser::enSaveResults saveData;
		saveData = newUser.Save();

		switch (saveData)
		{
		case clsUser::svFaildEmptyObject:
			cout << "\nSorry but data can,t save because you enter an empety thing..!\n";
			break;
		case clsUser::svSucceeded:
			cout << "\nClient has saved succesfully.. \n";
			//_PrintClient(newClient);
			_printUser(newUser);
			break;
		case clsUser::svFailedUsedAccount:
			cout << "\nSorry but data can,t save because you want to use Account number is alredy used..! \n";

			break;
		default:
			break;
		}



	}
	
};

