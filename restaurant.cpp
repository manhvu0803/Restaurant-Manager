#include <iostream>
#include "essentials.hpp"
#include <cstdlib>
#include "sales/bill.hpp"
#include "sales/order.hpp"
#include "sales/discount.hpp"
#include "menu.h"
#include <windows.h>

using namespace std;

int main()
{
    Menu &menu = Menu::instantiate();
    menu.load();
    ERROR_LOG &log = log.instantiate();
    srand(time(0));
    discount &disc = discount::instantiate();
    bill_manager &billMan = bill_manager::instantiate();
    try
    {
        bill *tmp = billMan.FindBill("1909000003");
        if (!tmp)
            cout << "NO\n";
        else
            tmp->DisplayBill();
    }
    catch (const char *msg)
    {
        log.LOG(msg);
    }
    // menu.newDish();
    system("pause");
}