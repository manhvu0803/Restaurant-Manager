#pragma once
#include <string>
#include <vector>
#include <fstream>
class Date
{
	int d;
	int m;
	int y;
public:
	Date(int d, int m, int y) : d(d), m(m), y(y) {};
	bool expired();
	std::string stringify();
	void print();
};
class Ingredients
{
	std::string id;
	int amount;
	std::string unit;
	Date exd;
public:
	Ingredients(std::string id, int amount, std::string unit, Date exd) : id(id), amount(amount), unit(unit), exd(exd) {};
	void exp(std::ofstream& fp);
	void print();
	bool find(const std::string& n);
	void changeID(const std::string& n);
	bool CheckandAdd(const int& n, bool op, const int& t);//bool op: 1 = add, 0 = check; n = amount to be added; t = threshold ( <= t = bad)
	void changeDate();
};
class Storage
{
	std::vector<Ingredients> str;
	double cost;
public:
	~Storage();
	void imp();
	void print();
	void input();//manual adding
	Ingredients* find(const std::string& f);
	void exp();
};
Date inputDate();
bool leap(int y);