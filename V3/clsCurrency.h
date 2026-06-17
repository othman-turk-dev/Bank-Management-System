#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsCurrency
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;

    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;

    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#")
    {
        vector<string> vCurrencyData;
        vCurrencyData = clsMyString::Split(Line, Seperator);

        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stod(vCurrencyData[3]));
    }

    static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
    {
        string stCurrencyRecord = "";
        stCurrencyRecord += Currency.Country() + Seperator;
        stCurrencyRecord += Currency.CurrencyCode() + Seperator;
        stCurrencyRecord += Currency.CurrencyName() + Seperator;
        stCurrencyRecord += to_string(Currency.Rate());

        return stCurrencyRecord;
    }

    static  vector <clsCurrency> _LoadCurrencyDataFromFile()
    {
        vector <clsCurrency> vCurrency;

        fstream MyFile;
        MyFile.open("Data\\CurrencyFile.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

                vCurrency.push_back(Currency);
            }

            MyFile.close();
        }

        return vCurrency;

    }

    static void _SaveCurrencyDataToFile(vector <clsCurrency> vClients)
    {

        fstream MyFile;
        MyFile.open("Data\\CurrencyFile.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsCurrency C : vClients)
            {
                DataLine = _ConverCurrencyObjectToLine(C);
                MyFile << DataLine << endl;
            }

            MyFile.close();

        }

    }

    void _UpdateByCurrencyCode()
    {
        vector <clsCurrency> _vCurrency;
        _vCurrency = _LoadCurrencyDataFromFile();

        for (clsCurrency& C : _vCurrency)
        {
            if (C.CurrencyCode() == CurrencyCode())
            {
                C = *this;
                break;
            }

        }

        _SaveCurrencyDataToFile(_vCurrency);
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:
    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string Country()
    {
        return _Country;
    }

    string CurrencyCode()
    {
        return _CurrencyCode;
    }

    string CurrencyName()
    {
        return _CurrencyName;
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _UpdateByCurrencyCode();
    }

    float Rate()
    {
        return _Rate;
    }

    static clsCurrency FindByCode(string CurrencyCode)
    {
        CurrencyCode = clsMyString::UpperAllString(CurrencyCode);

        fstream MyFile;
        MyFile.open("Data\\CurrencyFile.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }

            }

            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsMyString::UpperAllString(Country);

        fstream MyFile;
        MyFile.open("Data\\CurrencyFile.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (clsMyString::UpperAllString(Currency.Country()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return (!Currency.IsEmpty());
    }

    static vector <clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencyDataFromFile();
    }

    float ConvertToUSD(float Amount)
    {
        return (float)(Amount / Rate());
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);

        if (Currency2.CurrencyCode() == "USD")
        {
            return AmountInUSD;
        }

        return (float)(AmountInUSD * Currency2.Rate());


    };
};