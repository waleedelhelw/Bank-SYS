#pragma once
#include <iostream>
#include "clsScreen.h"
#include "core/clsUser.h"
#include <iomanip>
using namespace std;
class clsLoginRegisterScreen:protected clsScreen
{
private:

    // the passwords that will appeare in list is Encrypted in function _ConvertLoginRegisterLineToRecord()
    //if you want to decrypted go to the above function ic clsUser and decrypted password

    static void PrintLoginRegisterRecordLine(clsUser::stLoginRegesterUser LoginRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.date;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Username;
        cout << "| " << setw(20) << left << LoginRegisterRecord.password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.permessions;
    }


public:


	static void ShowLoginRegisterScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pRegisterScreen))
        {
            return;
        }

		UpScreen("Show Login Register Screen");

        vector<clsUser::stLoginRegesterUser>vUser;
        vUser = clsUser::GetLoginRegisterList();

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vUser.size() == 0)
        {
            cout << "\t\t\t\tNo Logins Available In the System!";
        }
        else
        {
            for (clsUser::stLoginRegesterUser User : vUser)
            {
                PrintLoginRegisterRecordLine(User);
                cout << endl;
            }

            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

        }
        
			
	}
};

