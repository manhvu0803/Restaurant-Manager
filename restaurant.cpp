#include <iostream>
#include "essentials.hpp"
#include <cstdlib>
#include "sales/bill.hpp"
#include "sales/order.hpp"
#include "sales/discount.hpp"

using namespace std;

int main()
{
    ERROR_LOG &log = log.instantiate();
    srand(0);
    discount &disc = discount::instantiate();
    try
    {
        disc.add_promo();
    }
    catch (const char *msg)
    {
        log.LOG(msg);
    }
}