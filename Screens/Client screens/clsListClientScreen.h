#pragma once
#include<iostream>
#include"core/clsBankClient.h"
#include"clsMainScreen.h"
using namespace std;
class clsListClientScreen:protected clsScreen
{
public:
	static void ShowListLlient()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pListClients))
		{
			return;
		}
		UpScreen("\tUser List Screen");

		vector<clsBankClient>vClients;
		vClients = clsBankClient::ListClient();

		cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(25) << "Email";
		cout << "| " << left << setw(10) << "Pin code";
		cout << "| " << left << setw(12) << "Account balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else
		{
			for (clsBankClient Client : vClients)
			{
				clsBankClient::PrintClientRecordLine(Client);
				cout << endl;
			}
		}


	}

};

