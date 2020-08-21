#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "essentials.hpp"
class Ingredients
{
	int id;
	int amount;
	std::string unit;
	date exd;
	std::string name;
	int floor;
public:
	Ingredients(int id, std::string name, int amount, std::string unit, date exd, int floor) : id(id), name(name), amount(amount), unit(unit), exd(exd), floor(floor) {};
	void exp(std::ofstream& fp, bool op);
	void print();
	bool findID(const int& n);
	bool findLabel(const std::string& n);
	void changeID(const int& n);
	bool CheckandAdd(const int& n, bool op);//bool op: 1 = add, 0 = check; n = amount to be added; t = threshold ( <= t = bad)
	void changeDate(const int& d, const int& m, const int& y);
	bool expired();
	bool compdate(const date& x);
};
class Storage
{
	std::vector<Ingredients> str;
	double cost;
public:
	Storage();
	~Storage();
	void imp();//load txt file into vector
	void print();
	void input(bool op);//manual adding
	Ingredients* findID(const int& f);
	Ingredients* findLabel(const std::string& f);
	void exp();//load vector into txt file
	void restock();
	void lowstock();
	void checkexp();
	void order();
	Ingredients& operator [](int i);
};