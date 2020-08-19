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
    double Total = 0;
    u_int bill_no = -1;
    vector<string> dish_IDs;
    vector<string> dish_names;
    vector<int> quantity;
    vector<double> total_per_dish;

public:
    bill(){};
    ~bill();
    void AddData(const string &ID, const string &name);
    double Total();
    double Income();
    void GenerateBill();
    void LoadOldBill();
    void RemoveData(const string &ID);
};

#endif