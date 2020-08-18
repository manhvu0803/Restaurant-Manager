#ifndef ORDER_HPP
#define ORDER_HPP

class order
{
private:
    order(){};
    static order *instance;

public:
    order *instantiate()
    {
        if (!instance)
            instance = new order;
        return instance;
    }
};

#endif