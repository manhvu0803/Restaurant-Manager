#include "manager.hpp"
#include <fstream>
#include <iomanip>

using namespace std;

const std::string bill::dir = "restaurant/bill/";

string toString(int y, int m, int d)
{
    string date;
    if (d < 10) date += '0';
    date += to_string(d) + '-';
    if (m < 10) date += '0';
    date += to_string(m) + '-';
    date += to_string(y);
    return date;
}

bill::bill(int number, int h, int m, int s, vector<dish>& dishes):
    number(number),
    h(h), m(m), s(s),
    dishes(dishes)
{};

unique_ptr<bill> bill::getBill(int y, int m, int d)
{    
    int number, hour, min, sec;
    char ch;
    ifstream file(dir + to_string(m) + "/" + toString(y, m, d));
    if (!file.is_open()) return unique_ptr<bill>();
    file.ignore(9);
    file >> number;
    file.ignore(256, '\n');
    file.ignore(256, '\n');
    file.ignore(256, ' ');
    file >> hour >> ch >> min >> ch >> sec;
    file.ignore(256, '\n');
    file.ignore(256, '\n');
    file.ignore(256, '\n');

    vector<dish> dishes;
    int dishNum;
    while (file >> dishNum) {
        dish d;
        file >> d.id;
        while (ch < '0' || ch > '9') {
            if (ch != ' ' || (ch == ' ' && d.name[d.name.length() - 1] != ' ')) 
                d.name += ch;
            file.get(ch);
        }
        file >> d.quantity >> d.price;
        dishes.push_back(d);
    }

    return unique_ptr<bill>(new bill(number, hour, min, sec, dishes));
}

long bill::total() const
{
    long sum = 0;
    for (auto i: dishes)
        sum += i.quantity * i.price;
    return sum;
}

ostream& operator<<(ostream& stream, const bill& b)
{
    stream << "Bill number: " << b.number;
    stream << "Time: " << b.h << ':' << b.m << ':' << b.s << '\n';
    for (int i = b.dishes.size(); i >= 0; --i) 
        stream << b.dishes[i].name << setw(10) << b.dishes[i].quantity << setw(5) << b.dishes[i].quantity << '\n';
    stream << "Total: " << b.total() << '\n';
    return stream;
}

// saleMenu
void saleMenu::showDateSale()
{
    int d, m, y;
    cout << "Year: ";
    if (!ui::input(y) || y < 0) {
        cout << "Wrong year format\n";
        return;
    }
    cout << "Month: ";
    if (!ui::input(m) || m < 0 || m > 12) {
        cout << "Wrong month format\n";
        return;
    }
    cout << "Day of month: ";
    if (!ui::input(d) || d < 0 || d > 31) {
        cout << "Wrong date format";
        return;
    }   
    unique_ptr<bill> b = bill::getBill(y, m, d); 
    if (b) cout << *b;
    else cout << "Bill not found\n";
}

void saleMenu::menu()
{
    ui::component mainMenu;
    ui::option dateOpt(showDateSale, "Show sale of a day");
    mainMenu.add(dateOpt);
    mainMenu.show();
}