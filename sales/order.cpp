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
    if (!orders.size())
    {
        cout << "Empty!\n";
        system("pause");
        return;
    }
    (*orders.begin())->DisplayBill();
}

void order::displayOldestOrder()
{
    system("cls");
    if (!orders.size())
    {
        cout << "Empty!\n";
        system("pause");
        return;
    }
    (*orders.rbegin())->DisplayBill();
}

void order::ListCurrentOrders()
{
    system("cls");
    cout << "Orders list";
    int count = 1;
    if (!orders.size())
    {
        cout << "Empty!\n";
        return;
    }
    for (auto &i : orders)
    {
        cout << left << setw(5) << count << i;
        ++count;
    }
}