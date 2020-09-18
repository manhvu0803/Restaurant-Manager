#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <limits>

namespace ui
{
    void clearConsole();

    class component
    {
        private:
            std::vector<component*> components;

        public:
            bool clearOnShow = true;

            std::string description;

            component() = default;
            component(const std::string& desc);

            virtual ~component();

            void add(component* comp);

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
            option(std::function<void()> func, const std::string& desc, const std::string& mess);
                    
            void show();
    };
    
    // Return true if succeed, false otherwise
    template <typename T> 
    bool input(T& val, std::istream& stream = std::cin, const bool clear = true)
    {
        stream >> val;
        bool successful = !stream.fail();
        if (clear) {
            stream.clear();
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return successful;
    }
}

#endif // UI_HPP