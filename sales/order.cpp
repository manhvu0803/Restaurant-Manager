#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include "order.hpp"
#include "menu.h"
#include "essentials.hpp"

using namespace std;

order::order()
{
    ifstream file("DishOrdered");
    if (!file.is_open())
    {
        ERROR_LOG *log = log->instantiate();
        log->LOG("File DishOrdered is missing");
        throw "File DishOrdered is missing!";
    }
    int tmp;
    while (!file.eof())
    {
        file >> tmp;
        quantity.emplace_back(tmp);
    }
    quantity.shrink_to_fit();
    file.close();
}

void order::update(const int &pos, const int &mode)
{
    if (mode)
        quantity.emplace(quantity.begin() + pos, 0);
    else
        quantity.erase(quantity.begin() + pos);
}

order::~order()
{
    ofstream file("DishOrdered");
    for (int i = 0; i < quantity.size() - 1; ++i)
        file << quantity[i] << endl;
    file << quantity[quantity.size() - 1];
    file.close();
    for (auto &i : bills)
        delete i;
}

order *order::instantiate()
{
    if (!instance)
        instance = new order;
    return instance;
}

order *order::instance = nullptr;

void order::NewOrder()
{
    order::instantiate();
    bill *new_bill = new bill;
    if (bills.size() >= 100)
        this->~order();
    int dish;
    do
    {
        system("cls");
        Menu *rest_menu = rest_menu->instantiate();
        rest_menu->output();
        cout << "0. Finalize order\n";
        cout << "-1. Cancel order\n";
        cout << "Option: ";
        int opt;
        while (!(cin >> dish) || dish < 1 || dish > rest_menu->getMenu().size() + 1)
        {
            cout << "Invalid!\n";
            cout << "Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
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
            new_bill->AddData(rest_menu->getMenu()[dish - 1]->getID(),
                              rest_menu->getMenu()[dish - 1]->getName(), rest_menu->getMenu()[dish - 1]->getPrice());
            UpdateDishQuant(dish - 1, opt);
        }
        else if (opt == 2)
        {
            new_bill->RemoveData(rest_menu->getMenu()[dish - 1]->getID(), rest_menu->getMenu()[dish - 1]->getPrice());
            UpdateDishQuant(dish - 1, opt);
        }
        else
            dish = 1;
    } while (dish && dish != -1);
    if (dish == -1)
        delete new_bill;
    else
    {
        bills.emplace_back(new_bill);
        orders.emplace_back(new_bill);
    }
}

void order::UpdateDishQuant(const int &index, const int &mode)
{
    if (mode == 1)
        ++quantity[index];
    else
        --quantity[index];
}

const vector<int> &order::getOrderedDishQuantity()
{
    return quantity;
}

bool order::CompleteOrderInQueue()
{
    if (!orders.size())
        return false;
    orders.pop_front();
    return true;
}

void order::displayNewestOrder()
{
    system("cls");
    (*orders.begin())->DisplayBill();
}

void order::displayOldestOrder()
{
    system("cls");
    (*orders.end())->DisplayBill();
}

void order::ListCurrentOrders()
{
    system("cls");
    cout << "Orders list";
    int count = 1;
    for (auto &i : orders)
    {
        cout << left << count << setw(3) << "." << i;
        ++count;
    }
}