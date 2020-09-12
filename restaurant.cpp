#include <iostream>
#include "sales/essentials.hpp"
#include <cstdlib>

using namespace std;

int main()
{
    ERROR_LOG *log = log->instantiate();
    srand(0);
    try
    {
    }
    catch (const char *msg)
    {
        log->LOG(msg);
    }
    delete log;
}