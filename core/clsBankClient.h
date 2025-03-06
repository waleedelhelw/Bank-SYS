#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"lib/clsStrings.h"
#include"clsPerson.h"
#include"lib/clsInputValidate.h"
class clsBankClient :public clsPerson
{
private:
	enum enMode { enEmpty = 1, enUpdate = 2 ,enAddNew=3 ,enDelete=4};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelet = false;

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::enUpdate, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
		
	}

	static string _ConvertDataToLine(clsBankClient& client, string Seperator = "#//#")
	{
		string line="";
		line += client.FirstName() + Seperator;
		line += client.LastName() + Seperator;
		line += client.Email() + Seperator;
		line += client.PhoneNumber() + Seperator;
		line += client.AccountNumber() + Seperator;
		line += client.PinCode() + Seperator;
		line += to_string(client.AccountBalance());
		return line;
	}

	static void _SaveDataToFile(vector<clsBankClient>vClients)
	{

		fstream MyFile;
		MyFile.open("E:\\library\\client\\Clients.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBankClient C : vClients)
			{
				if (C.MarkForDelete()==false)
				{
					DataLine = _ConvertDataToLine(C);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();

		}

	}

	void _Update()
	{
		vector<clsBankClient>_vClient;
		_vClient = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveDataToFile(_vClient);
		
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertDataToLine(*this));
	}

	static  vector <clsBankClient> _LoadClientsDataFromFile()
	{

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("E:\\library\\client\\Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLinetoClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();

		}

		return vClients;

	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("E:\\library\\client\\Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::enEmpty, "", "", "", "", "", "", 0);
	}

	 string _PrepareTransferOperation(float amount, clsBankClient & TOClient,string Seperator = "#//#")
	 {
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += AccountNumber() +Seperator +TOClient.AccountNumber() + Seperator+to_string(amount)+Seperator;
		LoginRecord += CurrentUser.UserName();
		return LoginRecord;
	 }

	 struct stTranserOPinfo;

	 static stTranserOPinfo _ConvertLoginRegisterTransferToRecord(string Line, string Seperator = "#//#")
	 {
		 stTranserOPinfo TranserOPinfo;
		 vector<string> vInfo = clsString::Split(Line, Seperator);
		 TranserOPinfo.date = vInfo[0];
		 TranserOPinfo.FromClient= vInfo[1];
		 TranserOPinfo.ToClient = vInfo[2];
		 TranserOPinfo.amount = stof( vInfo[3]);
		 TranserOPinfo.Username = vInfo[4];

		 return TranserOPinfo;
	 }


public:

	
	clsBankClient(enMode mode, string firstName, string lastName, string email, string Phone
		, string AccountNumber, string Pincode, float AccountBalance)
		:clsPerson(firstName, lastName, email, Phone)
	{
		_Mode = mode;
		_AccountNumber = AccountNumber;
		_PinCode = Pincode;
		_AccountBalance = AccountBalance;
	}

	struct stTranserOPinfo
	{
		string date;
		string FromClient;
		string ToClient;
		float amount;
		string Username;
	};


	bool IsEmpty()
	{
		return (_Mode == enMode::enEmpty);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string PinCode()
	{
		return _PinCode;
	}
	//__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;


	 void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	 float AccountBalance()
	{
		return _AccountBalance;
	}
	//__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirst Name   : " << FirstName();
		cout << "\nlast Name    : " << LastName();
		cout << "\nFullName     : " << FullName();
		cout << "\nEmail        : " << Email();
		cout << "\nPhone        : " << PhoneNumber();
		cout << "\nAcc. Number  : " << AccountNumber();
		cout << "\nPassword     : " << PinCode();
		cout << "\nBalance      : " << AccountBalance();
		cout << "\n___________________\n";

	}*/


	

	static clsBankClient Find(string AccountNumber)
	{
		
		fstream MyFile("E:\\library\\client\\Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
		}
		MyFile.close();
		return _GetEmptyClientObject();

	}

	
	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 , svFailedUsedAccount };

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::enEmpty:
		{

			return enSaveResults::svFaildEmptyObject;
		}
		// update mode ===========================================
		case enMode::enUpdate:
		{
			_Update();
			return enSaveResults::svSucceeded;

			break;
		}
		// add new mode ============================================
		case enMode::enAddNew:
		{
			if (IsClientExit(_AccountNumber))
			{
				return enSaveResults::svFailedUsedAccount;
				break;
			}
			else
			{
				_AddNew();
				//convert mode to update mode
				enMode::enUpdate;
				return enSaveResults::svSucceeded;
				break;
			}
		}
		//-- mode ====================================================

		}

	}

	static clsBankClient AddNewAccNumber(string accountNmber)
	{
		return clsBankClient(enMode::enAddNew, "", "", "", "", accountNmber, "", 0);
	}

	bool MarkForDelete()
	{
		return _MarkForDelet;
	}

	static bool IsClientExit(string accountNumber)
	{
		clsBankClient client = clsBankClient::Find(accountNumber);
		return (!client.IsEmpty());
	}
	bool IsClientExit()
	{
		return (clsBankClient::IsClientExit(this->_AccountNumber));
	}


	bool Delete()
	{
		vector<clsBankClient>_vClient;

		_vClient = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelet = true;
				break;
			}
		}

		_SaveDataToFile(_vClient);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector<clsBankClient>ListClient()
	{
		vector<clsBankClient>vList;
		vList = _LoadClientsDataFromFile();
		return vList;
	}

	static float TotalBalace(vector<clsBankClient>vClients)
	{
		vClients = _LoadClientsDataFromFile();
		float totalBalance = 0;
		for (clsBankClient client : vClients)
		{
			totalBalance += client.AccountBalance();
		}

		return totalBalance;
	}

	static void PrintClientRecordLine(clsBankClient Client)
	{

		cout << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.PhoneNumber();
		cout << "| " << setw(25) << left << Client.Email();
		cout << "| " << setw(10) << left << Client.PinCode();
		cout << "| " << setw(12) << left << Client.AccountBalance();

	}

	static clsBankClient ReadClientInfo(clsBankClient& Client)
	{
		cout << "Enter client's first Name      : ";
		Client.SetFirstName(clsInputValidate::ReadString());

		cout << "Enter client's last Name       : ";
		Client.SetLastName(clsInputValidate::ReadString());

		cout << "Enter client's Email           : ";
		Client.SetEmail(clsInputValidate::ReadString());

		cout << "Enter client's Phone           : ";
		Client.setPhone(clsInputValidate::ReadString());

		cout << "Enter client's PinCode         : ";
		Client.SetPinCode(clsInputValidate::ReadString());

		cout << "Enter client's Account Balance : ";
		Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());

		return Client;


	}
	void Deposite(float depositeMoney)
	{
		SetAccountBalance(AccountBalance() + depositeMoney);
	}
	

	void Withdraw(float withdrawMoney)
	{
		SetAccountBalance(AccountBalance() - withdrawMoney);
	}
	

	bool Trasfer(float amount,clsBankClient&ToClient)
	{
		if (amount >= 5 && amount <= AccountBalance())
		{
			
			Withdraw(amount);
			ToClient.Deposite(amount);
			TransferRggister(ToClient, amount);
			return true;
		}
		return false;
	}


	void TransferRggister(clsBankClient& ToClient,float amount)
	{
		string stDataLine = _PrepareTransferOperation(amount, ToClient);

		fstream MyFile;
		MyFile.open("E:\\library\\client\\Transfer register.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}



	static vector<stTranserOPinfo> GetTransfserOP_List()
	{
		vector <stTranserOPinfo> vTansferRegisterRecord;

		fstream MyFile;
		MyFile.open("E:\\library\\client\\Transfer register.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stTranserOPinfo TansferRegisterRecord;

			while (getline(MyFile, Line))
			{

				TansferRegisterRecord = _ConvertLoginRegisterTransferToRecord(Line);

				vTansferRegisterRecord.push_back(TansferRegisterRecord);

			}

			MyFile.close();

		}

		return vTansferRegisterRecord;

	}
	

};