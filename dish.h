#ifndef _DISH_H_
#define _DISH_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//#include <stdlib.h>
//#include <cstdlib>
#include <iomanip>
#include "essentials.hpp"
#include "Storage.h"
using namespace std;

class Dish {
	string id;
	string name;
	vector<Ingredients*> ings;
	double price;
public:
	Dish() : id("None"), name("None"), price(0) {};
	Dish(string id, string name, double price);
	void input();
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
};
#endif