#include "dish.h"



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
	Ingredients tmp1;
	vector<Ingredients> tmp2;
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
/*string Dish::generateID(int choice) {
	if (choice == 0) {
		for()
	}
	else {

	}
}*/