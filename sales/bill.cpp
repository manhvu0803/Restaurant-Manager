#include "bill.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include "PCH.hpp"
#include <cstdlib>
#include "../menu.h"
#include "order.hpp"
#include "discount.hpp"

using namespace std;

/**********************
 * BILL MANAGER
**********************/
bill *bill_manager::FindBill(const string &bill_no)
{
    for (auto &i : old_bills)
        if (bill_no == i->getBillNo())
            return i;
    for (auto &i : bills)
    {
        if (bill_no == i->getBillNo())
            return i;
    }
    stringstream path;
    string folder_name;
    int month;
    path << bill_no.substr(2, 2);
    path >> month;
    path << "";
    date tmp_d;
    path << "../restaurant/bill/" << month << "/" << bill_no.substr(0, 2) << "-" << bill_no.substr(2, 2) << "-" << tmp_d.y;
    path << "/" << bill_no;
    try
    {
        old_bills.emplace_back(new bill(path.str()));
        return old_bills.back();
    }
    catch (...)
    {
        return nullptr;
    }
}

bill_manager &bill_manager::instantiate()
{
    static bill_manager instance;
    return instance;
}

bill *bill_manager::NewBill()
{
    bill *new_bill = new bill;
    if (bills.size() >= 100)
        this->~bill_manager();
    int dish;
    do
    {
        system("cls");
        Menu &rest_menu = Menu::instantiate();
        rest_menu.output();
        cout << "0. Finalize order\n";
        cout << "-1. Cancel order\n";
        cout << "Option: ";
        int opt;
        while (!(cin >> dish) || dish < 1 || dish > rest_menu.getMenu().size() + 1)
        {
            cout << "Invalid!\n";
            cout << "Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        do
        {
            system("cls");
            cout << rest_menu.getMenu()[dish - 1]->getID();
            cout << " " << rest_menu.getMenu()[dish - 1]->getName() << endl;
            cout << "1. Add\n";
            cout << "2. Remove\n";
            cout << "0. Exit\n";
            cout << "Option: ";
            while (!(cin >> opt) || opt < 0 || opt > 2)
            {
                cout << "Invalid!\n";
                cout << "Try again: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            if (opt == 1)
            {
                new_bill->AddDish(rest_menu.getMenu()[dish - 1]->getID(),
                                  rest_menu.getMenu()[dish - 1]->getName(), rest_menu.getMenu()[dish - 1]->getPrice());
                UpdateDishQuant(dish - 1, opt);
                income += rest_menu.getMenu()[dish - 1]->getPrice();
            }
            else if (opt == 2)
            {
                if (new_bill->RemoveDish(rest_menu.getMenu()[dish - 1]->getID(), rest_menu.getMenu()[dish - 1]->getPrice()))
                {
                    UpdateDishQuant(dish - 1, opt);
                    income -= rest_menu.getMenu()[dish - 1]->getPrice();
                }
                else
                {
                    system("cls");
                    cout << "This dish has been removed!\n";
                    system("pause");
                }
            }
        } while (opt);
    } while (dish && dish != -1);
    if (dish == -1)
        delete new_bill;
    else
    {
        new_bill->applyDiscount();
        bills.emplace_back(new_bill);
        return new_bill;
    }
    return nullptr;
}

bill_manager::bill_manager()
{
    ifstream file("./restaurant/DishOrdered");
    if (!file.is_open())
        throw "File DishOrdered is missing!";
    int tmp;
    while (!file.eof())
    {
        file >> tmp;
        quantity.emplace_back(tmp);
    }
    quantity.shrink_to_fit();
    file.close();
}

void bill_manager::updateQuantNewDish(const int &pos, const int &mode)
{
    if (mode)
    {
        if (pos >= quantity.size() - 1)
            quantity.emplace_back(0);
        quantity.emplace(quantity.begin() + pos, 0);
    }
    else
    {
        if (pos >= quantity.size() - 1)
            return;
        quantity.erase(quantity.begin() + pos);
    }
}

bill_manager::~bill_manager()
{
    ofstream file("./restaurant/DishOrdered");
    for (int i = 0; i < quantity.size() - 1; ++i)
        file << i << endl;
    file << quantity[quantity.size() - 1];
    file.close();
    for (auto &i : bills)
        delete i;
}

void bill_manager::UpdateDishQuant(const int &index, const int &mode)
{
    if (mode == 1)
        ++quantity[index];
    else
        --quantity[index];
}

/**********************
 * BILL
**********************/
u_int bill::count = 0;

bill::bill()
{
    Total = 0;
    date tmp;
    string s_tmp;
    stringstream name;
    name << tmp;
    name << s_tmp;
    bill_no += name.str().substr(0, 2);
    bill_no += name.str().substr(2, 2);
    u_int count_t = count;
    int count_l = 0;
    while (count_t)
    {
        count_t /= 10;
        ++count_l;
    }
    count_l -= 6 - count_l;
    for (int i = 0; i < count_l; ++i)
        bill_no += "0";
    bill_no += count;
}

bill::bill(const string &bill_path)
{
    ifstream file(bill_path);
    if (!file.is_open())
    {
        string tmp;
        tmp = "Cannot open";
        tmp += bill_path;
        throw tmp.c_str();
    }
    file.seekg(9, ios::beg);
    getline(file, bill_no);
    skipchars(file, 6);
    string tmp;
    getline(file, tmp);
    Date = ConvertFromString(tmp);
    skipchars(file, 6);
    getline(file, tmp);
    Date.addTime(tmp);
    getline(file, tmp);
    getline(file, tmp);
    while (file.peek() != '\n')
    {
        skipchars(file, 5);
        file >> tmp;
        dish_IDs.emplace_back(tmp);
        int i_tmp;
        file >> i_tmp;
        quantity.emplace_back(i_tmp);
        double d_tmp;
        file >> d_tmp;
        total_per_dish.emplace_back(d_tmp);
        while (file.peek() == ' ')
            file.get();
        getline(file, tmp);
        dish_names.emplace_back(tmp);
    }
    skipchars(file, 6);
    file >> Total;
    file.close();
}

bill::~bill()
{
    stringstream path;
    path << "../restaurant/bill/" << Date.m << "/" << Date << "/" << bill_no;
    ofstream file(path.str());
    if (!file.is_open())
    {
        path << "";
        path << "../restaurant/bill/" << Date.m << "/" << Date;
        CreateDirectory(path.str().c_str(), NULL);
        path << "../restaurant/bill/" << Date.m << "/" << Date << "/" << bill_no;
        file.open(path.str());
    }
    file << "BILL NO: " << bill_no << endl;
    file << "DATE: " << Date << endl;
    file << "TIME: " << Date.GetTime() << endl;
    file << "DISHES:\n";
    file << left << setw(5) << "NO"
         << left << setw(15) << "ID"
         << left << setw(8) << "QUANT"
         << left << setw(15) << "PRICE"
         << "NAME" << endl;
    for (int i = 1; i <= dish_IDs.size(); ++i)
    {
        file << left << setw(5) << i
             << left << setw(15) << dish_IDs[i]
             << left << setw(8) << quantity[i]
             << left << setw(15) << total_per_dish[i]
             << dish_names[i] << endl;
    }
    file << endl
         << "TOTAL: " << Total;
    file.close();
}

void bill::AddDish(const string &ID, const string &name, const double &price)
{
    int id_size = this->dish_IDs.size();
    for (int i = 0; i < id_size; ++i)
    {
        if (dish_IDs[i] == ID)
        {
            total_per_dish[i] += price;
            Total += price;
            ++quantity[i];
            return;
        }
    }
    dish_names.emplace_back(name);
    dish_IDs.emplace_back(ID);
    quantity.emplace_back(1);
}

bool bill::RemoveDish(const string &ID, const double &price)
{
    int id_size = this->dish_IDs.size();
    for (int i = 0; i < id_size; ++i)
    {
        if (dish_IDs[i] == ID)
        {
            if (quantity[i] == 1)
            {
                dish_IDs.erase(dish_IDs.begin() + i);
                dish_names.erase(dish_names.begin() + i);
                total_per_dish.erase(total_per_dish.begin() + i);
            }
            else
            {
                --quantity[i];
                total_per_dish[i] -= price;
            }
            Total -= price;
            return true;
        }
    }
    return false;
}

void bill::DisplayBill()
{
    cout << "BILL NO: " << bill_no << endl;
    cout << "DATE: " << Date << endl;
    cout << "DISHES:\n";
    cout << left << setw(5) << "NO"
         << left << setw(15) << "ID"
         << left << setw(8) << "QUANT"
         << left << setw(15) << "PRICE"
         << "NAME" << endl;
    for (int i = 1; i <= dish_IDs.size(); ++i)
    {
        cout << left << setw(5) << i
             << left << setw(15) << dish_IDs[i]
             << left << setw(8) << quantity[i]
             << left << setw(15) << total_per_dish[i]
             << dish_names[i] << endl;
    }
    cout << endl
         << "TOTAL: " << Total;
}

const string &bill::getBillNo() const
{
    return bill_no;
}

void bill::applyDiscount()
{
    discount &disc = discount::instantiate();
    int opt;
MENU:
    system("cls");
    cout << "1. Promo\n";
    cout << "2. Voucher\n";
    cout << "0. Exit\n";
    while (!(cin >> opt) || opt < 0 || opt > 2)
    {
        cout << "Invalid!\n";
        cout << "Try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    string tmp;
    if (opt == 1)
    {
        system("cls");
        cout << "code: ";
        cin >> tmp;
        promo *Promo = disc.use_promo(tmp);
        if (!Promo)
        {
            system("cls");
            cout << "Invalid code!\n\n";
            system("pause");
            goto MENU;
        }
        system("cls");
        Promo->Info();
        Promo->Apply(Total);
        cout << "Applied successfully!\n";
        system("pause");
    }
    if (opt == 2)
    {
        system("cls");
        cout << "code: ";
        cin >> tmp;
        voucher *Voucher = disc.use_voucher(tmp);
        if (!Voucher)
        {
            system("cls");
            cout << "Invalid code!\n\n";
            system("pause");
            goto MENU;
        }
        Voucher->Apply(dish_IDs, total_per_dish, Total);
    }
}