#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"lib/clsInputValidate.h"
#include"core/clsBankClient.h"
using namespace std;

class clsTransfersList : protected clsScreen
{
    static void _PrintRecordLine(clsBankClient::stTranserOPinfo TransInfo)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << TransInfo.Username;
        cout << "| " << setw(20) << left << TransInfo.date;
        cout << "| " << setw(15) << left << TransInfo.FromClient;
        cout << "| " << setw(15) << left << TransInfo.ToClient;
        cout << "| " << setw(12) << left << TransInfo.amount << "\n";
    }

public:
    static void TransferList()
    {
        UpScreen("\tTransfer operation");

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________________\n";
        cout << setw(8) << left << "" << "| " << left << setw(12) << "Username";
        cout << "| " << left << setw(20) << "Date";
        cout << "| " << left << setw(15) << "From Acc";
        cout << "| " << left << setw(15) << "To Acc";
        cout << "| " << left << setw(12) << "Amount ";
        cout << "\n\t_________________________________________________________________________\n";

        vector<clsBankClient::stTranserOPinfo> vList = clsBankClient::GetTransfserOP_List();

        if (vList.empty())
        {
            cout << "\t\t\t\tNo OP Available In the System!\n";
        }
        else
        {
            for (clsBankClient::stTranserOPinfo OPinfo : vList)
            {
                _PrintRecordLine(OPinfo);
            }
        }

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________________\n";
    }
};
