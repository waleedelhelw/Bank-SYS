#pragma once

#include<iostream>
#include<iomanip>
#include"Global.h"
#include"lib/clsDate.h"
using namespace std;
class clsScreen
{
public:
	static void UpScreen(string titel, string SubTitle = CurrentUser.UserName())
	{
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << titel;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t Current user: " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
    



	}

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {

        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }

    }
};

