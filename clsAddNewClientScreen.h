#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsUser.h"
using namespace std;
class clsAddNewClientScreen:protected clsScreen
{

private:
	static void _PrintClient(clsBankClient &client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirst Name   : " << client. FirstName();
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
	
	static void AddNewClient()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}

		UpScreen("Add New Client Screen");


		cout << "Enter a new account number : ";
		string accounNumber = "";
		accounNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExit(accounNumber))
		{
			cout << "You can,t use Account number >> [" << accounNumber << "]\n Try another one : ";
			accounNumber = clsInputValidate::ReadString();
		}

		clsBankClient newClient = clsBankClient::AddNewAccNumber(accounNumber);
		clsBankClient:: ReadClientInfo(newClient);
		clsBankClient::enSaveResults saveData;
		saveData = newClient.Save();

		switch (saveData)
		{
		case clsBankClient::svFaildEmptyObject:
			cout << "\nSorry but data can,t save because you enter an empety thing..!\n";
			break;
		case clsBankClient::svSucceeded:
			cout << "\nClient has saved succesfully.. \n";
			_PrintClient(newClient);
			break;
		case clsBankClient::svFailedUsedAccount:
			cout << "\nSorry but data can,t save because you want to use Account number is alredy used..! \n";

			break;
		default:
			break;
		}

		
		
	}
};

