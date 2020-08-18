#ifndef ORDER_HPP
#define ORDER_HPP

#include "bill.hpp"
#include <vector>

using namespace std;

class order
{
private:
    order(){};
    static order *instance;
    vector<bill *> bills;

public:
    ~order();
    order *instantiate()
    {
        if (!instance)
            instance = new order;
        return instance;
    }
    void NewOrder();
};

order *order::instance = nullptr;

#endif