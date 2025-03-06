#pragma once
#include <iostream>
#include "clsScreen.h"
#include "core/clsUser.h"
#include <iomanip>
using namespace std;

class clsListUsersScreen :protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser User)
    {

        cout << setw(8) << left << "" << "| " << setw(12) << left << User.UserName();
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(12) << left << User.PhoneNumber();
        cout << "| " << setw(20) << left << User.Email();
        cout << "| " << setw(10) << left << User.Password();
        cout << "| " << setw(12) << left << User.Permissions();

    }

public:
	static void ShowListUsersScreen()
	{
        vector<clsUser>vUser;
        vUser = clsUser::ListUser();

        UpScreen("Show User List");
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUser.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser User : vUser)
            {

                _PrintUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }
	
};

