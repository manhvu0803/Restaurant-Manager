#ifndef DISCOUNT_HPP
#define DISCOUNT_HPP

#include <vector>
#include <iostream>
#include "../essentials.hpp"

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
using namespace std;

class Code
{
protected:
    vector<string> code;
    int quantity = 0;
    date expiration_date;
    string name;
    vector<string> dish; //ID
    int discount_value = 0;

public:
    string code_generator();
    bool NewCode(const string &code);
    void Info();
    bool CompareCode(const string &code);
    const date &getExpDate();
    void ListDish();
};

class promo : public Code
{
public:
    promo(){};
    promo(const string &file_name);
    void NewPromo();
    void Apply(double &totals);
    ~promo();
};

class voucher : public Code
{
public:
    voucher(){};
    voucher(const string &file_name);
    void NewVoucher();
    void Apply(const vector<string> &dish_IDs, vector<double> &totals, double &total);
    ~voucher();
};

//use voucher and promo
//must check if use_voucher() and use_promo() return actual object
class discount
{
private:
    vector<voucher *> vouchers;
    vector<promo *> promos;

public:
    discount();
    ~discount();
    discount(const discount &other) = delete;
    discount &operator=(const discount &other) = delete;
    void add_voucher();
    void add_promo();
    voucher *use_voucher(const string &code);
    promo *use_promo(const string &code);
    static discount &instantiate();
};

#endif