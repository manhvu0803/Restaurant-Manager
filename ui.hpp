#include <iostream>
#include <vector>
#include <functional>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)    
    void clearConsole();
#endif

class component
{
    public:
        bool clearOnShow = true;

        std::vector<component*> components;
        std::string description;

        component() = default;
        component(const std::string& desc);
        
        void add(component& comp);

        virtual void show();
};

class option: public component
{
    public:
        std::function<void()> action;

        option(std::function<void()> func);
        option(std::function<void()> func, const std::string& desc);

        void show();
};
