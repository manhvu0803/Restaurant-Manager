#ifndef _DISH_H_
#define _DISH_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//#include <stdlib.h>
//#include <cstdlib>
#include <iomanip>
using namespace std;

class Date
{
	int y;
	int m;
	int d;

public:
	Date() : y(1), m(1), d(1){};
	Date(int dd, int mm, int yy) : y(yy), m(mm), d(dd){};
	void input();
	//void output();
	bool checkday(int d, int m, int y);
};
class Ingredients
{
	string id;
	string name;
	int amount;
	string currency;
	Date exd;

public:
	Ingredients();
	Ingredients(string id, string name, int amount, string currency);
	//Ingredients(string id, string name, int amount, string currency, Date exd);
	//void input();
	//void output();
	//void load(string inputpath, int &pos);
	//void load();
};
class Dish
{
	string id;
	string name;
	vector<Ingredients *> ings;
	double price;

public:
	Dish() : id("None"), name("None"), price(0){};
	Dish(string id, string name, double price);
	//void input();
	void outputMenu();
	//void output();
	//void load(string inputpath);
	void add(Ingredients *a);
	string getID();
	string getName();
	double getPrice();
};
#endif