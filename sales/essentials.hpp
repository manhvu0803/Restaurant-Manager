#ifndef ESSENTIALS_HPP
#define ESSENTIALS_HPP

#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class ERROR_LOG
{
private:
    ofstream log_file;

public:
    ERROR_LOG()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        stringstream sstr;
        sstr << "log//" << now->tm_mday << "-" << now->tm_mon + 1 << "-" << now->tm_year + 1900 << ".log";
        log_file.open(sstr.str().c_str(), ios::app);
        log_file.seekp(0, ios::end);
        log_file << "Time: " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\n ";
    }
    ~ERROR_LOG()
    {
        log_file << "\n*************************************************\n";
        log_file.close();
    }
    void crash_log(const string &log)
    {
        log_file << "\n"
                 << log << "\n";
    }
};

typedef unsigned int u_int;

/****************************
 * date 
****************************/
class date
{
private:
    bool isValid()
    {
        date tmp;
        if (y < 1900 || m > 12 || m < 1 || d < 1)
            return false;
        int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (y % 400 == 0 || y % 100 != 0 && y % 4 == 0)
            month[1] += 1;
        if (d > month[m])
            return false;
        return true;
    }

public:
    u_int d, m, y;
    date()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        d = now->tm_mday;
        m = now->tm_mon + 1;
        y = now->tm_year + 1900;
    }
    friend ostream &operator<<(ostream &os, const date &_date)
    {
        os << _date.d << "/" << _date.m << "/" << _date.y;
        return os;
    }
    friend istream &operator>>(istream &is, date &_date)
    {
        date tmp;
        do
        {
            cout << "day: ";
            while (!cin >> tmp.d)
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "month: ";
            while (!cin >> tmp.m)
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "year: ";
            while (!cin >> tmp.y)
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
        } while (!tmp.isValid());
        _date = tmp;
    }
    bool operator<(const date &_date) const
    {
        if (y < _date.y)
            return true;
        else if (y > _date.y)
            return false;
        else
        {
            if (m < _date.m)
                return true;
            else if (m > _date.m)
                return false;
            else
            {
                if (d < _date)
                    return true;
                return false;
            }
        }
    }
    bool operator==(const date &_date) const
    {
        if (y == _date.y && m == _date.m && d == _date.d)
            return true;
        return false;
    }
    bool operator<=(const date &_date)
    {
        if (*this == _date || *this < _date)
            return true;
        return false;
    }
    bool operator>(const date &_date)
    {
        return !(*this <= _date);
    }
    bool operator>=(const date &_date)
    {
        return !(*this < _date);
    }
    void ConvertFromString(const string &_date)
    {
        if (_date.size() != 10)
            throw "Invalid format!";
        int d, m, y;
        stringstream sstr;
        sstr << _date.substr(0, 2);
        sstr >> d;
        sstr << "";
        sstr << _date.substr(3, 2);
        sstr >> m;
        sstr << "";
        sstr << _date.substr(6, 4);
        sstr >> y;
    }
    date
};

#endif