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
	void change(const std::string& n);
};
class Storage
{
	std::vector<Ingredients> str;
	double cost;
public:
	~Storage();
	void imp();
	void print();
	void input();
	Ingredients* find(const std::string& f);
	bool avail(const std::string& i);
	Date inputDate(int& d, int& m, int& y);
	void exp();
};