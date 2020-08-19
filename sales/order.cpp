#include <iostream>
#include <windows.h>
#include "order.hpp"
#include "menu.h"

using namespace std;

order::~order()
{
    for (auto &i : bills)
        delete i;
    bills.clear();
}

order *order::instantiate();
{
    if (!instance)
        instance = new order;
    return instance;
}

order *order::instance = nullptr;

void order::NewOrder()
{
    bill *new_bill = new bill;
    if (bills.size() >= 100)
        this->~order();
    int tmp;
    do
    {
        system("cls");
        Menu *rest_menu = rest_menu->instantiate();
        rest_menu->output();
        cout << "0. Finalize order\n";
        cout << "-1. Cancel order\n";
        cout << "Option: ";
        while (!(cin >> tmp) || tmp < 1 || tmp > rest_menu->getMenu().size() + 1)
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
        while (!(cin >> tmp) || tmp < 0 || tmp > 2)
        {
            cout << "Invalid!\n";
            cout << "Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        if (tmp == 1)
            new_bill->AddData(rest_menu->getMenu()[tmp - 1]->getID(), rest_menu->getMenu()[tmp - 1]->getName());
        else if (tmp == 2)
            new_bill->RemoveData(rest_menu->getMenu()[tmp - 1]->getID());
        else
            tmp = 1;
    } while (tmp && tmp != -1);
    if (tmp == -1)
        delete new_bill;
    else
        bills.emplace_back(new_bill);
}