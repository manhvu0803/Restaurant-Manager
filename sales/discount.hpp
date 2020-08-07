#ifndef DISCOUNT_HPP
#define DISCOUNT_HPP

#include <iostream>
#include "essentials.hpp"

using namespace std;

/**********************
 * VOUCHER
 * Use code to verify
 * CheckVoucher checks expired date and entered code
 * Aggregation
**********************/
class voucher
{
private:
    date expired_date;
    u_int quantity;
    double discount_value;
    string code;

public:
    void Discount();
    void NewVoucher();
    bool CheckVoucher(const string &code);
};

#endif