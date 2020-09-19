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
	system("cls");
	cout << "This is our menu " << endl;
	vector<pair<int, int>> tmp = this->favor();
	for (int i = 0; i < menu.size(); i++) {
		cout << setw(3) << left << to_string(i+1) ;
		if (tmp.size() > 4) {
			for (int j = 0; j < tmp.size() / 4; j++) {
				if (i == tmp[j].first) {
					menu[i]->outputMenu(true);
				}
				else {
					menu[i]->outputMenu(false);
				}
			}
		}
		else {
			if (i == tmp[0].first) {
				menu[i]->outputMenu(true);
			}
			else {
				menu[i]->outputMenu(false);
			}
		}
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
	ofstream fout;
	while (choice == 1) {
		tmp.input();
		system("cls");
		tmp.outputMenu(false);
		cout << "Do you want to add this dish to your menu? (0: No, 1: Yes) :";
		cin >> choice;
		while (cin.fail() || choice != 0 && choice != 1) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, try again" << endl;
			cout << "Your choice: ";
			cin >> choice;
		}
		pos = this->add(&tmp);
		obj.update(pos, 1);
		cout << "Successfully add " << endl;
		this->save();
		this->output();
		fout.open("./restaurant/menu/" + tmp.getID() + ".txt");
		tmp.save(fout);
		cout << "Do you want to add another dish? (0: No, 1: Yes): " << endl;
		cin >> choice;
		while (cin.fail() || choice != 0 && choice != 1) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, try again" << endl;
			cout << "Your choice: ";
			cin >> choice;
		}
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
			while (cin.fail() || choice < 0 || choice > menu.size() - 1) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Error, try again" << endl;
				cout << "Your choice: ";
				cin >> choice;
			}
			cin.ignore(256, '\n');
			string path = "./restaurant/menu/" + menu[choice1]->getID() + ".txt";
			bool re = this->deleteFile(path);
			if (re) {
				cout << "Delete successfully" << endl;
			}
			else {
				cout << "Can't delete" << endl;
			}
			menu.erase(menu.begin() + choice1);
			obj.update(choice1, 0);
			this->save();
			cout << "Do you want to delete any other dish? (0: No, 1: Yes): ";
			cin >> choice;
			while (cin.fail() || choice != 0 && choice != 1) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Error, try again" << endl;
				cout << "Your choice: ";
				cin >> choice;
			}
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
			while (cin.fail()||choice <0 || choice > menu.size() - 1) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Error, try again" << endl;
				cout << "Your dish index: ";
				cin >> choice1;
			}
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
		while (cin.fail() || choice != 0 && choice != 1) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, try again" << endl;
			cout << "Your choice: ";
			cin >> choice;
		}
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
vector<pair<int,int>> Menu::favor() {
	string inputpath = "./restaurant/DishOrdered";
	ifstream fin;
	int n = 0;
	vector<pair<int,int>> tmp;
	fin.open(inputpath);
	if (!fin.is_open()) {
		cout << "Can't open file" << endl;
	}
	else {
		int tmp1 = 0;
		while(fin >> tmp1) {
			pair<int, int> tmp2;
			tmp2.first = n;
			tmp2.second = tmp1;
			tmp.push_back(tmp2);
			n++;
		}
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (tmp[i].second < tmp[j].second) {
					pair<int, int> tmp1 = tmp[j];
					tmp[j] = tmp[i];
					tmp[i] = tmp1;
				}
			}
		}
		fin.close();
	}

	return tmp;
}
void Menu::iOutput() {
	this->load();
	this->output();
}
void Menu::iChangeDish() {
	this->load();
	this->changeDish();
}
void Menu::iNewDish() {
	this->load();
	this->newDish();
}
void Menu::iRemoveDish() {
	this->load();
	this->removeDish();
}