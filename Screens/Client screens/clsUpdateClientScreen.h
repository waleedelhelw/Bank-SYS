#pragma once
#include<iostream>
#include"core/clsBankClient.h"
#include"lib/clsInputValidate.h"
using namespace std;
class clsUpdateClientScreen :protected clsScreen
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

	static void UpdateClient()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;
		}
		UpScreen("Update Client Screen");

		string AccounNumber;
		cout << "Please enter Client Account Number : ";
		AccounNumber = clsInputValidate::ReadString();
		// ===========================================================
		while (!clsBankClient::IsClientExit(AccounNumber))
		{
			cout << "Cant find client with Accoun Number [" << AccounNumber << "]\n";
			cout << "Try another one : ";
			AccounNumber = clsInputValidate::ReadString();
		}
		// ===========================================================


		clsBankClient client = clsBankClient::Find(AccounNumber);
		_PrintClient(client);

		cout << "-------------\n";
		cout << " Update Data\n";
		cout << "-------------\n";

		clsBankClient::ReadClientInfo(client);

		clsBankClient::enSaveResults saveData;
		saveData = client.Save();


		switch (saveData)
		{
		case clsBankClient::svFaildEmptyObject:
			cout << "Fail to save data because you entered empty data.. !\n";
			break;
		case clsBankClient::svSucceeded:
			cout << "Data has saved succesfully . \n";

			break;
		default:
			break;
		}


	} //

};

