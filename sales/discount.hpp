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
    vector<promo *> promos;

public:
    discount();
    ~discount();
    void add_voucher();
    void add_promo();
    bool use_voucher(const string &code);
    bool use_promo(const string &code);
};

class Code
{
protected:
    vector<string> code;
    int quantity = 0;
    date expiration_date;
    string name;
    vector<string> dish;
    int discount_value;

public:
    string code_generator();
    bool NewCode(const string &code);
};

class promo : public Code
{
public:
    promo() { throw "Cannot instantiate a voucher object withoud data!"; };
    promo(const string &path);
    void NewPromo();
    void ListDish();
};

class voucher : public Code
{
public:
    voucher() { throw "Cannot instantiate a voucher object withoud data!"; };
    voucher(const string &path);
    void NewVoucher();
    void ListDish();
    ~voucher();
};

#endif