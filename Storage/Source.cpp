#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Storage.h"
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
	string id, unit;
	int amount;
	cout << "Label: ";
	getline(cin, id);
	cout << "Amount: ";
	cin >> amount;
	cin.ignore();
	cout << "Unit: ";
	getline(cin, unit);
	Date date = inputDate();
	Ingredients ing(id, amount, unit, date);
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
		string id, unit, line;
		int amount, d, m, y;
		getline(file, id, '\n');
		file >> amount;
		getline(file, line);
		getline(file, unit, '\n');
		file >> d >> m >> y;
		getline(file, line);
		Date date(d, m, y);
		Ingredients ing(id, amount, unit, date);
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
Ingredients* Storage::find(const string& n)
{
	vector<Ingredients>::iterator it;
	for (it = str.begin(); it != str.end(); it++)
		if ((*it).find(n))
			return &(*it);
	return NULL;
}
bool Ingredients::find(const string& n)
{
	if (id.find(n) != string::npos)
		return true;
	else return false;
}
void Ingredients::changeID(const string& n)
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
void Ingredients::changeDate()
{
	exd = inputDate();
}