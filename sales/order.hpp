#ifndef ORDER_HPP
#define ORDER_HPP

#include "bill.hpp"
#include <vector>

using namespace std;

class order
{
private:
    order();
    static order *instance;
    vector<bill *> bills;
    vector<int> quantity;

public:
    ~order();
    order(const order &other) = delete;
    order &operator=(const order &other) = delete;
    order *instantiate();
    void NewOrder();
    void UpdateDishQuant(const int &index, const int &mode);
    void update(const int &pos, const int &mode);
    const vector<int> &getOrderedDishQuantity();
};

#endif