#ifndef BILL_CPP
#define BILL_CPP

#include "essentials.hpp"
#include <iostream>
#include <vector>
// #include "order.hpp"

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

class bill_manager
{
private:
    vector<bill *> bills;
    vector<bill *> old_bills;
    static bill_manager *instance;
    bill_manager(){};

public:
    static bill_manager *instantiate();
    bill *FindBill(const string &bill_no);
};

class bill
{
private:
    date Date;
    double Total;
    string bill_no;
    vector<string> dish_IDs;
    vector<string> dish_names;
    vector<int> quantity;
    vector<double> total_per_dish;
    static double income;

public:
    bill() : Total(0){};
    ~bill();
    void AddDish(const string &ID, const string &name, const double &price);
    void LoadOldBill();
    bool RemoveDish(const string &ID, const double &price);
    void DisplayBill();
    const string &getBillNo() const;
};

#endif