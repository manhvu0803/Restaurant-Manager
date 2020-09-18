#include "ui.hpp"
#include "manager/manager.hpp"
#include "Storage/storageMenu.hpp"

int main()
{
    ui::component menu;
    menu.add(new saleMenu());
    menu.add(new storageMenu());
    menu.show();
}