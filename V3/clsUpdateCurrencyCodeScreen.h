#pragma once
#include"clsCurrency.h"
#include"clsScreen.h"
#include"clsInputValidation.h"

using namespace std;

class clsUpdateCurrencyCodeScreen : protected clsScreen
{
private:

    static double _ReadRate()
    {
        cout << "\nEnter New Rate: ";
        double NewRate = 0;

        NewRate = clsInputValidate::ReadNumber<double>();
        return NewRate;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }

public:
    static void ShowUpdateCurrencyRateScreen()
    {

        _DrawScreenHeader("\tUpdate Currency Screen");

        string CurrencyCode = "";

        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrency(Currency);

        cout << "\nAre you sure you want to update the rate of this Currency y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            Currency.UpdateRate(_ReadRate());

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(Currency);
        }
    }

};

