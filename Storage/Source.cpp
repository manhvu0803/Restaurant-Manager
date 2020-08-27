#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Storage.h"
#include <ctime>
using namespace std;
string Date::stringify()
{
	ostringstream os;
	os << d << endl << m << endl << y;
	return os.str();
}
void Ingredients::exp(ofstream& fp)
{
	fp << id << "\n";
	fp << name << endl;
	fp << amount << "\n";
	fp << unit << endl;
	fp << exd.stringify();
}
void Storage::exp()
{
	ofstream File("storage.txt", ios::trunc);
	vector<Ingredients>::iterator it;
	for (it = str.begin(); it != str.end(); it++)
	{
		(*it).exp(File);
		File << endl;
	}
	File.close();
}
void Storage::input()
{
	string name, unit;
	int amount, id;
	cout << "ID: ";
	cin >> id;
	cin.ignore();
	cout << "Label: ";
	getline(cin, name);
	while (findLabel(name) || findID(id))
	{
		cout << "ID: ";
		cin >> id;
		cin.ignore();
		cout << "Label: ";
		getline(cin, name);
	}
	cout << "Amount: ";
	cin >> amount;
	cin.ignore();
	cout << "Unit: ";
	getline(cin, unit);
	Date date = inputDate();
	Ingredients ing(id, name, amount, unit, date);
	str.push_back(ing);
}
bool leap(int y)
{
	return(((y % 4 == 0) &&(y % 100 != 0)) || (y % 400 == 0));
}
Date inputDate()
{
	int d, m, y;
	cout << "Expiration date: ";
	cin >> d >> m >> y;
	if (d < 1 || d > 31)
		return inputDate();
	if (m < 1 || m > 12)
		return inputDate();
	if (m == 2)
	{
		if (leap(y) && d > 29)
			return inputDate();
		else if (d > 28)
			return inputDate();
	}
	if (d > 30 && (m == 4 || m == 6 || m == 9 || m == 11))
		return inputDate();
	Date date(d, m, y);
	return date;
}
Storage::~Storage()
{
	vector<Ingredients>().swap(str);
}
void Storage::imp()
{
	ifstream file("storage.txt");
	while (file.good())
	{
		if (file.peek() == EOF)
		{
			file.close();
			return;
		}
		string unit, line, name;
		int amount, d, m, y, id;
		file >> id;
		getline(file, line);
		getline(file, name, '\n');
		file >> amount;
		getline(file, line);
		getline(file, unit, '\n');
		file >> d >> m >> y;
		getline(file, line);
		Date date(d, m, y);
		Ingredients ing(id, name, amount, unit, date);
		str.push_back(ing);
	}
	file.close();
}
void Date::print()
{
	cout << d << "/" << m << "/" << y << endl;
}
void Ingredients::print()
{
	cout << "ID: " << id << endl;
	cout << "Label: " << name << endl;
	cout << "Amount: " << amount << " " << unit << endl;
	exd.print();
}
void Storage::print()
{
	for (auto x : str)
	{
		x.print();
		cout << endl;
	}
}
Ingredients* Storage::findID(const int& f)
{
	vector<Ingredients>::iterator it;
	for (it = str.begin(); it != str.end(); it++)
		if ((*it).findID(f))
			return &(*it);
	return NULL;
}
bool Ingredients::findID(const int& n)
{
	if (id == n)
		return true;
	else return false;
}
Ingredients* Storage::findLabel(const string& f)
{
	vector<Ingredients>::iterator it;
	for (it = str.begin(); it != str.end(); it++)
		if ((*it).findLabel(f))
			return &(*it);
	return NULL;
}
bool Ingredients::findLabel(const string& n)
{
	if (name.find(n) != string::npos)
		return true;
	else return false;
}
void Ingredients::changeID(const int& n)
{
	id = n;
}
bool Ingredients::CheckandAdd(const int& n, bool op, const int& t)
{
	if (amount + n <= t)
		return false;
	if (op)
		amount += n;
	return amount;
}
int datefrom(int d, int m, int y)
{
	int leap, day = 0, i;
	if (m > 2)
	{
		day += 58;
		leap = y / 4 - y / 100 + y / 400;
		for (i = 3; i < m; ++i)
		{
			if (i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
				day += 31;
			else
				day += 30;
		}
	}
	else
	{
		leap = (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
		if (m == 2)
			day += 31;
	}
	day += y * 365 + leap + d;
	return day;
}
void Ingredients::changeDate()
{
	exd = inputDate();
}
bool Date::expired()
{
	time_t now = NULL;
	struct tm* t = localtime(&now);
	if (datefrom(d, m, y) >= datefrom(t->tm_mday, t->tm_mon + 1, t->tm_year + 1900))
		return true;
	else return false;
}
bool Ingredients::expired()
{
	return exd.expired();
}