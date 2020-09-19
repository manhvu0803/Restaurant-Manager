#include "manager.hpp"
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <iomanip>

using namespace std;

namespace manager
{
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
    
    string toString2(int m, int d, int num)
    {
        string date;
        if (d < 10) date += '0';
        date += to_string(d);
        if (m < 10) date += '0';
        date += to_string(m);
        string sNum = to_string(num);
        while (sNum.length() < 6) sNum = '0' + sNum;
        return date + sNum;
    }

    bill::bill(int number, int h, int m, int s, vector<dish>& dishes):
        number(number),
        h(h), m(m), s(s),
        dishes(dishes)
    {};

    unique_ptr<bill> bill::getBill(int m, int d, int num)
    {    
        int number, hour, min, sec;
        char ch;
        ifstream file(dir + to_string(m) + "/" + toString(2020, m, d));
        if (!file.is_open()) {
            file.open(dir + to_string(m) + "/" + toString2(m, d, num));
            if (!file.is_open()) return unique_ptr<bill>();
        }
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
            char c = ' ';
            while (c == ' ') 
                c = file.get();            
            getline(file, d.name);
            d.name = c + d.name;
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
    void showSale(int day = 0, int m = 0)
    {    
        char choice;
        unordered_map<string, dish> dMap;
        long long total = 0;
        int lim = 12;
        int lim2 = 31;
        int start = day;
        string filename;
        if (day == 0) start = 1;
        else lim2 = day;
        if (m == 0) {
            m = 1;
            filename = "./" + to_string(day) + "-" + to_string(m) + ".csv";
        }
        else {
            lim = m;
            filename = "./" + to_string(m) + ".csv";
        }
        for (m = m; m <= lim; ++m)
            for (day = start; day <= lim2; ++day) 
                for (int j = 1; j < 10; ++j) {          
                    unique_ptr<bill> b = bill::getBill(m, day, j); 
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

    void saleMenu::showDateSale()
    {
        cout << "Sale of a day\n";
        int d, m;
        try {
            m = getMonth();
            d = getDate();
        }
        catch (const exception& e) {
            cerr << e.what() << '\n';
            return;
        }
        
        showSale(d, m);
    }

    void saleMenu::showMonthSale()
    {
        cout << "Sale of a month\n";
        int m, y;
        try {
            m = getMonth();
        }
        catch (const exception& e) {
            cerr << e.what() << '\n';
            return;
        }

        showSale(0, m);
    }

    void saleMenu::showYearSale()
    {
        cout << "Sale of a year\n";
        showSale();
    }

    saleMenu::saleMenu(): component("Sale manager")
    {        
        component::add(new ui::option(showDateSale, "Show sale of a day"));
        component::add(new ui::option(showMonthSale, "Show sale of a month"));
        component::add(new ui::option(showYearSale, "Show sale of a year"));    
    }
}