#include "discount.hpp"
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <dirent.h>
#include <cstdio>
#include <stdexcept>

#define MAX_CODE_LENGTH 10

using namespace std;

discount *discount::instance = nullptr;

discount *discount::Instantiate()
{
    if (!instance)
        instance = new discount;
}

discount::discount()
{

    dirent *ent;
    DIR *dir = opendir("voucher");
    if (dir == NULL)
    {
        Clog.crash_log("Folder voucher is missing");
        exit(-1);
    }
    while ((ent = readdir(dir)) != NULL)
    {
        string f_name = ent->d_name;
        date tmp;
        string voucher_name;
        try
        {
            //Remove expired voucher list
            try
            {
                voucher_name = f_name.substr(0, 10);
            }
            catch (std::out_of_range &e)
            {
                Clog.crash_log(e.what());
                exit(-1);
            };
            if (tmp == ConvertFromString(voucher_name))
            {
                string path = "voucher//";
                path += f_name;
                remove(path.c_str());
            }
            vouchers.push_back(new voucher(voucher_name));
        }
        catch (const char *msg)
        {
            Clog.crash_log(msg);
            exit(-1);
        };
    }
    closedir(dir);
}

discount::~discount()
{
}

/*********************
 * VOUCHER
*********************/
voucher::voucher(const string &path)
{
    ifstream file(path);
    if (!file.fail())
    {
        stringstream error;
        error << "Cannot open file : " << path;
        throw error.str().c_str();
    }
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