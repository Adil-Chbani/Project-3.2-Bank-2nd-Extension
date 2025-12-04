#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";



struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

// -----------------> Global Variabel <-------------------------
void Login();
void ShowMainMenueATM();
stClient CurrentLogin;
//--------------------------------------------------------------
enum EnClients { QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5 };
enum EnBalanceInQucikWithdraw {
	One1 = 20,
	Two2 = 50,
	Three3 = 100,
	Four4 = 200,
	Five5 = 400,
	Six6 = 600,
	Seven7 = 800,
	Eight8 = 1000,
	Nine9 = 0,

};
vector<string> SplitStringByDelim(string S1, string Delimiter)
{
	int pos = 0;
	vector<string> vString;
	string word = "";
	while ((pos = S1.find(Delimiter)) != S1.npos)
	{
		word = S1.substr(0, pos);
		if (word != "")
		{
			vString.push_back(word);
		}
		S1.erase(0, (pos + Delimiter.length()));
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}

stClient ConvertFileToRecord(string S1, string Delimiter = "#//#")
{
	vector<string>vString = SplitStringByDelim(S1, Delimiter);
	stClient Client;
	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);
	return Client;
}

vector<stClient> LoadFileToRecord(string FileName)
{
	fstream file;
	vector<stClient> stUsers;
	file.open(FileName, ios::in);
	if (file.is_open())
	{
		string line;
		stClient Client;
		while (getline(file, line))
		{
			Client = ConvertFileToRecord(line);
			stUsers.push_back(Client);
		}
		file.close();
	}
	return stUsers;
}

string Space(int NumberSpace)
{
	string ResultSpace = "";
	for (int i = 1; i <= NumberSpace; i++)
	{
		ResultSpace += "\t";
	}
	return ResultSpace;
}
//============================================
void BackToMainMenue()
{
	cout << "Press any Key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenueATM();
}
//--------------------------------> Check Balance <-------------------------------------
int CheckBalanceTakeResult()
{
	/*vector<stClient> sClients = LoadFileToRecord(ClientsFileName);
	for (stClient S : sClients)
	{
		if (CurrentLogin.AccountNumber == S.AccountNumber)
		{
			return S.AccountBalance;
		}
	}
	return 0;
	*/
	return CurrentLogin.AccountBalance;
}
//------------------------> Start Quick Withdraw <--------------
string ConvertRecordToFile(stClient Client, string Delimiter = "#//#")
{
	string Result = "";
	Result += Client.AccountNumber + Delimiter;
	Result += Client.PinCode + Delimiter;
	Result += Client.Name + Delimiter;
	Result += Client.Phone + Delimiter;
	Result += to_string(Client.AccountBalance);
	return Result;
}

void AddOrUpdateContentFile(string fileName, vector<stClient> sClients)
{
	fstream file;
	string StringLineClient = "";
	file.open(fileName, ios::out);
	if (file.is_open())
	{
		for (stClient& Client : sClients)
		{
			StringLineClient = ConvertRecordToFile(Client);
			file << StringLineClient << endl;
		}
		file.close();
	}
}

void WithdrawOptionFromBalance(int Balance)
{
	vector<stClient> sClients = LoadFileToRecord(ClientsFileName);
	for (stClient& S : sClients)
	{
		if (CurrentLogin.AccountNumber == S.AccountNumber)
		{
			S.AccountBalance -= Balance;
			CurrentLogin.AccountBalance = S.AccountBalance;
			break;
		}
	}
	AddOrUpdateContentFile(ClientsFileName, sClients);
	cout << "\nDone Successfully. New balance is : " << CurrentLogin.AccountBalance << endl;
	BackToMainMenue();
}
void CalculateQucikWithdraw(int Balance)
{
	char AskAdd = 'n';
	if (CurrentLogin.AccountBalance < Balance)
	{
		cout << "The amount exceeds your balance, make another choice.";
		BackToMainMenue();
	}
	else
	{
		cout << "\nAre sure you want perfrom this transaction? y/n ? ";
		cin >> AskAdd;
		if (toupper(AskAdd) == 'Y')
		{
			WithdrawOptionFromBalance(Balance);
		}
		else
		{
			BackToMainMenue();
		}
	}
}
int ReadOptionQuicik()
{
	int Number;
	do
	{
		cout << "Choose what to wothdraw from [1] to [8] ? ";
		cin >> Number;
	} while (Number < 1 || Number > 9);
	if (Number == 1)
	{
		return EnBalanceInQucikWithdraw::One1;
	}
	else if (Number == 2)
	{
		return EnBalanceInQucikWithdraw::Two2;
	}
	else if (Number == 3)
	{
		return EnBalanceInQucikWithdraw::Three3;
	}
	else if (Number == 4)
	{
		return EnBalanceInQucikWithdraw::Four4;
	}
	else if (Number == 5)
	{
		return EnBalanceInQucikWithdraw::Five5;
	}
	else if (Number == 6)
	{
		return EnBalanceInQucikWithdraw::Six6;
	}
	else if (Number == 7)
	{
		return EnBalanceInQucikWithdraw::Seven7;
	}
	else if (Number == 8)
	{
		return EnBalanceInQucikWithdraw::Eight8;
	}
	else if (Number == 9)
	{
		BackToMainMenue();
	}
}

void ShowQucikWithdraw()
{
	cout << "=========================================================\n";
	cout << Space(2) << "Check Balance Screen\n";
	cout << "=========================================================\n";
	cout << Space(1) << "[1] 20" << Space(2) << "[2] 50" << endl;
	cout << Space(1) << "[3] 100" << Space(2) << "[4] 200" << endl;
	cout << Space(1) << "[5] 400" << Space(2) << "[6] 600" << endl;
	cout << Space(1) << "[7] 800" << Space(2) << "[8] 1000" << endl;
	cout << Space(1) << "[9] Exit" << endl;
	cout << "=========================================================\n";

	cout << "Your Balance is " << CheckBalanceTakeResult() << endl;
	CalculateQucikWithdraw(ReadOptionQuicik());

}
void ShowBalance()
{
	cout << "=========================================================\n";
	cout << Space(2) << "Check Balance Screen\n";
	cout << "=========================================================\n";
	cout << "Your Balance is " << CheckBalanceTakeResult() << endl;
}

//--------------------------------------------> Normal Withdraw  <-----------------------------------

int ReadNormalWithdraw()
{
	int Balance;
	do
	{
		cout << "\nEnter an Amount Multiple of 5's ? ";
		cin >> Balance;
		while (cin.fail())
			cin.clear();
		cin.ignore(numeric_limits <std::streamsize>::max(), '\n');
		cout << "please Enter Positive Number ";
		cin >> Balance;
	} while (Balance < 0);
	return Balance;
}
void CheckNormalWithdraw()
{
	int Balance = 0;
	do
	{
		Balance = ReadNormalWithdraw();

	} while (Balance % 5 != 0);
	CalculateQucikWithdraw(Balance);

}
void ShowNormalWithdraw()
{
	cout << "=========================================================\n";
	cout << Space(2) << "Normal Withdraw  Screen\n";
	cout << "=========================================================\n";
	CheckNormalWithdraw();
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> Deposit Screen <_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void DepositToBalance(int Balance)
{
	vector<stClient> sClients = LoadFileToRecord(ClientsFileName);
	for (stClient& S : sClients)
	{
		if (CurrentLogin.AccountNumber == S.AccountNumber)
		{
			S.AccountBalance += Balance;
			CurrentLogin.AccountBalance = S.AccountBalance;
			break;
		}
	}
	AddOrUpdateContentFile(ClientsFileName, sClients);
	cout << "\nDone Successfully. New balance is : " << CurrentLogin.AccountBalance << endl;
	BackToMainMenue();
}

int ReadValueDeposit()
{
	int Balance;
	do {
		cout << "\nEnter a Positive Deposit Amount? ";
		cin >> Balance;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please Enter Number Positive : ";
			cin >> Balance;
		}
	} while (Balance < 0);
	return Balance;
}

void CheckDeposit(int Balance)
{
	char AskAdd = 'n';
	cout << "\nAre sure you want perfrom this transaction? y/n ? ";
	cin >> AskAdd;
	if (toupper(AskAdd) == 'Y')
	{
		DepositToBalance(Balance);
	}
	else
	{
		BackToMainMenue();
	}

}

void DepositToBalanceClient()
{
	char AskAdd = 'n';
	CheckDeposit(ReadValueDeposit());
}

void ShowDeposit()
{
	cout << "=========================================================\n";
	cout << Space(2) << "Deposit Screen\n";
	cout << "=========================================================\n";
	DepositToBalanceClient();
}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-> Switch ALL Information <_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void PermitUseAllInMenue(EnClients Client)
{
	switch (Client)
	{
	case EnClients::QuickWithdraw:
		system("cls");
		ShowQucikWithdraw();
		BackToMainMenue();
		break;
	case EnClients::NormalWithdraw:
		system("cls");
		ShowNormalWithdraw();
		BackToMainMenue();
		break;

	case EnClients::Deposit:
		system("cls");
		ShowDeposit();
		BackToMainMenue();
		break;

	case EnClients::CheckBalance:
		system("cls");
		ShowBalance();
		BackToMainMenue();
		break;

	case EnClients::Logout:
		Login();
		break;

	}
}

// -----------------------------------------------------------> Start Menue ATM <---------------------------------------------------------------------------------
int ReadValueMenue()
{
	int Number = 0;

	do {
		cout << "Choose what do you want to do? [1 to 5 ]? ";
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please Enter Number Positive From 1 a 5: ";
			cin >> Number;
		}
	} while (Number < 1 || Number > 5);
	return Number;
}
void ShowMainMenueATM()
{
	system("cls");
	cout << "=========================================================\n";
	cout << Space(2) << "ATM Main Menue Screen\n";
	cout << "=========================================================\n";
	cout << Space(1) << "[1] Quick Withdraw.\n";
	cout << Space(1) << "[2] Normal Withdraw.\n";
	cout << Space(1) << "[3] Deposit.\n";
	cout << Space(1) << "[4] Check Balance.\n";
	cout << Space(1) << "[5] Logout.\n";
	cout << "=========================================================\n";
	PermitUseAllInMenue((EnClients)ReadValueMenue());
}

// -------------------------------------------------------------> Login <------------------------------------------------------------------------------------------
bool FindLogin(string AccountNumber, string PinCode, stClient& Client)
{
	vector < stClient> Clients = LoadFileToRecord(ClientsFileName);
	for (stClient& C : Clients)
	{
		if (AccountNumber == C.AccountNumber)
		{
			if (PinCode == C.PinCode)
			{
				Client = C;
				return true;
			}
		}
	}
	return false;
}

void Login()
{
	string AccountNumber, PinCode;
	bool LoginFailed = false;
	do
	{
		system("cls");
		cout << "------------------------------------------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "------------------------------------------------------------\n";
		if (LoginFailed)
		{
			cout << "Invalide Account Nubmer/PonCode!" << endl;
		}
		cout << "Enter Account Number? ";
		getline(cin >> ws, AccountNumber);
		cout << "Enter Password? ";
		getline(cin, PinCode);
		LoginFailed = !FindLogin(AccountNumber, PinCode, CurrentLogin);
	} while (LoginFailed);
	ShowMainMenueATM();
}

int main()
{
	Login();
	return 0;
}