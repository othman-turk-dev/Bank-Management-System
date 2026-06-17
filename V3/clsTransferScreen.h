#pragma once
#include<iostream>
#include<string>
#include"clsBnakClient.h"
#include"clsScreen.h"
#include"clsutility.h"
#include"clsString.h"
#include "clsInputValidation.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer : ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static double _ReadAmount(clsBankClient SourceClient)
    {
        double Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadNumber<double>();

        while (Amount > SourceClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadNumber<double>();
        }
        return Amount;
    }

public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t   Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
        
        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
        
        _PrintClient(DestinationClient);

        float Amount = _ReadAmount(SourceClient);

        char Answer = 'n';
        cout << "are you sure do you want to perform this option (y/n) ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient , CurrentUser.UserName))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
	}

};


