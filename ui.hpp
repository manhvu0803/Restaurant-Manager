#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <vector>
#include <functional>

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
        // successMessage shows after action finish and wait for enter
        // If it is empty, the confirm enter is skipped
        std::string successMessage = "Press Enter to continue...";

        std::function<void()> action;

        option(std::function<void()> func);
        option(std::function<void()> func, const std::string& desc);
                
        void show();
};

#endif // UI_HPP