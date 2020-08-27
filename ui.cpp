#include "ui.hpp"
#include <vector>
#include <functional>
#include <iostream>
#include <limits>

using namespace std;

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
#else
    void clearConsole() {}
#endif

// Return true if succeed, false otherwise
template <typename T> 
bool input(std::istream& stream, T& val, const bool clr = true)
{
    stream >> val;
    bool successful = !stream.fail();
    if (clr) {
        stream.clear();
        stream.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return successful;
}

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
        while (!input(cin , choice) || choice < 0 || choice > choiceCnt) 
            cout << "Invalid input, please choose again\n";
        
        if (choice > 0) components[choice - 1]->show();        
    }
    while (choice > 0);    
}

// option
option::option(std::function<void()> func): action(func) {}

option::option(std::function<void()> func, const std::string& desc):
    action(func),
    component(desc)
{}

void option::show()
{
    action();
    if (successMessage.length() > 0) {
        cout << successMessage << '\n';
        cin.get();
    }
}