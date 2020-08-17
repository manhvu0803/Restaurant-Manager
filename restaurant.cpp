#include <iostream>
#include "sales/essentials.hpp"

using namespace std;

int main()
{
    try
    {
    }
    catch (const char *msg)
    {
        Clog.crash_log(msg);
    }
}