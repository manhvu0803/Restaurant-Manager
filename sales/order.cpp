#include <fstream>
#include <iomanip>
#include "order.hpp"
#include "../menu.h"
#include "PCH.hpp"
#include "bill.hpp"

using namespace std;

void order::update(const int &pos, const int &mode)
{
    bill_manager &tmp = bill_manager::instantiate();
    tmp.updateQuantNewDish(pos, mode);
}

order &order::instantiate()
{    
    static order instance;
    return instance;
}

void order::NewOrder()
{
    bill_manager &bill_m = bill_manager::instantiate();
    orders.emplace_back(bill_m.NewBill());
}

bool order::CompleteOrderInQueue()
{
    if (!orders.empty())
        return false;
    orders.pop_front();
    return true;
}

void order::displayNewestOrder()
{
    system("cls");
    if (orders.empty())
    {
        cout << "Empty!";
        system("pause");
        return;
    }
    (*orders.begin())->DisplayBill();
}

void order::displayOldestOrder()
{
    system("cls");
    if (orders.empty())
    {
        cout << "Empty!";
        system("pause");
        return;
    }
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