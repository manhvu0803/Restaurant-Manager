#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Storage.h"
#include <ctime>
#include "essentials.hpp"
using namespace std;
void Ingredients::changeAmt(const int& x)
{
	amount = x;
}
int Ingredients::getAmount()
{
	return amount;
}
void Ingredients::exp(ofstream& fp, bool op)
{
	fp << id << "\n";
	fp << name << endl;
	fp << amount << "\n";
	if (op)
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
	do
	{
		cout << "ID: ";
		cin >> id;
		cin.ignore();
		cout << "Label: ";
		getline(cin, name);
	} while (findID(id) || findLabel(name));
	do
	{
		cout << "Amount: ";
		cin >> amount;
		cout << "Minimum amount: ";
		cin >> floor;
	} while (floor < 0 || amount < 0);
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
		int amount, id, floor;
		u_int x, y, z;
		file >> id;
		getline(file, line);
		getline(file, name, '\n');
		file >> amount;
		file >> floor;
		getline(file, line);
		getline(file, unit, '\n');
		file >> x;
		file.seekg(1, ios::cur);
		file >> y;
		file.seekg(1, ios::cur);
		file >> z;
		getline(file, line);
		date t(x, y - 1, z);
		Ingredients ing(id, name, amount, unit, t, floor);
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
bool Ingredients::CheckandAdd(const int& n, bool op)
{
	if (amount + n <= 0)
		return false;
	if (op)
		amount += n;
	return (amount > floor);
}
void Ingredients::changeDate(const int& d, const int& m, const int& y)
{
	date n(d, m, y);
	exd = n;
}
bool Ingredients::expired()
{
	date c;
	if (exd >= c)
	{
		amount = 0;
		cout << id << " " << name << endl;
	}
	return (exd >= c);
}
void Storage::checkexp()
{
	cout << "Expired:\n";
	for (auto x : str)
	{
		x.expired();
	}
}
void Storage::lowstock()
{
	cout << "Low stock:\n";
	for (auto x : str)
	{
		if (x.CheckandAdd(0, 0))
			x.print();
	}
}
void Storage::restock()
{
	ifstream file("restock.txt");
	while (file.good())
	{
		if (file.peek() == EOF)
		{
			file.close();
			return;
		}
		int id, fill, c;
		u_int d, m, y;
		string line;
		file >> id;
		getline(file, line);
		file >> fill;
		getline(file, line);
		file >> c;
		cost += c;
		getline(file, line);
		file >> d;
		file.seekg(1, ios::cur);
		file >> m;
		file.seekg(1, ios::cur);
		file >> y;
		int dd, mm, yy;
		dd = d;
		mm = m;
		yy = y;
		getline(file, line);
		getline(file, line);
		Ingredients* x = findID(id);
		x->changeDate(dd, mm, yy);
		x->CheckandAdd(fill, 0);
	}
	file.close();
}
bool Ingredients::compdate(const date& x)
{
	return exd > x;
}
Storage::Storage()
{
	cost = 0;
}
void Storage::order()
{
	ofstream file("restock.txt", ios::app);
	int id, fill, c;
	date d;
	do
	{
		cout << "ID:";
		cin >> id;
		cout << "Amount:";
		cin >> fill;
		cout << "Price: ";
		cin >> c;
		cin >> d;
	} while (findID(id) == NULL || fill < 0 || c < 0 || findID(id)->compdate(d));
	file << id << endl;
	file << fill << endl;
	file << c << endl;
	file << d;
	file.close();
}
Ingredients& Storage::operator[](int i)
{
	return str[i];
}
Ingredients::Ingredients() : exd()
{
	id = 0;
	amount = 0;
	floor = 0;
}
int Ingredients::getID()
{
	return id;
}
string Ingredients::getName()
{
	return name;
}
string Ingredients::getUnit()
{
	return unit;
}
vector<Ingredients> Storage::getStorage()
{
	return str;
}
