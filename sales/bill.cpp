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

bool bill::AddData(const string &ID, const string &name)
{
    int id_size = this->dishes_IDs.size();
    for (int i = 0; i < id_size; ++i)
    {
        if (dishes_IDs[i] == ID)
            ++quantity[i];
        else
        {
            dish_names.push_back(name);
            dishes_IDs.push_back(ID);
            quantity.push_back(1);
        }
    }
}