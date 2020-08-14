#ifndef DISCOUNT_HPP
#define DISCOUNT_HPP

#include <iostream>
#include "essentials.hpp"

using namespace std;

/**********************
 * Discount
 * discount theo mua(4)
 * discount theo voucher(4)
 * discount theo promote code(4)
 * discount tung mon an
**********************/

/**********************
 * Voucher
 * discount voi so tien nhat dinh
 * so luong voucher tuy theo so luong code generate duoc
 * co han su dung cho tung code
 * tao bang random va luu vao file(moi khi chuong trinh chay thi load lai)
**********************/

class discount
{
private:
    vector<voucher *> vouchers;
    discount();
    static discount *instance;

public:
    ~discount();
    void add_voucher();
    discount *Instantiate();
};

class voucher
{
private:
    vector<string> code;
    u_int quantity = 0;
    string code_generator();
    date expiration_date;
    vector<string> dish;

public:
    voucher();
    voucher(const string &path);
    ~voucher();
    void Discount();
    void AddDiscount();
    void RemoveDiscount();
};

#endif