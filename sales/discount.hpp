#ifndef DISCOUNT_HPP
#define DISCOUNT_HPP

#include <vector>
#include <iostream>
#include "essentials.hpp"

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

class Code
{
protected:
    std::vector<std::string> code;
    int quantity = 0;
    date expiration_date;
    std::string name;
    std::vector<std::string> dish; //ID
    int discount_value;

public:
    std::string code_generator();
    bool NewCode(const std::string &code);
    int getDiscountValue();
    bool CompareCode(const std::string &code);
    void ListDish();
};

class promo : public Code
{
public:
    promo(){};
    promo(const std::string &file_name);
    void NewPromo();
    void Apply(double &totals);
    ~promo();
};

class voucher : public Code
{
public:
    voucher(){};
    voucher(const std::string &file_name);
    void NewVoucher();
    void Apply(const vector<string> &dish_IDs, vector<double> &totals, double &total);
    ~voucher();
};

//use voucher and promo
//must check if use_voucher() and use_promo() return actual object
class discount
{
private:
    std::vector<voucher *> vouchers;
    std::vector<promo *> promos;
    static discount *instance;

public:
    discount();
    ~discount();
    discount(const discount &other) = delete;
    discount &operator=(const discount &other) = delete;
    void add_voucher();
    void add_promo();
    voucher *use_voucher(const std::string &code);
    promo *use_promo(const std::string &code);
    static discount *instantiate();
};

#endif