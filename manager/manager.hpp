#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "../ui.hpp"

struct dish
{
    long id;
    int quantity;
    long price;
    std::string name;
};

class bill
{            
    private:        
        static const std::string dir;

    public:
        const int number;
        const int h, m, s;
        const std::vector<dish> dishes;
        
        bill(int number, int h, int m, int s, std::vector<dish>& dishes);

        static std::unique_ptr<bill> getBill(int y, int m, int d);

        long total() const;
        
        friend std::ostream& operator<<(std::ostream& stream, const bill& b);
};

class saleMenu: public ui::component
{
    public:
        static void showDateSale();
        static void showMonthSale();
        static void showYearSale();
        static void menu();
};

#endif // MANAGER_HPP