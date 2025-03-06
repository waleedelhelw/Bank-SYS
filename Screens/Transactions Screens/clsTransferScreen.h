#pragma once
#include<iostream>
#include"clsScreen.h"
#include"lib/clsInputValidate.h"
#include"core/clsBankClient.h"
using namespace std; 
class clsTransferScreen:protected clsScreen
{
private:
	static void _PrintClient(clsBankClient& client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		//cout << "\nFirst Name   : " << client.FirstName();
		//cout << "\nlast Name    : " << client.LastName();
		cout << "\nFullName     : " << client.FullName();
		//cout << "\nEmail        : " << client.Email();
		//cout << "\nPhone        : " << client.PhoneNumber();
		cout << "\nAcc. Number  : " << client.AccountNumber();
		//cout << "\nPassword     : " << client.PinCode();
		cout << "\nBalance      : " << client.AccountBalance();
		cout << "\n___________________\n";

	}

	//static bool CanOperationDone(clsBankClient& FromClient,clsBankClient &TOclient,float amount)
	//{
	//	if (amount >= 5 && amount <= FromClient.AccountBalance())
	//	{
	//		return true;
	//	}
	//	return false;
	//}

	static clsBankClient _ReadFromClient()
	{
		string AccountNumber = "";
		cout << "Enter an account number to transfer money from: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExit(AccountNumber))
		{
			cout << "Can,t find account number[" << AccountNumber << "] in system, " <<
				"enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient fromClient = clsBankClient::Find(AccountNumber);
		cout << "\n----------------\n";
		_PrintClient(fromClient);
		cout << "----------------\n";

		return fromClient;
	}


	static clsBankClient _ReadToClient()
	{
		string AccountNumber = "";
		cout << "Enter an account number to transfer money To: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExit(AccountNumber))
		{
			cout << "Can,t find account number[" << AccountNumber << "] in system, " <<
				"enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient TOclient = clsBankClient::Find(AccountNumber);

		cout << "\n----------------\n";
		_PrintClient(TOclient);
		cout << "----------------\n";

		return TOclient;
	}


public:
	static void ShowTransferScreen()
	{

		float amount = 0;
		UpScreen("\t Transfer Screen");

		clsBankClient fromClient = _ReadFromClient();
		clsBankClient TOclient = _ReadToClient();
		
		
	cout << "Enter the amount to transfer: ";
		amount = clsInputValidate::ReadFloatNumber();


		while (!fromClient.Trasfer(amount,TOclient))
		{
			cout << "this operation can,t done , enter another amount: ";
			amount = clsInputValidate::ReadFloatNumber();
		}

		


		cout << "Are you sure you want to transfer [" << amount << "] : ";
		string answer = "n";
		answer = clsInputValidate::ReadString();

		if (answer == "y" || answer == "Y")
		{
			////_SetBalance(client, DepositeMoney);
			//fromClient.Withdraw(amount);
			//TOclient.Deposite(amount);


			clsBankClient::enSaveResults saveFromClient = fromClient.Save();
			clsBankClient::enSaveResults saveToClient = TOclient.Save();

			if (saveFromClient == clsBankClient::svSucceeded && saveToClient == clsBankClient::svSucceeded)
			{
				cout << "\n✅ Transaction completed successfully. The new balances are:\n";
				_PrintClient(fromClient);
				_PrintClient(TOclient);

			}
			else
			{
				cout << "\n❌ Transaction failed! Reasons:\n";

				if (saveFromClient != clsBankClient::svSucceeded)
				{
					cout << "- Failed to save sender's account data.\n";
				}
				if (saveToClient != clsBankClient::svSucceeded)
				{
					cout << "- Failed to save receiver's account data.\n";
				}
			}

		}

	}

	

};

