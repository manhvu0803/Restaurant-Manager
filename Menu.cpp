#include "menu.h"

void Menu::load() {
	string inputpath = "./restaurant/menu/dishes.txt";
	string tmp;
	string id1, name1, cur1;
	double cost;
	int amount,x;
	ifstream fin,fin1;

	fin.open(inputpath);
	if (!fin.is_open()) {
		cout << "Can't open menu file " << endl;
	}
	else {
		while (getline(fin, tmp)) {
			inputpath = "./restaurant/menu/" + tmp + ".txt";
			fin1.open(inputpath);
			if (!fin1.is_open()) {
				cout << "Can't open dish file " << endl;
			}
			else {
				getline(fin1, tmp);
				id1 = tmp;
				getline(fin1, tmp);
				name1 = tmp;
				getline(fin1, tmp);
				cost = stod(tmp);
				Dish* tmp1 = new Dish(id1, name1, cost);
				while (getline(fin1, tmp)) {
					id1 = tmp;
					getline(fin1, tmp);
					name1 = tmp;
					getline(fin1, tmp);
					amount = stoi(tmp);
					getline(fin1, tmp);
					cur1 = tmp;
					Ingredients* tmp2 = new Ingredients(id1, name1, amount, cur1);
					tmp1->add(tmp2);
				}
				this->add(tmp1);
				fin1.close();
			}
			
		}
		fin.close();
	}


}
void Menu::output() {
	cout << "This is our menu " << endl;
	for (int i = 0; i < menu.size(); i++) {
		cout << setw(2) << left << "(" + to_string(i) + "): ";
		menu[i]->outputMenu();
	}
}
void Menu::add(Dish* a) {
	menu.push_back(a);
}
const vector<Dish*> Menu::getMenuc() {
	return menu;
}
vector<Dish*>Menu::getMenu() {
	return menu;
}
void Menu::save() {
	ofstream fout;
	string outputpath = "./restaurant/menu/dishes.txt";
	fout.open(outputpath);
	if (!fout.is_open()) {
		cout << "Can't open menu file" << endl;
	}
	else {
		for (int i = 0; i < menu.size(); i++) {
			fout << menu[i]->getID() << endl;
		}
		fout.close();
	}
	for (int i = 0; i < menu.size(); i++) {
		outputpath = "./restaurant/menu/" + menu[i]->getID() + ".txt";
		fout.open(outputpath);
		if (!fout.is_open()) {
			cout << "Can't open dish file" << endl;
		}
		else {
			menu[i]->save(fout);
		}

	}
	fout.close();
}
void Menu::newDish() {
	Dish tmp;
	int choice = 1;
	while (choice == 1) {
		tmp.input();
	}
}