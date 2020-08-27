#include "bill.hpp"
#include <iostream>
#include <fstream>

using namespace std;

/**********************
 * BILL
**********************/

bill::~bill()
{
    /* stringstream path;
     path << "bill/" << Date;
     ofstream file(path.str().c_str());
     // In bill
     file.close();*/
    string path = "C:/Users/duy/source/repos/Restaurant - Manager/restaurant";
    time_t present = time(0);
    tm current;
    localtime_s(&current, &present);
    double Total = 0, total;


    string month = to_string(1 + current.tm_mon);
    fstream fout(path + "/" + month + "/income.txt", ios::out);

    for (int i = 0; i < 31; i++)
    {

        string day = to_string(i + 1);
        day.append(".txt");
        ifstream fin(path + "/" + month + "/" + day);
        if (fin.is_open())
        {
            while (!fin.eof())
            {
                string line;
                getline(fin, line);
                getline(fin, line);
                fin >> total;
                Total += total;

            }
        }
        fin.close();

    }
    fout << "Income of the month: " << Total;


}

void bill::AddData(const string& ID, const string& name, const double& price)
{
    int id_size = this->dish_IDs.size();
    for (int i = 0; i < id_size; ++i)
    {
        if (dish_IDs[i] == ID)
        {
            total_per_dish[i] += price;
            ++quantity[i];
            return;
        }
    }
    dish_names.emplace_back(name);
    dish_IDs.emplace_back(ID);
    quantity.emplace_back(1);
}
void bill::RemoveData(const string& ID, const double& price)
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

            return;
        }
    }
}
void bill::GenerateBill()
{
    string path = "C:/Users/duy/source/repos/Restaurant - Manager/restaurant";
    double Total = 0;
    time_t present = time(0);
    tm current;
    localtime_s(&current, &present);
    cout << current.tm_hour << ":" << current.tm_min << " " << current.tm_mday << "/" << 1 + current.tm_mon << "/" << 1900 + current.tm_year << endl;


    for (int i = 0; i < dish_names.size(); i++)
    {
        cout << dish_names[i] << "\t\t" << quantity[i] << "\t\t" << total_per_dish[i] << endl;

        Total += total_per_dish[i];

    }
    cout << "Total: " << Total;
    string month = to_string(1 + current.tm_mon);
    string day = to_string(current.tm_mday);
    day.append(".txt");
    fstream fout(path + "/" + month + "/" + day, ios::app);
    for (int i = 0; i < dish_names.size(); i++)
    {
        fout << endl << dish_names[i] << ";" << quantity[i] << ";" << total_per_dish[i] << ";";

    }
    fout << Total << endl;
    fout.close();

}





