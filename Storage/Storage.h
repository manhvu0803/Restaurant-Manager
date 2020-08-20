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
	int id;
	int amount;
	std::string unit;
	Date exd;
	std::string name;
public:
	Ingredients(int id, std::string name, int amount, std::string unit, Date exd) : id(id), name(name), amount(amount), unit(unit), exd(exd) {};
	void exp(std::ofstream& fp);
	void print();
	bool findID(const int& n);
	bool findLabel(const std::string& n);
	void changeID(const int& n);
	bool CheckandAdd(const int& n, bool op, const int& t);//bool op: 1 = add, 0 = check; n = amount to be added; t = threshold ( <= t = bad)
	void changeDate();
	bool expired();
};
class Storage
{
	std::vector<Ingredients> str;
	double cost;
public:
	~Storage();
	void imp();//load txt file into vector
	void print();
	void input();//manual adding
	Ingredients* findID(const int& f);
	Ingredients* findLabel(const std::string& f);
	void exp();//load vector into txt file
	void restock();
	void checkexp();
};
Date inputDate();
bool leap(int y);