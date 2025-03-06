#pragma once
#include<iostream>
#include<fstream>
#include"lib/clsDate.h"
#include"Global.h"
#include"clsUser.h"
using namespace std;
class clsLoginRegestir
{
private:
    static string _ConverUserObjectToLoginLine(clsUser User=CurrentUser, string Seperator = "#//#")
    {

        string UserRecord = "";
        //UserRecord += User.FirstName() + Seperator;
        //UserRecord += User.LastName() + Seperator;
        //UserRecord += User.Email() + Seperator;
        //UserRecord += User.PhoneNumber() + Seperator;
        UserRecord += clsDate::GetSystemDateTimeString();
        UserRecord += User.UserName() + Seperator;
        UserRecord += User.Password() + Seperator;
        UserRecord += to_string(User.Permissions());

        return UserRecord;

    }
    
    static void _AddDataLineToLoginFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("E:\\library\\client\\Login file.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }


public:

    static void AddToLoginLoginFile()
    {
        _AddDataLineToLoginFile(_ConverUserObjectToLoginLine());
    }

};

