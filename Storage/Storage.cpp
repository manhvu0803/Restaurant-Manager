#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Storage.h"
#include <ctime>
#include "essentials.hpp"
using namespace std;
void Ingredients::exp(ofstream& fp, bool op)
{
	fp << id << "\n";
	fp << name << endl;
	fp << amount << "\n";
	fp << floor << endl;
	fp << unit << endl;
	if (op)
		fp << exd;
}
void Storage::exp()
{
	ofstream File("storage.txt", ios::trunc);
	vector<Ingredients>::iterator it;
	for (it = str.begin(); it != str.end(); it++)
	{
		(*it).exp(File, 1);
		File << endl;
	}
	File.close();
}
void Storage::input(bool op)
{
	string name, unit;
	int amount, id, floor;
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
	cout << "Minimum amount: ";
	cin >> floor;
	while (floor < 0 || amount < 0)
	{
		cout << "Amount: ";
		cin >> amount;
		cout << "Minimum amount: ";
		cin >> floor;
	}
	cin.ignore();
	cout << "Unit: ";
	getline(cin, unit);
	date d;
	if (op)
	cin >> d;
	Ingredients ing(id, name, amount, unit, d, floor);
	str.push_back(ing);
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
		int amount, d, m, y, id, floor;
		file >> id;
		getline(file, line);
		getline(file, name, '\n');
		file >> amount;
		file >> floor;
		getline(file, line);
		getline(file, unit, '\n');
		file >> d;
		file.seekg(1, ios::cur);
		file >> m;
		file.seekg(1, ios::cur);
		file >> y;
		getline(file, line);
		date date(d, m, y);
		Ingredients ing(id, name, amount, unit, date, floor);
		str.push_back(ing);
	}
	file.close();
}
void Ingredients::print()
{
	cout << "ID: " << id << endl;
	cout << "Label: " << name << endl;
	cout << "Amount: " << amount << " " << unit << endl;
	cout << "Date: " << exd;
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
void Ingredients::changeDate()
{
	cin >> exd;
}
bool Ingredients::expired()
{
	date c;
	return (exd >= c);
}