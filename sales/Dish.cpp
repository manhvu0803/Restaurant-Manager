#include "dish.h"

void Date::input()
{
	cout << "Input your date: " << endl;
	cout << "Year: ";
	cin >> y;
	while (y <= 0 || cin.fail())
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Error, try again" << endl;
		cout << "Year: ";
		cin >> y;
	}
	cout << "Month: ";
	cin >> m;
	while (m <= 0 || cin.fail() || m > 12)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Error, try again" << endl;
		cout << "Month: ";
		cin >> m;
	}
	cout << "Day: ";
	cin >> d;
	while (cin.fail() || this->checkday(d, m, y))
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Error, try again" << endl;
		cout << "Day: ";
		cin >> d;
	}
}
bool Date::checkday(int d, int m, int y)
{
	if (d <= 0 || d > 31 || m <= 0 || m > 12 || y <= 0)
	{
		return false;
	}
	else if (d == 29 && m == 2 && y % 400 != 0 && y % 4 != 0 || y % 100 == 0)
	{
		return false;
	}
	else if (d == 30 && m == 2)
	{
		return false;
	}
	else if (d == 31 && m == 4 || m == 6 || m == 9 || m == 11)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Dish::add(Ingredients *a)
{
	ings.push_back(a);
}
Ingredients::Ingredients()
{
	name = "None";
	id = "None";
	amount = 0;
	currency = "None";
}
Ingredients::Ingredients(string id, string name, int amount, string currency)
{
	this->id = id;
	this->name = name;
	this->amount = amount;
	this->currency = currency;
}
Dish::Dish(string id, string name, double cost)
{
	this->id = id;
	this->name = name;
	this->price = cost;
}
string Dish::getID()
{
	return id;
}
string Dish::getName()
{
	return name;
}
double Dish::getPrice()
{
	return price;
}
void Dish::outputMenu()
{
	cout << setw(10) << left << id << ": " << setw(20) << left << name << setw(10) << left << to_string(long int(price)) + " VND" << endl;
}