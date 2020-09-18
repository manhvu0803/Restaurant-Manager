#include <iostream>
#include "essentials.hpp"
#include <cstdlib>
#include "sales/bill.hpp"
#include "sales/order.hpp"

using namespace std;

int main()
{
    ERROR_LOG &log = log.instantiate();
    srand(0);
    try
    {
    }
    catch (const char *msg)
    {
        log.LOG(msg);
    }
}