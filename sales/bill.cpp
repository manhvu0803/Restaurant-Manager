#include "bill.hpp"
#include <iostream>

using namespace std;

/**********************
 * BILL
**********************/

bool bill::AddOrder(const string &ID, const string &name)
{
    int id_size = this->dishes_IDs.size();
    for (int i = 0; i < id_size; ++i)
    {
        if (dishes_IDs[i] == ID)
            ++quantity[i];
    }
    else
    {
        dish_names.push_back()
    }

}