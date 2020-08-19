#ifndef _MENU_H_
#define _MENU_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "dish.h"
using namespace std;

/************************
 * Menu
 * Dung instantiate() de tao object
 * Menu *obj = obj->instantiate
 * Nho delete Menu khi het chuong trinh
************************/
class Menu
{
	static Menu *instance;
	vector<Dish *> menu;
	Menu();

public:
	~Menu();
	Menu *instantiate();
	//void input();
	void output();
	//void save();
	void load();
	void add(Dish *a);
	vector<Dish *> getMenu();
};
#endif
