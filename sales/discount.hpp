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
********************** /

/**********************
 * Promo code
 * discount theo phan tram
 * khong gioi han so luong promo
 * 1 code duy nhat de nho de nhap
 * han su dung chung
**********************/

class discount
{
protected:
    double discount_value = 0;
    date expired_date;
    vector<string> dish;

public:
    void Discount() = 0;
    void AddDiscount() = 0;
    void RemoveDiscount() = 0;
};

class voucher : public discount
{
private:
    vector<string> code;
    u_int quantity = 0;
    string code_generator();

public:
    voucher();
    ~voucher();
    void Discount();
    void AddDiscount(const int &num_of_voucher);
    void RemoveDiscount();
}

#endif