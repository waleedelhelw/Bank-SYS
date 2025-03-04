#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"clsStrings.h"
#include"clsPerson.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsListClientScreen.h"
#include"clsAddNewClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsTransActionScreen.h"
#include"clsManageUsersScreen.h"
#include"Global.h"
#include"clsLoginRegisterScreen.h"
#include"clsCurrencyMainScreen.h"
using namespace std;
class clsMainScreen :protected clsScreen
{
private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRegisterScreen = 8 ,eCurrencyMenuScreen=9,eExit = 10
    };

    static int _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        int Choice = clsInputValidate::ReadIntNumberBetween(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }



    static void _PerfromMainMenueOption(enMainMenueOptions choice)
    {
        switch (choice)
        {
        case clsMainScreen::eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;

        case clsMainScreen::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case clsMainScreen::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case clsMainScreen::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case clsMainScreen::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case clsMainScreen::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case clsMainScreen::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case clsMainScreen::eLoginRegisterScreen:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;

        case clsMainScreen::eCurrencyMenuScreen:
            system("cls");
            _ShowCurrencyMenuScreen();
            _GoBackToMainMenue();
            break;

        case clsMainScreen::eExit:
            system("cls");
            _Logout();
            break;
        default:
            break;
        }
    }

    static void _ShowLoginRegisterScreen()
    {
       // cout << "show current user\n";
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {

        clsListClientScreen::ShowListLlient();

    }

    static void _ShowAddNewClientsScreen()
    {

        clsAddNewClientScreen::AddNewClient();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::DeleteClient();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::UpdateClient();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();

    }

    static void _ShowTransactionsMenue()
    {
        clsTransActionScreen::ShowTransactionsMenue();

    }

    static void _ShowManageUsersMenue()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUsersScreen::ShowManageUsersMenue();

    }

   /* static void _ShowEndScreen()
    {
        cout << "\nEnd Screen Will be here...\n";

    }*/


    static void _ShowCurrencyMenuScreen()
    {
        clsCurrencyMainScreen::ShowCurrenciesMenue();
    }

    static void _Logout()
    {
        CurrentUser = CurrentUser.Find("", "");
    }

public:

    static void ShowMainMenue()
    {
        system("cls");
        clsScreen::UpScreen("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Menu.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());

    }
};