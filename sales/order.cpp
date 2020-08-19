#include <iostream>
#include <windows.h>
#include "order.hpp"

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