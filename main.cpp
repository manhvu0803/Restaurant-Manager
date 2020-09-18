#include "ui.hpp"
#include "manager/manager.hpp"

int main()
{
    ui::clearConsole();
    ui::component menu;
    menu.add(new saleMenu());
    menu.show();
}