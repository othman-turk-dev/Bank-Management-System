#pragma warning(display:4996)
#pragma once
#include<ctime>
#include<iomanip>
#include<iostream>
#include<vector>
#include<string>
#include"clsString.h"

using namespace std;

class clsDate
{
private:
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;
	
public:

	clsDate()
	{
		time_t t = time(0);
		tm now;
		localtime_s(&now, &t);
		_Day =   now.tm_mday;
		_Month = now.tm_mon + 1;
		_Year =  now.tm_year + 1900;
	}

	clsDate(short Day , short Month , short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	
	clsDate(short TotalDays , short Year)
	{
		short ReminingDays = TotalDays;
		short MonthDay = 0;

		clsDate::_Year = Year;
		clsDate::_Month = 1;

		while (true)
		{
			MonthDay = NumberOfDaysInMonth(clsDate::_Month, Year);
			if (ReminingDays > MonthDay)
			{
				ReminingDays -= MonthDay;
				clsDate::_Month++;
			}
			else
			{
				clsDate::_Day = ReminingDays;
				break;
			}
		}
	}

	clsDate(string stringLine)
	{
		vector<string>vDate = clsMyString::Split(stringLine, "/");

		clsDate::_Day = stod(vDate[0]);
		clsDate::_Month = stod(vDate[1]);
		clsDate::_Year = stod(vDate[2]);
	}

	static clsDate GetSystemDate()
	{
		//system date
		time_t t = time(0);
		tm now;
		localtime_s(&now, &t);

		short Day, Month, Year;

		Year = now.tm_year + 1900;
		Month = now.tm_mon + 1;
		Day = now.tm_mday;

		return clsDate(Day, Month, Year);
	}

	static string GetSystemDateTimeString()
	{
		//system datetime string
		time_t t = time(0);
		tm now;
		localtime_s(&now, &t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now.tm_year + 1900;
		Month = now.tm_mon + 1;
		Day = now.tm_mday;
		Hour = now.tm_hour;
		Minute = now.tm_min;
		Second = now.tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	void Print()
	{
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}

	static bool IsLeapYear(int Year)
	{
		return ((Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0));
	}

	void IsLeapYear()
	{
		if (IsLeapYear(clsDate::_Year))
			cout << "Yes,Is Leap Year";
		else
			cout << "NO, Is Not Leap Year";
	}

	static short NumberOfDaysInMonth(short Month, short Year)
	{
		short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30 ,31,30,31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : (NumberOfDays[Month - 1]);
	}

	void NumberOfDaysInMonth()
	{
		cout << NumberOfDaysInMonth(_Month, _Year) << endl;
	}

	static short NumberOfDaysInYear(int Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}
	
	void NumberOfDaysInYear()
	{
		cout << NumberOfDaysInYear(_Year) << endl;
	}

	static short DayOfWeek(short Year, short Month, short Day)
	{
		int a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;

		return ((Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7);
	}

	void DayOfWeek()
	{
		cout << DayOfWeek(_Year, _Month, _Day) << endl;
	}

	string NameShortMonth(short Month)
	{
		string arr12Month[] = { "Jan","Feb","March","Apr","May","Jaun","July","Aug","Sep","Oct","Nov","Dec" };
		return arr12Month[Month - 1];
	}

	void NameShortMonth()
	{
		cout << NameShortMonth(_Month) << endl;
	}

	void PrintMonthCalender(short Month, short Year)
	{
		short DayOfWeek1 = DayOfWeek(Year, Month, 1);
		short NumberOfDay = NumberOfDaysInMonth(Month, Year);

		printf("\n-----------------------%s--------------------------\n", NameShortMonth(Month).c_str());
		printf("\n  Sun  Mon  Tue  Wed  Thur  Fri  Sat\n");

		short j;
		for (j = 0; j < DayOfWeek1; j++)
		{
			printf("     ");
		}

		for (short i = 1; i <= NumberOfDay; i++)
		{
			printf("%5d", i);
			if (++j == 7)
			{
				j = 0;
				printf("\n");
			}
		}
		printf("\n----------------------------------------------------\n");
	}

	void PrintMonthCalender()
	{
		PrintMonthCalender(_Month, _Year);
	}

	void PrintYearCalender(short Year)
	{
		printf("\n____________________________________________________\n");
		printf("\n                   Calender - %d                   \n", Year);
		printf("____________________________________________________\n");

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalender(i, Year);
		}
	}

	void PrintYearCalender()
	{
		PrintYearCalender(_Year);
	}

	static short NumberOfDaysFromBigginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (short i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, Year);
		}
		TotalDays += Day;

		return TotalDays;
	}

	void NumberOfDaysFromBigginingOfTheYear()const
	{
		cout << NumberOfDaysFromBigginingOfTheYear(_Day, _Month, _Year) << endl;
	}

	clsDate DateAddDays(short DaysAdd, clsDate Date)
	{
		short ReminingDays = DaysAdd + NumberOfDaysFromBigginingOfTheYear(clsDate::_Day, clsDate::_Month, clsDate::_Year);
		short MonthDay = 0;

		clsDate::_Month = 1;

		while (true)
		{

			MonthDay = NumberOfDaysInMonth(clsDate::_Month, clsDate::_Year);
			if (ReminingDays > MonthDay)
			{
				ReminingDays -= MonthDay;
				clsDate::_Month++;
				if (clsDate::_Month > 12)
				{
					clsDate::_Month = 1;
					clsDate::_Year++;
				}
			}
			else
			{
				clsDate::_Day = ReminingDays;
				break;
			}
		}

		return Date;
	}

	clsDate DateAddDays(short DaysAdd)
	{
		return DateAddDays(DaysAdd, *this) ;
	}

	static bool CheckDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? (Date1._Day < Date2._Day) : false)) : false);
	}

	void CheckDate1BeforeDate2(clsDate Date2)
	{
		if (CheckDate1BeforeDate2(*this, Date2))
			cout << "Date1 Before Date2/n";
		else
			cout << "Date1 (NOT) Before Date2/n";
	}
	
	static bool CheckEqualDate(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? (Date1._Day == Date2._Day) : false) : false;
	}

	void CheckEqualDate(clsDate Date2)
	{
		if (CheckEqualDate(*this, Date2))
			cout << "\n\nYes, Date1 is EQUAL Date2..\n";
		else
			cout << "\n\nNo, Date1 is NOT EQUAL Date2..\n";
	}
	
	static bool CheckDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		// Date1 is after Date2 if it's not before and not equal
		return !CheckDate1BeforeDate2(Date1, Date2) && !CheckEqualDate(Date1, Date2);
	}

	void CheckDate1AfterDate2(clsDate Date2)
	{
		if (CheckDate1AfterDate2(*this, Date2))
			cout << "Date1 After Date2\n";
		else
			cout << "Date1 (NOT) After Date2\n";
	}

	static bool IsLastDayInYear(clsDate Date)
	{
		return Date._Day == NumberOfDaysInMonth(Date._Month, Date._Year);
	}

	bool IsLastDayInYear()
	{
		cout << IsLastDayInYear(*this) << endl;
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	void IsLastMonthInYear()
	{
		cout << IsLastMonthInYear(_Month) << endl;
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return (DayOfWeek(Date._Year , Date._Month , Date._Day) == 6);
	}
	
	void IsEndOfWeek()
	{
		if (IsEndOfWeek(*this))
			cout << "Yes , Is End of week\n\n";
		else
			cout << "No , NOT end of week\n\n";
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short DayIndex = DayOfWeek(Date._Year, Date._Month, Date._Day);
		return (DayIndex == 5 || DayIndex == 6);
	}

	void IsWeekEnd()
	{
		if (IsWeekEnd(*this))
			cout << "Yes , Is Week End.\n\n";
		else
			cout << "No , NOT Week End.\n\n";
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return (!IsWeekEnd(Date));
	}

	void IsBusinessDay()
	{
		if (IsBusinessDay(*this))
			cout << "Yes , Is business day\n\n";
		else
			cout << "No , is NOT a BUsiness day\n\n";
	}

	static bool IsValidDate(clsDate Date1)
	{
		if (Date1._Day < 1 || Date1._Day > 31)
			return false;

		if (Date1._Month < 1 || Date1._Month>31)
			return false;

		if (Date1._Month == 2)
		{
			if (IsLeapYear(Date1._Year))
			{
				if (Date1._Day > 29)
					return false;
			}
			else
			{
				if (Date1._Day > 28)
					return false;
			}
		}

		short DayInMonth = NumberOfDaysInMonth(Date1._Month, Date1._Year);

		if (Date1._Day > DayInMonth)
			return false;

		return true;
	}

	void IsValidDate()
	{
		if (IsValidDate(*this))
			cout << "\n\nYes, Date Valid Date.\n";
		else
			cout << "\n\nNo, Date is NOT Valid Date.\n";

	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		// Date >= From && Date <= To
		if ((clsDate::CheckDate1AfterDate2(Date, From) || clsDate::CheckEqualDate(Date, From))
			&&
			(clsDate::CheckDate1BeforeDate2(Date, To) || clsDate::CheckEqualDate(Date, To))
		  )
		{
			return true;
		}

		// Date >= To && Date <= From (reverse range)
		if ((clsDate::CheckDate1AfterDate2(Date, To) || clsDate::CheckEqualDate(Date, To))
			&&
			(clsDate::CheckDate1BeforeDate2(Date, From) || clsDate::CheckEqualDate(Date, From))
		   )
		{
			return true;
		}

		return false;
	}
};

