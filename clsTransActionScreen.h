#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsMainScreen.h"
#include"clsScreen.h"
#include"clsDepositeScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalance.h"
#include"clsTransferScreen.h"
#include"clsTransfersList.h"
class clsTransActionScreen: protected clsScreen 
{
private:
	enum _enTransActions{eWithdaw=1,eDeposite=2,eTotalBalance=3,eTransfer=4,
        etransferlist=5,eExit};

    static void _ShowDepositScreen()
    {
        //cout << "\n Deposit Screen will be here.\n";
        clsDepositeScreen::Deposite();
    }

    static void _ShowWithdrawScreen()
    {
        //cout << "\n Withdraw Screen will be here.\n";
        clsWithdrawScreen::Withdraw();
    }

    static void _ShowTotalBalancesScreen()
    {
        //cout << "\n Balances Screen will be here.\n";
        clsTotalBalance::ShowTotalBalance();

    }


    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferListScreen()
    { 
        clsTransfersList::TransferList();
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }

    static int ReadChoice()
    {
        int choice = 0;
        cout << "Choose between 1 to 6: ";
        choice = clsInputValidate::ReadIntNumberBetween(1, 6);
        return choice;
    }

    static void _PerformanceTransaction(_enTransActions choice)
    {
        switch (choice)
        {
        case clsTransActionScreen::eWithdaw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;


        case clsTransActionScreen::eDeposite:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;


        case clsTransActionScreen::eTotalBalance:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;

        case clsTransActionScreen::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;

        case clsTransActionScreen::etransferlist:
            system("cls");
            _ShowTransferListScreen();
            _GoBackToTransactionsMenue();
            break;

        case clsTransActionScreen::eExit:
           /* system("cls");    
            clsMainScreen::ShowMainMenue();*/
            break;

        default:
            break;
        }
    }

public:
	static void ShowTransactionsMenue()
	{

        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;
        }
        system("cls");
        UpScreen("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Withdraw.\n";

        cout << setw(37) << left << "" << "\t[2] Deposit.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer Money.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer List.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n"; 

        _PerformanceTransaction((_enTransActions)ReadChoice());
	}

};

