#include "order.hpp"
#include <iostream>
#include <windows.h>

using namespace std;

order::~order()
{
    for (auto &i : bills)
        delete i;
    bills.clear();
}

void order::NewOrder()
{
    system("cls");
    if (bills.size() >= 100)
        this->~order();
}