#ifndef BILL_CPP
#define BILL_CPP

#include "../essentials.hpp"
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
    string bill_no;
    vector<string> dish_IDs;
    vector<string> dish_names;
    vector<int> quantity;
    vector<double> total_per_dish;
    static u_int count;

public:
    bill();
    bill(const string &bill_path);
    ~bill();
    void AddDish(const string &ID, const string &name, const double &price);
    bool RemoveDish(const string &ID, const double &price);
    void DisplayBill();
    const string &getBillNo() const;
    void applyDiscount();
};

class bill_manager
{
private:
    vector<bill *> bills;
    vector<bill *> old_bills;
    static bill_manager *instance;
    bill_manager();
    double income;
    void UpdateDishQuant(const int &index, const int &mode);
    vector<int> quantity;

public:
    static bill_manager *instantiate();
    bill *FindBill(const string &bill_no);
    bill_manager &operator=(const bill_manager &other) = delete;
    bill_manager(const bill_manager &other) = delete;
    bill *NewBill();
    ~bill_manager();
    void updateQuantNewDish(const int &pos, const int &mode);
};

#endif