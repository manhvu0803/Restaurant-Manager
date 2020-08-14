#include <iostream>
#include <vector>
#include <functional>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)    
    void clearConsole();
#endif

class component
{
    public:
        std::vector<component*> components;
        std::string description;

        virtual void show();
};

class option: public component
{
    public:
        std::function<void()> action;

        void show();
};
