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
    static discount *instance;

public:
    discount();
    ~discount();
    void add_voucher();
};

class Code
{
protected:
    vector<string> code;

public:
    string code_generator();
    bool NewCode(const string &code);
};

class promo
{
};

class voucher : public Code
{
private:
    int quantity = 0;
    date expiration_date;
    vector<string> dish;
    string name;

public:
    voucher(){};
    voucher(const string &path);
    void NewVoucher();
    ~voucher();
};

#endif