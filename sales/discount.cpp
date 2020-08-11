#include "discount.hpp"
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <dirent.h>

#define MAX_CODE_LENGTH 10

using namespace std;

/*********************
 * VOUCHER
*********************/
voucher::voucher()
{

    dirent *ent;
    DIR *dir = opendir("voucher");
    if (dir == NULL)
        throw "Missing components!\n";
    string tmp;
    readdir(dir);
    readdir(dir);
    while ((ent = readdir(dir)) != NULL)
    {
        tmp = "";
        string f_name = ent->d_name;
        int length = f_name.length();
        if (f_name.length() >= 6)
        {
            for (int i = 0; i < 6; ++i)
                tmp += f_name[length - 1 - i];
            if (tmp != "1trap.")
                continue;
            else
            {
                tmp = "";
                for (int i = 0; i < length - 6; ++i)
                    tmp.push_back(f_name[i]);
                break;
            }
        }
    }
    string tmp;
    while (!file.eof())
    {
        ++quantity;
        getline(file, tmp);
        code.push_back(tmp);
    }
    file.close();
}

voucher::~voucher()
{
    ofstream file("voucher.txt", ios::app);
    file.seekp(0, ios::end);
    for (auto &i : code)
        file << i << endl;
    file.close();
}
string voucher::code_generator()
{
    vector<int> tmp(MAX_CODE_LENGTH);
    srand(0);
    for (int i = 0; i <= MAX_CODE_LENGTH; ++i)
        tmp[rand() % MAX_CODE_LENGTH] = rand() % 26 + 65;
    string code = "1234567890";
    for (int i = 0; i < MAX_CODE_LENGTH; ++i)
    {
        if (tmp[i] > 9)
            code[i] = static_cast<char>(tmp[i]);
        else
            code[i] = rand() % 10 + 48;
    }
    return code;
}

void voucher::AddDiscount()
{
    cout << "Number of vouchers :";
    int num_of_voucher;
    while (!(cin >> num_of_voucher) || num_of_voucher <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << "Expiration date: ";
    date tmp;
    do
    {
        cin >> expiration_date;
    } while (tmp <= expiration_date);
    for (int i = 0; i < num_of_voucher; ++i)
        code.push_back(code_generator());
    quantity += num_of_voucher;
}