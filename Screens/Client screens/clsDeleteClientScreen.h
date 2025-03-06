#pragma once
#include<iostream>
#include"core/clsBankClient.h"
#include"lib/clsInputValidate.h"
using namespace std;
class clsDeleteClientScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient& client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirst Name   : " << client.FirstName();
		cout << "\nlast Name    : " << client.LastName();
		cout << "\nFullName     : " << client.FullName();
		cout << "\nEmail        : " << client.Email();
		cout << "\nPhone        : " << client.PhoneNumber();
		cout << "\nAcc. Number  : " << client.AccountNumber();
		cout << "\nPassword     : " << client.PinCode();
		cout << "\nBalance      : " << client.AccountBalance();
		cout << "\n___________________\n";

	}
public:
	static void DeleteClient()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}

		UpScreen("Delete Screen");

		cout << "Enter account number to delete : ";
		string accountNumber = "";
		accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExit(accountNumber))
		{
			cout << "Un exit client with account number [" << accountNumber << "] ,please try another one :";
			accountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(accountNumber);
		_PrintClient(client);

		string answer = "n";
		cout << "\n\nDo you want to delete this client ? : ";
		answer = clsInputValidate::ReadString();
		if (answer == "Y" || answer == "y")
		{
			if (client.Delete())
			{
				cout << "client has deleted succesfully :)\n";
				_PrintClient(client);
			}
			else
			{
				cout << "Erorr can,t delete client :(\n";
			}
		}

	}

};

