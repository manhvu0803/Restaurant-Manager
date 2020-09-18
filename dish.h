#ifndef _DISH_H_
#define _DISH_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//#include <stdlib.h>
//#include <cstdlib>
#include <stdio.h>
#include <iomanip>
#include "essentials.hpp"
#include "Storage.h"
#include "order.hpp"
#include "Windows.h"
using namespace std;

class Dish {
	string id;
	string name;
	vector<Ingredients*> ings;
	double price;
public:
	Dish() : id("None"), name("None"), price(0) {};
	Dish(string id, string name, double price);
	void outputMenu();
	//void output();
	//void load(string inputpath);
	void add(Ingredients* a);
	string getID();
	string getName();
	double getPrice();
	void save(ofstream& fout);
	void input();
	string generateID(int choice);
	void addIngsToDish(vector<Ingredients> a);
	string newID(string prevID);
	string NtoS(const int& number);
	void change();
	Ingredients* inputIng();
};
#endif