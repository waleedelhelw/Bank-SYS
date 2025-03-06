#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"lib/clsStrings.h"
#include"clsPerson.h"
#include"lib/clsInputValidate.h"
#include"lib/clsUtil.h"
//#include"Global.h"
using namespace std;

class clsUser :public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkForDelete = false;
    bool _MarkedForDelete = false;

    
    struct stLoginRegesterUser;

    static stLoginRegesterUser _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegesterUser LoginRegisterRecord;


        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.date = LoginRegisterDataLine[0];
        LoginRegisterRecord.Username = LoginRegisterDataLine[1];
        LoginRegisterRecord.password = LoginRegisterDataLine[2]; // I made pssword encrypted
        //LoginRegisterRecord.password = clsUtil::DecryptText( LoginRegisterDataLine[2]);
        LoginRegisterRecord.permessions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName() + Seperator;
        UserRecord += User.LastName() + Seperator;
        UserRecord += User.Email() + Seperator;
        UserRecord += User.PhoneNumber() + Seperator;
        UserRecord += User.UserName() + Seperator;
        //UserRecord += User.Password() + Seperator;
        UserRecord += clsUtil::EncryptText(User.Password())+Seperator;
        UserRecord += to_string(User.Permissions());

        return UserRecord;

    }

    static clsUser _ConvertLinetoClientObject(string Line,string Seperator = "#//#")
    {
        vector<string> vUser;
        vUser = clsString::Split(Line,Seperator);

        return clsUser(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3],
            vUser[4], clsUtil::DecryptText( vUser[5]), stoi(vUser[6]));
    }

    static vector<clsUser>_LoadUserDataFromFile()  // there is an file here
    {
        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("E:\\library\\client\\User manger.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoClientObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("E:\\library\\client\\User manger.txt", ios::out | ios::app);  // there is a file here

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }


    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += UserName () + Seperator;
        LoginRecord += clsUtil::EncryptText( Password ()) + Seperator;
        LoginRecord += to_string(Permissions());
        return LoginRecord;
    }



  

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertDataToLine(*this));
    }

    void _Update()
    {
        vector<clsUser>_vUser;
        _vUser = _LoadUserDataFromFile();
        for (clsUser& C : _vUser)
        {
            if (C.UserName() == UserName())
            {
                C = *this;
                break;
            }
        }

        _SaveDataToFile(_vUser);

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode,"","","","","","",0);
    }

    static string _ConvertDataToLine(clsUser& user, string Seperator = "#//#")
    {
        string line = "";
        line += user.FirstName() + Seperator;
        line += user.LastName() + Seperator;
        line += user.Email() + Seperator;
        line += user.PhoneNumber() + Seperator;
        line += user.UserName() + Seperator;
        //line += user.Password() + Seperator;
        line += clsUtil::EncryptText(user.Password())+Seperator;
        line += to_string(user.Permissions());
        return line;
    }

    static void _SaveDataToFile(vector<clsUser>vClients)
    {

        fstream MyFile;
        MyFile.open("E:\\library\\client\\User manger.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser C : vClients)
            {
                if (C.MarkForDelete() == false)
                {
                    DataLine = _ConvertDataToLine(C);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        return Permissions;

    }

public:
    struct stLoginRegesterUser
    {
        string date;
        string Username;
        string password;
        int permessions;
    };

    clsUser(enMode mode, string firstName, string lastName, string email, string phone, string username, string password, int permessinos)
        :clsPerson(firstName, lastName, email, phone)
    {
        _Mode = mode;
        _UserName = username;
        _Password = password;
        _Permissions = permessinos;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    static clsUser AddNewUser(string userName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", userName, "", 0);
    }


    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
        , pRegisterScreen = 128, pCurrencyscreen=265
    };


    void setPassword(std::string password) 
    {
        _Password = password;
    }

    void setPermissions(int permissions) 
    {
        _Permissions = permissions;
    }

    // Getters

    string UserName() 
    {
        return _UserName;
    }

    string Password() 
    {
        return _Password;
    }

    int Permissions()
    {
        return _Permissions;
    }

    bool MarkForDelete()
    {
        return _MarkedForDelete;
    }



    static bool IsUserExit(string username)
    {
        vector<clsUser>vUser;
        vUser = _LoadUserDataFromFile();
        for (clsUser& user : vUser)
        {
            if(user.UserName()==username)
            {
                return true;
            }
        }
        return false;
    }

    static clsUser Find(string Username)  // file herer
    {

        fstream MyFile("E:\\library\\client\\User manger.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser Client = _ConvertLinetoClientObject(Line);
                if (Client.UserName() == Username)
                {
                    MyFile.close();
                    return Client;
                }
            }
        }
        MyFile.close();
        return _GetEmptyUserObject();

    }


    static clsUser Find(string Username, string Password)  // file herer
    {

        fstream MyFile("E:\\library\\client\\User manger.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser user = _ConvertLinetoClientObject(Line);
                if (user.UserName() == Username && user.Password()==Password)
                {
                    MyFile.close();
                    return user;
                }
            }
        }
        MyFile.close();
        return _GetEmptyUserObject();

    }

    static vector<clsUser>ListUser()
    {
        vector<clsUser>vList;
        vList = _LoadUserDataFromFile();
        return vList;
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFailedUsedAccount };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
        }
        // update mode ===========================================
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }
        // add new mode ============================================
        case enMode::AddNewMode:
        {
            if (IsUserExit(_UserName))
            {
                return enSaveResults::svFailedUsedAccount;
                break;
            }
            else
            {
                _AddNew();
                //convert mode to update mode
                _Mode= enMode::UpdateMode;
                return enSaveResults::svSucceeded;
                break;
            }
        }
        //-- mode ====================================================

        }

    }


   /* static int ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        return Permissions;

    }*/

    static clsUser ReadUsernfo(clsUser& User)
    {
        cout << "Enter User first Name      : ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "Enter User's last Name       : ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "Enter User's Email           : ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "Enter User's Phone           : ";
        User.setPhone(clsInputValidate::ReadString());

        cout << "Enter User's password        : ";
        User.setPassword(clsInputValidate::ReadString());

        User.setPermissions(_ReadPermissionsToSet());

        return User;


    }

    void Update()
    {
        clsUser::ReadUsernfo(*this);
    }

    bool Delete()
    {
        vector<clsUser> vUser = _LoadUserDataFromFile();

        for (clsUser& U : vUser)
        {
            if (U.UserName() == _UserName)
            {
                U._MarkedForDelete = true; 
                break;
            }
        }

        _SaveDataToFile(vUser);
        *this = _GetEmptyUserObject();  

        return true;
    }


    

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions() == enPermissions::eAll)
            return true;

        if ((Permission & this->Permissions()) == Permission)
            return true;
        else
            return false;

    }

    void UserRegester()
    {
        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("E:\\library\\client\\Login file.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }




    static  vector <stLoginRegesterUser> GetLoginRegisterList()
    {
        vector <stLoginRegesterUser> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("E:\\library\\client\\Login file.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stLoginRegesterUser LoginRegisterRecord;

            while (getline(MyFile, Line))
            {

                LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

                vLoginRegisterRecord.push_back(LoginRegisterRecord);

            }

            MyFile.close();

        }

        return vLoginRegisterRecord;

    }

};


