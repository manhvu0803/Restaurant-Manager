#include "manager.hpp"
#include <fstream>

using namespace std;

bill::bill(int number, int h, int m, int s, vector<dish>& dishes):
    number(number),
    h(h), m(m), s(s),
    dishes(dishes)
{};

unique_ptr<bill> bill::getBill(int y, int m, int d)
{    
    int number, h, m, s;
    char ch;
    ifstream file("restaurant/bill/" + to_string(9) + "/03-09-2020");
    cout << boolalpha << file.is_open() << '\n';
    file.ignore(9);
    file >> number;
    file.ignore(256, '\n');
    file.ignore(256, '\n');
    file.ignore(256, ' ');
    file >> h >> ch >> m >> ch >> s;
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

    return unique_ptr<bill>(new bill(number, h, m, s, dishes));
}

long bill::total()
{
    long sum = 0;
    for (auto i: dishes)
        sum += i.quantity * i.price;
    return sum;
}

// saleMenu
void saleMenu::showDateSale()
{
    int d, m, y;
    cout << "Year: ";
    if (!ui::input(cin, y) || y > 0) return;
    cout << "Month: ";
    if (!ui::input(cin, m) || m < 0 || m > 12) return;
    cout << "Day of month: ";
    if (!ui::input(cin, d) || d < 0 || d > 31) return;
    unique_ptr<bill> dateBill = bill::getBill(y, m, d);
}

void saleMenu::menu()
{
    //new ui::option(bind(&saleManger::, &t), "Do something");
}