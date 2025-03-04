#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
using namespace std;
class clsDepositeScreen:protected clsScreen
{
private:

	/*static void _SetBalance(clsBankClient &client,float DepositeMoney)
	{
		client.SetAccountBalance(DepositeMoney + client.AccountBalance());
	}*/
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

	static void _printClientBalance(clsBankClient& client)
	{
		cout << "account balance of account number [" << client.AccountNumber() << "] has been " << client.AccountBalance();
	}
public:
	static void Deposite()
	{
		UpScreen("Deposite Screen ");
		string accountNumber = "";
		cout << "Enter account number to deposite: ";
		accountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExit(accountNumber))
		{
			cout << "Un exit client with account number [" << accountNumber << "], Try another one: ";
			accountNumber = clsInputValidate::ReadString();
		}


		clsBankClient client = clsBankClient::Find(accountNumber);
		_PrintClient(client);
		float DepositeMoney = 0;

		cout << "\nHow much you want to deposite : ";
		DepositeMoney = clsInputValidate::ReadFloatNumber();


		while (DepositeMoney <= 5)
		{
			cout << "you cant deposite liss than 5 dolar : ";
			DepositeMoney = clsInputValidate::ReadFloatNumber();

		}

		//clsBankClient::SetAccountBalance(DepositeMoney + clsBankClient::AccountBalance());
		cout << "Are you sure you want to deposite [" << DepositeMoney << "] : ";
		string answer="n";
		answer = clsInputValidate::ReadString();

		if (answer == "y" || answer == "Y")
		{
			//_SetBalance(client, DepositeMoney);
			client.Deposite(DepositeMoney);
			_printClientBalance(client);

			clsBankClient::enSaveResults saveData;
			saveData = client.Save();

			switch (saveData)
			{
			case clsBankClient::svFaildEmptyObject:
				cout << "\nSorry but data can,t save..!\n";
				break;
			case clsBankClient::svSucceeded:
				cout << "\nClient has saved succesfully.. \n";
				break;
			case clsBankClient::svFailedUsedAccount:
				cout << "\nSorry but data can,t ..! \n";

				break;
			default:
				break;
			}
		}
		
	}
	
};

