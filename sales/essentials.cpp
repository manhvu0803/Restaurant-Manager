#include "essentials.hpp"
#include <sstream>

using namespace std;

/*************************************
 * ERROR_LOG
*************************************/

ERROR_LOG::ERROR_LOG()
{
    time_t t = time(0);
    tm *now = localtime(&t);
    std::stringstream sstr;
    sstr << "log//" << now->tm_mday << "-" << now->tm_mon + 1 << "-" << now->tm_year + 1900 << ".log";
    log_file.open(sstr.str().c_str(), std::ios::app);
    log_file.seekp(0, std::ios::end);
    log_file << "Time: " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\n ";
}

ERROR_LOG::~ERROR_LOG()
{
    log_file << "\n*************************************************\n";
    log_file.close();
}

void ERROR_LOG::LOG(const std::string &log)
{
    log_file << "\n"
             << log << "\n";
}

ERROR_LOG *ERROR_LOG::instance = nullptr;

ERROR_LOG *ERROR_LOG::instantiate()
{
    if (!instance)
        instance = new ERROR_LOG;
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
    date tmp;
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

date ConvertFromString(const std::string &_date)
{
    if (_date.size() != 10)
        throw "Invalid date string format!";
    int d, m, y;
    std::stringstream sstr;
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

std::ostream &operator<<(std::ostream &os, const date &_date)
{
    if (_date.d < 10)
        os << 0;
    os << _date.d << "-";
    if (_date.m < 10)
        os << 0;
    os << _date.m << "-" << _date.y;
    return os;
}

std::istream &operator>>(std::istream &is, date &_date)
{
    date tmp;
    do
    {
        std::cout << "day: ";
        while (!(std::cin >> tmp.d))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        std::cout << "month: ";
        while (!(std::cin >> tmp.m))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        std::cout << "year: ";
        while (!(std::cin >> tmp.y))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    } while (!tmp.isValid());
    _date = tmp;
    return is;
}