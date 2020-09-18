#include "menu.h"

/*Menu::~Menu() {
	delete single;
}*/
Menu::Menu(){}
Menu& Menu::instantiate() {
	static Menu instance;
	return instance;
}
//Menu* Menu::single = nullptr;
void Menu::load() {
	string inputpath = "./restaurant/menu/dishes.txt";
	string tmp;
	string id1, name1, cur1;
	double cost;
	date dt;
	int amount,x;
	ifstream fin,fin1;
	if (menu.size() != 0) {
		menu.clear();
	}
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
					x = stoi(tmp);
					getline(fin1, tmp);
					name1 = tmp;
					getline(fin1, tmp);
					amount = stoi(tmp);
					getline(fin1, tmp);
					cur1 = tmp;
					Ingredients* tmp2 = new Ingredients(x, name1, amount, cur1, dt,-1);
					tmp1->add(tmp2);
				}
				menu.push_back(tmp1);
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
int Menu::add(Dish* a) {
	int flag = -2;
	size_t found = a->getID().find("DK");
	if (found != string::npos) {
		menu.push_back(a);
		return menu.size() - 1;
	}
	else {
		size_t found1;
		for (int i = 0; i < menu.size(); i++) {
			found1 = menu[i]->getID().find("DK");
			if (found1 != string::npos) {
				flag = i;
				break;
			}
		}
		if (flag == -2) {
			menu.push_back(a);
			return menu.size() - 1;
		}
		else {
			menu.insert(menu.begin() + flag, a);
			return flag;
		}
	}
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
	int pos;
	order& obj = obj.instantiate();
	int choice = 1, choice1;
	while (choice == 1) {
		tmp.input();
		tmp.outputMenu();
		cout << "Do you want to add this dish to your menu? (0: No, 1: Yes) :";
		cin >> choice;
		pos = this->add(&tmp);
		obj.update(pos, 1);
		cout << "Successfully add " << endl;
		this->output();
		cout << "Do you want to add another dish? (0: No, 1: Yes): " << endl;
		cin >> choice;
	}
}
void Menu::removeDish() {
	int choice = 1,choice1 ;
	order& obj = obj.instantiate();
	while (choice == 1) {
		if (menu.size() != 0) {
			for (int i = 0; i < menu.size(); i++) {
				cout << setw(3) << left << "(" + to_string(i) + ")" << setw(6) << left << menu[i]->getID() << setw(20) << left << menu[i]->getName() << endl;
			}
			cout << "Choose the dish you want to remove " << endl;
			cout << "Your dish index: ";
			cin >> choice1;
			cin.ignore(256, '\n');
			menu.erase(menu.begin() + choice1);
			obj.update(choice1, 0);
			this->save();
			bool re = this->deleteFile("./restaurant/menu/" + menu[choice1]->getID());
			if (re) {
				cout << "Delete successfully" << endl;
			}
			else {
				cout << "Can't delete" << endl;
			}
			cout << "Do you want to delete any other dish? (0: No, 1: Yes): ";
			cin >> choice;
		}
		else {
			cout << "Nothing to show" << endl;
			choice = 0;
		}
	}
}
void Menu::changeDish() {
	int choice = 1, choice1;
	while (choice == 1) {
		if (menu.size() != 0) {
			for (int i = 0; i < menu.size(); i++) {
				cout << setw(3) << left << "(" + to_string(i) + ")" << setw(6) << left << menu[i]->getID() << setw(20) << left << menu[i]->getName() << endl;
			}
			cout << "Choose the dish you want to change " << endl;
			cout << "Your dish index: ";
			cin >> choice1;
			cin.ignore(256, '\n');
			menu[choice1]->change();
		}
		else {
			cout << "Nothing to show" << endl;
			choice = 0;
		}
		cout << "Do you want to change another dish ?" << endl;
		cout << "Your choice (0: NO , 1: YES): ";
		cin >> choice;
	}
}
bool Menu::deleteFile(string path) {
	int ret = remove(path.c_str());
	if (ret == 0) {
		return true;
	}
	else {
		return false;
	}
}
int Menu::favor() {
	string inputpath = "./restaurant/DishOrdered.txt";
	ifstream fin;
	fin.open(inputpath);
	if (!fin.is_open()) {
		cout << "Can't open file" << endl;
	}
	else {
		cout << "Can open" << endl;
	}
	fin.close();
	return 1;
}