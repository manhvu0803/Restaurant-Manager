#include "ui.hpp"
#include <vector>
#include <functional>
#include <iostream>
#include <limits>

using namespace std;

namespace ui
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        #include <direct.h>
        #include <windows.h>
        
        void clearConsole()
        {
            COORD topLeft  = {0, 0};
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO screen;
            DWORD written;

            GetConsoleScreenBufferInfo(console, &screen);
            FillConsoleOutputCharacterA(
                console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
            );
            FillConsoleOutputAttribute(
                console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
                screen.dwSize.X * screen.dwSize.Y, topLeft, &written
            );
            SetConsoleCursorPosition(console, topLeft);
        }
    #elif
        void clearConsole() {}
    #endif // WIN32

    component::component(const string& desc): description(desc) {}

    void component::add(component& comp)
    {
        components.push_back(&comp);
    }

    void component::show()
    {
        int choice;
        do {
            if (clearOnShow) clearConsole();
            int choiceCnt = components.size();

            cout << "0: Return\n";
            for (int i = 0; i < choiceCnt; ++i)
                cout << i + 1  << ": " << components[i]->description << '\n';

            cout << "Your choice: ";
            while (!input(choice) || choice < 0 || choice > choiceCnt) 
                cout << "Invalid input, please choose again\n";
            
            if (choice > 0) components[choice - 1]->show();        
        }
        while (choice > 0);    
    }

    // option
    option::option(function<void()> func): action(func) {}

    option::option(function<void()> func, const string& desc):
        action(func),
        component(desc)
    {}

    option::option(function<void()> func, const string& desc, const string& mess):
        action(func),
        component(desc),   
        successMessage(mess)
    {}

    void option::show()
    {
        if (clearOnShow) clearConsole();
        action();
        if (successMessage.length() > 0) {
            cout << successMessage << '\n';
            cin.get();
        }
    }
}