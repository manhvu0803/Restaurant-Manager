#ifndef _MENU_H_
#define _MENU_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "dish.h"
#include "essentials.hpp"

using namespace std;

class Menu {
	Menu();
	static Menu* single;
	vector<Dish*> menu;
public:
	//void input();
	void output();
	void save();
	void load();
	int add(Dish* a);
	const vector<Dish*> getMenuc();
	vector<Dish*> getMenu();
	void newDish();
	void removeDish();
	void changeDish();
	bool deleteFile(string path);
	//void favor();
	static Menu* instantiate();
	//~Menu();

};
#endif
