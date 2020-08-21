#include "bill.hpp"
#include <iostream>
#include <fstream>

using namespace std;

/**********************
 * BILL
**********************/

bill::~bill()
{
    stringstream path;
    path << "bill/" << Date;
    ofstream file(path.str().c_str());
    // In bill
    file.close();
}

void bill::AddData(const string &ID, const string &name, const double &price)
{
    int id_size = this->dish_IDs.size();
    for (int i = 0; i < id_size; ++i)
    {
        if (dish_IDs[i] == ID)
        {
            total_per_dish[i] += price;
            ++quantity[i];
            return;
        }
    }
    dish_names.emplace_back(name);
    dish_IDs.emplace_back(ID);
    quantity.emplace_back(1);
}

void bill::RemoveData(const string &ID, const double &price)
{
    int id_size = this->dish_IDs.size();
    for (int i = 0; i < id_size; ++i)
    {
        if (dish_IDs[i] == ID)
        {
            if (quantity[i] == 1)
            {
                dish_IDs.erase(dish_IDs.begin() + i);
                dish_names.erase(dish_names.begin() + i);
                total_per_dish.erase(total_per_dish.begin() + i);
            }
            else
            {
                --quantity[i];
                total_per_dish[i] -= price;
            }

            return;
        }
    }
}