#pragma once
#include"clsCurrencyListScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyCodeScreen.h"
#include"clsCurrencyCalcuterScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen
{

private:
    enum enCurrencyExchangeMenu
    {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateCurrency = 3,
        eCurrencyCalculater = 4,
        eShowMainMenue = 5
    };

    static short ReadCurrencyMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _ShowListCurrenciesScreen()
    {
        //cout << "\n _ShowListCurrenciesScreen Screen will be here.\n";
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        //cout << "\n _ShowFindCurrencyScreen Screen will be here.\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyScreen()
    {
         //cout << "\n _ShowUpdateCurrencyScreen Screen will be here.\n";
        clsUpdateCurrencyCodeScreen::ShowUpdateCurrencyRateScreen();

    }

    static void _ShowCurrencyCalculaterScreen()
    {
        //cout << "\n _ShowCurrencyCalculaterScreen Screen will be here.\n";
        clsCurrencyCalcuterScreen::ShowCurrencyCalculatorScreen();
    }

    static void _GoBackToCurrencyMenu()
    {
        cout << "\n\nPress any key to go back to Currency Meun...";
        system("pause>0");
        ShowCurrencyMenue();
    }

    static void _PerformTransactionsMenueOption(enCurrencyExchangeMenu CurrencyExchangeMenu)
    {
        switch (CurrencyExchangeMenu)
        {
        case enCurrencyExchangeMenu::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyMenu();
            break;
        }

        case enCurrencyExchangeMenu::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyMenu();
            break;
        }


        case enCurrencyExchangeMenu::eUpdateCurrency:
        {
            system("cls");
            _ShowUpdateCurrencyScreen();
            _GoBackToCurrencyMenu();
            break;
        }

        case enCurrencyExchangeMenu::eCurrencyCalculater:
        {
            system("cls");
            _ShowCurrencyCalculaterScreen();
            _GoBackToCurrencyMenu();
            break;
        }

        case enCurrencyExchangeMenu::eShowMainMenue:
        {

            //do nothing here the main screen will handle it :-) ;

        }
        }


    }



public:
    static void ShowCurrencyMenue()
    {

        //if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        //{
        //    return;// this will exit the function and it will not continue
        //}

        system("cls");
        _DrawScreenHeader("\t  Currency Main Menu Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currency.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Currency.\n";
        cout << setw(37) << left << "" << "\t[4] CurrencyCalculater.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enCurrencyExchangeMenu)ReadCurrencyMenueOption());
    }
};

