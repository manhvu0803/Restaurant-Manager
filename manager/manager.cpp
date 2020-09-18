#include "manager.hpp"
#include <fstream>
#include <stdexcept>
#include <unordered_map>
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
        file >> d.id >> d.quantity >> d.price;        
        while (file.peek() == ' ') 
            file.get();
        getline(file, d.name);
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
    stream << "Bill number: " << b.number << '\n';
    stream << "Time: " << b.h << ':' << b.m << ':' << b.s << '\n';
    stream << left << setw(20) << "Dish" << setw(10) << "Quantity" << "Price\n";
    for (auto i: b.dishes) 
        stream << setw(20) << i.name << setw(10) << i.quantity << setw(10) << i.price << '\n';
    stream << "Total: " << b.total() << '\n' << right;
    return stream;
}

int getYear()
{
    int y;
    cout << "Year: ";
    if (!ui::input(y) || y < 0) throw invalid_argument("Wrong year format");
    return y;
}

int getMonth()
{
    int m;
    cout << "Month: ";
    if (!ui::input(m) || m < 0 || m > 12) throw invalid_argument("Wrong month format\n");        
    return m;
}

int getDate()
{
    int d;
    cout << "Day of month: ";
    if (!ui::input(d) || d < 0 || d > 31) throw invalid_argument("Wrong date format");        
    return d;
}


// saleMenu
void saleMenu::showDateSale()
{
    cout << "Sale of a day\n";
    int d, m, y;
    try {
        y = getYear();
        m = getMonth();
        d = getDate();
    }
    catch (const exception& e) {
        cerr << e.what() << '\n';
        return;
    }    
        
    unique_ptr<bill> b = bill::getBill(y, m, d); 
    if (b) cout << *b;
    else cout << "Bill not found\n";
}

void showSale(int y, int m = 0)
{    
    char choice;
    unordered_map<string, dish> dMap;
    long long total = 0;
    int lim = 12;
    string filename;
    if (m == 0) {
        m = 1;
        filename = "./" + to_string(m) + "-" + to_string(y) + ".csv";
    }
    else {
        lim = m;
        filename = "./" + to_string(y) + ".csv";
    }        
    for (m = m; m <= lim; ++m)
        for (int i = 1; i <= 31; ++i) {          
            unique_ptr<bill> b = bill::getBill(y, m, i); 
            if (b) {
                for (auto d: b->dishes) {
                    auto ite = dMap.find(d.name);
                    if (ite == dMap.end()) dMap.emplace(d.name, d);
                    else ite->second.quantity += d.quantity;
                }
                total += b->total();
            };
        }

    cout << left << setw(20) << "Dish" << setw(10) << "Quantity" << "Price\n";
    for (auto i: dMap)         
        cout << setw(20) << i.second.name << setw(10) << i.second.quantity << setw(10) << i.second.price << '\n';
    cout << "Total: " << total << right << '\n';

    cout << "Do you want to export to csv file? (Y/N): \n";
    ui::input(choice);
    if (choice == 'Y' || choice == 'y') {
        ofstream file(filename);
        if (!file.is_open()) cout << "Can't create file\n";
        file << "Dish,Quantity,Price\n";
        for (auto i: dMap)         
            file << i.second.name << ',' << i.second.quantity << ',' << i.second.price << '\n';
        file << "Total," << total;
    }
}

void saleMenu::showMonthSale()
{
    cout << "Sale of a month\n";
    int m, y;
    try {
        y = getYear();
        m = getMonth();
    }
    catch (const exception& e) {
        cerr << e.what() << '\n';
        return;
    }

    showSale(y, m);
}

void saleMenu::showYearSale()
{
    cout << "Sale of a year\n";
    int y;
    try {
        y = getYear();
    }
    catch (const exception& e) {
        cerr << e.what() << '\n';
        return;
    }

    showSale(y);
}

saleMenu::saleMenu(): component("Sale manager")
{        
    component::add(new ui::option(showDateSale, "Show sale of a day"));
    component::add(new ui::option(showMonthSale, "Show sale of a month"));
    component::add(new ui::option(showYearSale, "Show sale of a year"));    
}