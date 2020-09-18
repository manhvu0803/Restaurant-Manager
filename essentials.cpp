#include "essentials.hpp"
#include <sstream>

using namespace std;

/*************************************
 * other useful function (public)
*************************************/

void skipchars(ifstream &file, const int &num)
{
    for (int i = 0; i < num; ++i)
        file.get();
}

/*************************************
 * ERROR_LOG
*************************************/

ERROR_LOG::ERROR_LOG()
{
    time_t t = time(0);
    tm *now = localtime(&t);
    stringstream sstr;
    sstr << "log//" << now->tm_mday << "-" << now->tm_mon + 1 << "-" << now->tm_year + 1900 << ".log";
    log_file.open(sstr.str().c_str(), ios::app);
    log_file.seekp(0, ios::end);
    log_file << "Time: " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\n ";
}

ERROR_LOG::~ERROR_LOG()
{
    log_file << "\n*************************************************\n";
    log_file.close();
}

void ERROR_LOG::LOG(const string &log)
{
    log_file << "\n"
             << log << "\n";
}

ERROR_LOG &ERROR_LOG::instantiate()
{
    static ERROR_LOG instance;
    return instance;
}

/****************************
 * date 
****************************/

bool date::operator<(const date &_date) const
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
            if (d < _date.d)
                return true;
            return false;
        }
    }
}

date::date(const int &d, const int &m, const int &y)
{
    if (y < 1900 || m > 12 || m < 1 || d < 1)
        throw "Invalid date!";
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (y % 400 == 0 || y % 100 != 0 && y % 4 == 0)
        month[1] += 1;
    if (d > month[m])
        throw "Invalid date!";
    this->d = d;
    this->m = m;
    this->y = y;
}

bool date::isValid()
{
    if (y < 1900 || m > 12 || m < 1 || d < 1)
        return false;
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (y % 400 == 0 || y % 100 != 0 && y % 4 == 0)
        month[1] += 1;
    if (d > month[m - 1])
        return false;
    return true;
}

bool date::operator==(const date &_date) const
{
    if (y == _date.y && m == _date.m && d == _date.d)
        return true;
    return false;
}
bool date::operator<=(const date &_date) const
{
    if (*this == _date || *this < _date)
        return true;
    return false;
}
bool date::operator>(const date &_date) const
{
    return !(*this <= _date);
}
bool date::operator>=(const date &_date) const
{
    return !(*this < _date);
}

date ConvertFromString(const string &_date)
{
    if (_date.size() != 10)
        throw "Invalid date string format!";
    int d, m, y;
    stringstream sstr;
    sstr << _date.substr(0, 2);
    sstr >> d;
    sstr.clear();
    sstr << "";
    sstr << _date.substr(3, 2);
    sstr >> m;
    sstr.clear();
    sstr << "";
    sstr << _date.substr(6, 4);
    sstr >> y;
    date tmp(d, m, y);
    return tmp;
}

ostream &operator<<(ostream &os, const date &_date)
{
    if (_date.d < 10)
        os << 0;
    os << _date.d << "-";
    if (_date.m < 10)
        os << 0;
    os << _date.m << "-" << _date.y;
    return os;
}

istream &operator>>(istream &is, date &_date)
{
    date tmp;
    do
    {
        cout << "day: ";
        while (!(cin >> tmp.d))
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "month: ";
        while (!(cin >> tmp.m))
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "year: ";
        while (!(cin >> tmp.y))
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }

    } while (!tmp.isValid());
    _date = tmp;
    return is;
}

date::date()
{
    time_t t = time(0);
    tm *now = localtime(&t);
    d = now->tm_mday;
    m = now->tm_mon + 1;
    y = now->tm_year + 1900;
    h = now->tm_hour;
    min = now->tm_min;
    s = now->tm_sec;
}

string date::GetTime() const
{
    stringstream date_str;
    if (h < 10)
        date_str << 0;
    date_str << h << ":";
    if (min < 10)
        date_str << 0;
    date_str << min << ":";
    if (s < 10)
        date_str << 0;
    date_str << s;
    return date_str.str();
}

void date::CurrentTime()
{
    date tmp;
    *this = tmp;
}

void date::addTime(const string &Time)
{
    if (Time.size() != 8)
        throw "Invalid date string format!";
    stringstream sstr;
    sstr << Time.substr(0, 2);
    sstr >> h;
    sstr.clear();
    sstr << "";
    sstr << Time.substr(3, 2);
    sstr >> min;
    sstr.clear();
    sstr << "";
    sstr << Time.substr(6, 4);
    sstr >> s;
}
