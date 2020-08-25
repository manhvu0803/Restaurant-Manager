#include "discount.hpp"
#include "essentials.hpp"
#include "menu.h"
#include "essentials.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <dirent.h>
#include <windows.h>

#define MAX_CODE_LENGTH 10

using namespace std;

/*********************
 * DISCOUNT
*********************/
discount::discount()
{
    ERROR_LOG *log = log->instantiate();
    dirent *ent;
    DIR *dir = opendir("voucher");
    if (dir == NULL)
    {
        log->LOG("Folder voucher is missing");
        closedir(dir);
        return;
    }
    readdir(dir);
    readdir(dir);
    while ((ent = readdir(dir)) != NULL)
    {
        string voucher_name = ent->d_name;
        date tmp;
        voucher *voucher_t = nullptr;
        try
        {
            //Remove expired voucher list
            if (tmp >= ConvertFromString(voucher_name))
            {
                string path = "voucher//";
                path += voucher_name;
                remove(path.c_str());
            }
            voucher_t = new voucher(voucher_name);
            vouchers.emplace_back(voucher_t);
        }
        catch (const char *msg)
        {
            log->LOG(msg);
            delete voucher_t;
        };
    }
    closedir(dir);
    dir = opendir("promo");
    if (dir == NULL)
    {
        log->LOG("Folder promo is missing");
        closedir(dir);
        return;
    }
    readdir(dir);
    readdir(dir);
    while ((ent = readdir(dir)) != NULL)
    {
        string promo_name = ent->d_name;
        date tmp;
        voucher *promo_t = nullptr;
        try
        {
            //Remove expired voucher list
            if (tmp >= ConvertFromString(promo_name))
            {
                string path = "promo//";
                path += promo_name;
                remove(path.c_str());
            }
            promo_t = new voucher(promo_name);
            vouchers.emplace_back(promo_t);
        }
        catch (const char *msg)
        {
            log->LOG(msg);
            delete promo_t;
        };
    }
    closedir(dir);
}

voucher *discount::use_voucher(const std::string &code)
{
    for (auto &i : vouchers)
    {
        if (i->CompareCode(code))
            return i;
    }
    return nullptr;
}

promo *discount::use_promo(const std::string &code)
{
    for (auto &i : promos)
    {
        if (i->CompareCode(code))
            return i;
    }
    return nullptr;
}

discount::~discount()
{
    for (auto &i : vouchers)
        delete i;
    for (auto &i : promos)
        delete i;
}

void discount::add_voucher()
{
    voucher *tmp = new voucher;
    tmp->NewVoucher();
    vouchers.emplace_back(tmp);
}

void discount::add_promo()
{
    promo *tmp = new promo;
    tmp->NewPromo();
    promos.emplace_back(tmp);
}

discount *discount::instantiate()
{
    if (!instance)
        instance = new discount;
    return instance;
}

discount *discount::instance = nullptr;

/*********************
 * CODE
*********************/

string Code::code_generator()
{
    vector<int> tmp(MAX_CODE_LENGTH);
    srand(0);
    for (int i = 0; i <= MAX_CODE_LENGTH; ++i)
        tmp[rand() % MAX_CODE_LENGTH] = rand() % 26 + 65;
    string _code_ = "1234567890";
    for (int i = 0; i < MAX_CODE_LENGTH; ++i)
    {
        if (tmp[i] > 9)
            _code_[i] = static_cast<char>(tmp[i]);
        else
            _code_[i] = rand() % 10 + 48;
    }
    return _code_;
}

bool Code::NewCode(const string &_code_)
{
    if (_code_.length() != 10)
        return false;
    this->code.emplace_back(_code_);
    return true;
}

void Code::ListDish()
{
    Menu *rest_menu = rest_menu->instantiate();
    for (auto &i : dish)
    {
        for (auto &j : rest_menu->getMenu())
        {
            if (i == j->getID())
                cout << j->getName();
        }
    }
}

bool Code::CompareCode(const string &code)
{
    for (auto &i : dish)
    {
        if (i == code)
            return true;
    }
    return false;
}

int Code::getDiscountValue()
{
    return discount_value;
}

/*********************
 * VOUCHER
*********************/

voucher::voucher(const string &file_name)
{
    stringstream path;
    path << "voucher/" << file_name;
    ifstream file(path.str().c_str());
    string tmp;
    getline(file, tmp);
    if (tmp != "VOUCHER")
    {
        file.close();
        throw "Invalid file format!";
    }
    getline(file, name);
    file >> discount_value;
    getline(file, tmp);
    getline(file, tmp);
    getline(file, tmp);
    while (tmp.size())
    {
        dish.emplace_back(tmp);
        getline(file, tmp);
    }
    while (!file.eof())
    {
        getline(file, tmp);
        code.emplace_back(tmp);
    }
    file.close();
}

voucher::~voucher()
{
    stringstream path;
    path << "voucher/" << expiration_date;
    ofstream file(path.str().c_str());
    file << "VOUCHER\n";
    file << name << "\n\n";
    for (auto &i : dish)
        file << i << "\n";
    file << "\n";
    for (int i = 0; i < code.size() - 1; ++i)
        file << code[i] << "\n";
    file << code[code.size() - 1];
    file.close();
}

void voucher::NewVoucher()
{
    if (name.size())
        throw "Cannot use an existed voucher object to create a new voucher!";
    cout << "Number of vouchers :";
    while (!(cin >> quantity) || quantity <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << "Expiration date: \n";
    date tmp_d;
    do
    {
        cin >> expiration_date;
    } while (tmp_d >= expiration_date);
    int tmp;
    do
    {
        system("cls");
        Menu *rest_menu = rest_menu->instantiate();
        cout << "Choose dish:\n";
        rest_menu->output();
        cout << "0. Exit\n";
        cout << "Option: ";
        while (!(cin >> tmp) || tmp < 0 || tmp > rest_menu->getMenu().size() + 1)
        {
            cout << "Invalid!\n";
            cout << "Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        if (tmp)
            dish.emplace_back(rest_menu->getMenu()[tmp - 1]->getID());
    } while (tmp || !dish.size());
    cout << "Discount value: ";
    while (!(cin >> discount_value) || discount_value <= 0 || discount_value > 100)
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    for (int i = 0; i < quantity; ++i)
        code.emplace_back(code_generator());
}

/*********************
 * PROMO
*********************/

promo::promo(const string &file_name)
{
    stringstream path;
    path << "promo/" << file_name;
    ifstream file(path.str().c_str());
    string tmp;
    getline(file, tmp);
    if (tmp != "PROMO")
    {
        file.close();
        throw "Invalid file format!";
    }
    getline(file, name);
    file >> discount_value;
    getline(file, tmp);
    getline(file, tmp);
    getline(file, tmp);
    while (tmp.size())
    {
        dish.emplace_back(tmp);
        getline(file, tmp);
    }
    while (!file.eof())
    {
        getline(file, tmp);
        code.emplace_back(tmp);
    }
    file.close();
}

void promo::NewPromo()
{
    if (name.size())
        throw "Cannot use an existed promo object to create a new promo!";
    cout << "Number of promos :";
    while (!(cin >> quantity) || quantity <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << "Expiration date: \n";
    date tmp_d;
    do
    {
        cin >> expiration_date;
    } while (tmp_d <= expiration_date);
    int tmp;
    do
    {
        system("cls");
        Menu *rest_menu = rest_menu->instantiate();
        cout << "Choose dish:\n";
        rest_menu->output();
        cout << "0. Exit\n";
        cout << "Option: ";
        while (!(cin >> tmp) || tmp < 0 || tmp > rest_menu->getMenu().size() + 1)
        {
            cout << "Invalid!\n";
            cout << "Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        if (tmp)
            dish.emplace_back(rest_menu->getMenu()[tmp - 1]->getID());
    } while (tmp || !dish.size());
    cout << "Discount value: ";
    while (!(cin >> discount_value) || discount_value <= 10000)
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    for (int i = 0; i < quantity; ++i)
        code.emplace_back(code_generator());
}

promo::~promo()
{
    stringstream path;
    path << "promo/" << expiration_date;
    ofstream file(path.str().c_str());
    file << "PROMO\n";
    file << name << "\n\n";
    for (auto &i : dish)
        file << i << "\n";
    file << "\n";
    for (int i = 0; i < code.size() - 1; ++i)
        file << code[i] << "\n";
    file << code[code.size() - 1];
    file.close();
}
