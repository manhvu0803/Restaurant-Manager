#include "ui.hpp"
#include "manager/manager.hpp"
#include "uiMenu.hpp"

int main()
{
    ui::component menu;
    menu.add(new manager::saleMenu());
    menu.add(new storageMenu());
    menu.add(new menuComponent());
    menu.add(new billMenu());
    menu.show();
}