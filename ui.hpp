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
    
    // Return true if succeed, false otherwise
    template <typename T> 
    bool input(std::istream& stream, T& val, const bool clear)
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