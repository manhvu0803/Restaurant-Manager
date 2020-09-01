#include "bill.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "essentials.hpp"
#include <iomanip>

using namespace std;

/**********************
 * BILL
**********************/

bill::~bill()
{
    stringstream path;
    path << "../restaurant/bill/" << Date.m;
    path << Date << "-" << bill_no;
    ofstream file(path.str());
    file << "BILL NO: " << bill_no << endl;
    file << "DATE: " << Date << endl;
    file << "DISHES:\n";
    file << "ID" << setw(8) << "NAME" << setw(15) << "QUANTITY" << setw(10) << "PRICE" << endl;
    for (int i = 1; i <= dish_IDs.size(); ++i)
    {
        cout << i << "." << setw(3) << dish_IDs[i];
        cout << setw(12) << dish_names[i];
        cout << setw(30) << quantity[i];
        cout << setw(10) << total_per_dish[i] << endl;
    }
    file << endl
         << "TOTAL: " << Total;
    file.close();
}
//     // time_t present = time(0);
//     // tm current;
//     // localtime_s(&current, &present);
//     double Total = 0, total;

//     string month = to_string(1 + current.tm_mon);
//     fstream fout(path + "/" + month + "/income.txt", ios::out);
//     string month = to_string(1 + current.tm_mon);
//     string day = to_string(current.tm_mday);
//     day.append(".txt");
//     fstream fout1(path + "/" + month + "/" + day, ios::app);
//     for (int i = 0; i < dish_names.size(); i++)
//     {
//         fout1 << endl
//               << dish_names[i] << ";" << quantity[i] << ";" << total_per_dish[i] << ";";
//     }
//     fout1 << Total << endl;
//     fout1.close();

//     for (int i = 0; i < 31; i++)
//     {

//         string day = to_string(i + 1);
//         day.append(".txt");
//         ifstream fin(path + "/" + month + "/" + day);
//         if (fin.is_open())
//         {
//             while (!fin.eof())
//             {
//                 string line;
//                 getline(fin, line);
//                 getline(fin, line);
//                 fin >> total;
//                 Total += total;
//             }
//         }
//         fin.close();
//     }
//     fout << "Income of the month: " << Total;

void bill::AddDish(const string &ID, const string &name, const double &price)
{
    int id_size = this->dish_IDs.size();
    for (int i = 0; i < id_size; ++i)
    {
        if (dish_IDs[i] == ID)
        {
            total_per_dish[i] += price;
            Total += price;
            ++quantity[i];
            return;
        }
    }
    dish_names.emplace_back(name);
    dish_IDs.emplace_back(ID);
    quantity.emplace_back(1);
}

bool bill::RemoveDish(const string &ID, const double &price)
{
    int id_size = this->dish_IDs.size();
    for (int i = 0; i < id_size; ++i)
    {
        if (dish_IDs[i] == ID)
        {
            if (quantity[i] == 1)
            {
                dish_IDs.erase(dish_IDs.begin() + i);
                dish_names.erase(dish_names.begin() + i);
                total_per_dish.erase(total_per_dish.begin() + i);
            }
            else
            {
                --quantity[i];
                total_per_dish[i] -= price;
            }
            Total -= price;
            return true;
        }
    }
    return false;
}

// void bill::GenerateBill()
// {
//     string path = "../restaurant/bill/";
//     double Total = 0;
//     time_t present = time(0);
//     tm current;
//     localtime_s(&current, &present);
//     cout << current.tm_hour << ":" << current.tm_min << " " << current.tm_mday << "/" << 1 + current.tm_mon << "/" << 1900 + current.tm_year << endl;

//     for (int i = 0; i < dish_names.size(); i++)
//     {
//         cout << dish_names[i] << "\t\t" << quantity[i] << "\t\t" << total_per_dish[i] << endl;

//         Total += total_per_dish[i];
//     }
//     cout << "Total: " << Total;
// }

void bill::DisplayBill()
{
    cout << "BILL NO: " << bill_no << endl;
    cout << "DATE: " << Date << endl;
    cout << "DISHES:\n";
    cout << "NO" << setw(5) << "ID" << setw(15) << "NAME" << setw(30) << "QUANTITY" << setw(8) << "PRICE" << endl;
    for (int i = 1; i <= dish_IDs.size(); ++i)
    {
        cout << i << "." << setw(5) << dish_IDs[i];
        cout << setw(15) << dish_names[i];
        cout << setw(30) << quantity[i];
        cout << setw(8) << total_per_dish[i] << endl;
    }
    cout << endl
         << "TOTAL: " << Total;
}

const string &bill::getID() const
{
    return bill_no;
}
