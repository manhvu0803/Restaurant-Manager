#ifndef ESSENTIALS_HPP
#define ESSENTIALS_HPP

#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>

#define CRLF 8

typedef unsigned int u_int;

/*************************************
 * ERROR_LOG

*************************************/
class ERROR_LOG final
{
private:
    static ERROR_LOG *instance;
    std::ofstream log_file;

public:
    ERROR_LOG();
    ~ERROR_LOG();
    ERROR_LOG(const ERROR_LOG &other) = delete;
    ERROR_LOG &operator=(const ERROR_LOG &other) = delete;
    void LOG(const std::string &log);
    static ERROR_LOG *instantiate();
};

/****************************
 * date 
****************************/
class date
{
private:
    bool isValid();

public:
    u_int d, m, y, h, min, s;
    date();
    date(const int &d, const int &m, const int &y);
    friend std::ostream &operator<<(std::ostream &os, const date &_date);
    friend std::istream &operator>>(std::istream &is, date &_date);
    void addTime(const std::string &Time);
    bool operator<(const date &_date) const;
    bool operator>(const date &_date) const;
    bool operator>=(const date &_date) const;
    bool operator<=(const date &_date) const;
    bool operator==(const date &_date) const;
    friend date ConvertFromString(const std::string &_date);
    void CurrentTime();
    std::string GetTime() const;
};

date ConvertFromString(const std::string &_date);
void skipchars(std::ifstream &file, const int &num);

#endif