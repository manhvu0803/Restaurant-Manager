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
#endif

template <typename T> 
void input(std::istream& stream, T& val, const bool clr = true)
{
    stream >> val;
    if (stream.fail()) throw runtime_error("Input format is invalid");
    if (clr) {
        stream.clear();
        stream.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
