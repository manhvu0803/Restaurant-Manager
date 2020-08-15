#ifndef BILL_CPP
#define BILL_CPP

#include "essentials.hpp"
#include <iostream>
#include <vector>

using namespace std;

/*********************
 * BILL
 * so luong cac mon an duoc dat
 * ten cac mon an duoc dat
 * so hoa don
 * tinh tong tien
 * apply giam gia
 * in hoa don ra man hinh
 * xuat hoa don ra file (ten: ngay + so thu tu)
 * ghi chu doanh thu trong ngay
*********************/

/*********************
 * 
*********************/
class bill
{
private:
    date Date;
    double Total;
    u_int bill_no;
    vector<string> dishes;
    vector<int> quantitty;

public:
    bool AddOrder();
    double Total();
    double Income();
    void GenerateBill();

public:
};

#endif