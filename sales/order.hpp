#ifndef ORDER_HPP
#define ORDER_HPP

#include <vector>
#include <list>
#include "bill.hpp"

using namespace std;

class order
{
private:
    order(){};
    static order *instance;
    list<bill *> orders;

public:
    order(const order &other) = delete;
    order &operator=(const order &other) = delete;
    static order *instantiate();
    void NewOrder();
    void update(const int &pos, const int &mode);
    bool CompleteOrderInQueue();
    void displayNewestOrder();
    void displayOldestOrder();
    void ListCurrentOrders();
};

#endif