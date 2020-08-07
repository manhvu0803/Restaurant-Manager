#ifndef BILL_CPP
#define BILL_CPP

#include "essentials.hpp"

class bill
{
private:
    date Date;
    double Total;

public:
    bool AddDish();
    void calculate();

public:
};

#endif