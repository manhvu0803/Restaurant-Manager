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
    order(const order &other) = delete;
    order &operator=(const order &other) = delete;
    order *instantiate();
    void NewOrder();
};

#endif