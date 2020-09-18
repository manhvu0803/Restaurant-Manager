#include "dish.h"

#include <string>

// Dish
void Dish::add(Ingredients* a) {
	ings.push_back(a);
}
Dish::Dish(string id, string name, double cost) {
	this->id = id;
	this->name = name;
	this->price = cost;
}
string Dish::getID() {
	return id;
}
string Dish::getName() {
	return name;
}
void Dish::outputMenu() {
	cout << setw(10) << left << id << ": " << setw(20) << left << name << setw(10) << left << to_string(long int(price)) + " VND" << endl;
}
double Dish::getPrice() {
	return price;
}
void Dish::save(ofstream& fout) {
	fout << id << endl;
	fout << name << endl;
	fout << to_string(long int(price)) << endl;
	for (int i = 0; i < ings.size(); i++) {
		ings[i]->exp(fout, false);
	}
}
void Dish::addIngsToDish(vector<Ingredients> a) {
	int choice = 1;
	int Amount = 0;
	date tmp;

	cout << "Ingredients list :" << endl;
	for (int i = 0; i < a.size(); i++) {
		cout << setw(10) << left << id << ": " << setw(20) << left << name << endl;
	}
	cout << "Choose the ingredients that you need " << endl;
	while (choice == 1) {
		cout << "The index of ingredient: ";
		cin >> choice;
		cout << "The amount you need (" << a[choice].getUnit() << "): ";
		cin >> Amount;
		int Id = a[choice].getID();
		string Name = a[choice].getName();
		string Unit = a[choice].getUnit();
		Ingredients* n = new Ingredients(Id, Name, Amount, Unit, tmp, -1);
		this->add(n);
		cout << "You want to add another ingredients ? (0: No, 1: Yes)" << endl;
		cin >> choice;
	}
}
void Dish::input() {
	int choice;
	string Name,Id;
	double Price;
	Storage tmp;
	cout << "Please input dish info: " << endl;
	cout << "Type of dish:" << endl;
	cout << "(0)FD" << endl << "(1)DK" << endl;
	cout << "Your choice: ";
	cin >> choice;
	cin.ignore(256, '\n');
	cout << "Name of the dish: ";
	getline(cin, Name);
	Id = this->generateID(choice);
	cout << "Price of the dish: ";
	cin >> Price;
	while (Price < 0 || cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Error, try again" << endl;
		cout << "Price of the dish: ";
		cin >> Price;
	}
	this->addIngsToDish(tmp.getStorage());
	
}
string Dish::generateID(int choice) {
	ifstream fin;
	int flag = -2;
	string tmp1;
	vector<string> tmp;
	size_t found;
	fin.open("./restaurant/meunu/dishes.txt");
	if (!fin.is_open()) {
		cout << "Can't open file menu" << endl;
	}
	else {
		while (getline(fin, tmp1)) {
			tmp.push_back(tmp1);
		}
		fin.close();
	}
	if (choice == 0) {
		for (int i = 0; i < tmp.size();i++) {
			found = tmp[i].find("DK");
			if (found != string::npos) {
				flag = i - 1;
				break;
			}
		}
		if (flag == -2) {
			return "FD" + newID(tmp[tmp.size() - 1]);
		}
		else {
			return "FD" + newID(tmp[flag]);
		}
	}
	else {
		return "DK" + newID(tmp[tmp.size() - 1]);
	}
}
string Dish::newID(string prevID) {
	string str = prevID.substr(2, 3);
	int number = stoi(str) + 1 ;
	return NtoS(number);

}
string Dish::NtoS(int const& number) {
	if (number < 10) {
		return "00" + to_string(number);
	}
	else if (number < 100) {
		return "0" + to_string(number);
	}
	else {
		return to_string(number);
	}
}
void Dish::change() {
	int choice, choice1, amnt;
	Ingredients tmp;
	ofstream fout;
	cout << "Choose the aspect you want to change: " << endl;
	cout << "(0) Price" << endl << "(1) Ingredients" << endl;
	cout << "Your choice: ";
	cin >> choice;
	cin.ignore(256, '\n');
	if (choice == 0) {
		cout << "This is the price: " << this->getPrice() << " VND" << endl;
		cout << "Enter the new price you want: ";
		cin >> this->price;
		cout << "The price has been change" << endl;
		string path = "./restaurant/menu/" + this->getID() + ".txt";
		fout.open(path);
		if (fout.is_open()) {
			this->save(fout);
			cout << "Save successfully" << endl;
			fout.close();
		}
		else {
			cout << "Cant open file dish" << endl;
		}
	}
	else {
		for (int i = 0; i < ings.size(); i++) {
			cout << setw(3) << left << "(" + to_string(i) + ")" << setw(17) << left << ings[i]->getName() 
				<< setw(8) << left << ings[i]->getAmount() << setw(12) << left << ings[i]->getUnit() << endl;
		}
		cout << "Choose the function you want to do: " << endl;
		cout << "(0) Add ingredients" << endl << "(1) Remove ingredients" << endl << "(2) Change the amount of ingredients" << endl;
		cout << "Your choice: ";
		cin >> choice;
			cout << "Choose the index of the ingredient you want to change " << endl;
			cout << "Your choice: ";
			cin >> choice1;
			cin.ignore(256, '\n');
			ings[choice1]->print();
		if(choice == 2){
			cout << "New amount: ";
			cin >> amnt;
			while (cin.fail() || amnt <= 0) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Error, try again" << endl;
				cout << "New amount: ";
				cin >> amnt;
			}
			ings[choice1]->changeAmt(amnt);
		}
		else if (choice1 == 0) {
			ings.push_back(this->inputIng());
			string path = "./restaurant/menu/" + this->getID() + ".txt";
			fout.open(path);
			if (fout.is_open()) {
				this->save(fout);
				cout << "Save successfully" << endl;
				fout.close();
			}
			else {
				cout << "Cant open file dish" << endl;
			}
		}
		else {
			ings.erase(ings.begin() + choice1);
			string path = "./restaurant/menu/" + this->getID() + ".txt";
			fout.open(path);
			if (fout.is_open()) {
				this->save(fout);
				cout << "Save successfully" << endl;
				fout.close();
			}
			else {
				cout << "Cant open file dish" << endl;
			}
		}

	}
}
Ingredients* Dish::inputIng() {
	Storage tmp;
	Ingredients* tmp1;
	date tmp2;
	int choice,amnt;
	tmp.imp();
	cout << "The ingredients our storage has: " << endl;
	tmp.print();
	cout << "Enter the index of the ingredient you want to choose: ";
	cin >> choice;
	cout << "The amount you want: ";
	cin >> amnt;
	tmp1 = new Ingredients(tmp[choice].getID(), tmp[choice].getName(), amnt, tmp[choice].getUnit(), tmp2, 0);
	return tmp1;
}