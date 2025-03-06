#pragma once
#include<iostream>
#include"clsScreen.h"
#include"lib/clsInputValidate.h"
#include"core/clsBankClient.h"
using namespace std;
class clsWithdrawScreen:protected clsScreen
{
private:

	/*static void _SetBalance(clsBankClient& client, float WithdrawMoney)
	{
		client.SetAccountBalance(client.AccountBalance()- WithdrawMoney);
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
	static void Withdraw()
	{
		UpScreen("\tWithdraw Screen ");
		string accountNumber = "";
		cout << "Enter account number to withdraw: ";
		accountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExit(accountNumber))
		{
			cout << "Un exit client with account number [" << accountNumber << "], Try another one: ";
			accountNumber = clsInputValidate::ReadString();
		}


		clsBankClient client = clsBankClient::Find(accountNumber);
		_PrintClient(client);
		float WithdrawMoney = 0;

		cout << "\nHow much you want to withdraw : ";
		WithdrawMoney = clsInputValidate::ReadFloatNumber();


		while (WithdrawMoney <= 5 ||WithdrawMoney>client.AccountBalance())
		{
			cout << "you cant witdraw liss than 5 dolar or more than ["<<client.AccountBalance()<<"] : ";
			WithdrawMoney = clsInputValidate::ReadFloatNumber();

		}

		//clsBankClient::SetAccountBalance(DepositeMoney + clsBankClient::AccountBalance());
		cout << "Are you sure you want to withdraw [" << WithdrawMoney << "] : ";
		string answer = "n";
		answer = clsInputValidate::ReadString();

		if (answer == "y" || answer == "Y")
		{
			//_SetBalance(client, WithdrawMoney);
			client.Withdraw(WithdrawMoney);
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

