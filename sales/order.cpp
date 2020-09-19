#include <fstream>
#include <iomanip>
#include "order.hpp"
#include "../menu.h"
#include "PCH.hpp"
#include "bill.hpp"

using namespace std;

void order::update(const int &pos, const int &mode)
{
    bill_manager::instantiate()->updateQuantNewDish(pos, mode);
}

order &order::instantiate()
{    
    static order instance;
    return instance;
}

order *order::instance = nullptr;

void order::NewOrder()
{
    bill_manager *bill_m = bill_manager::instantiate();
    orders.emplace_back(bill_m->NewBill());
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