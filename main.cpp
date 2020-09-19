#include "ui.hpp"
#include "manager/manager.hpp"
#include "uiMenu.hpp"

int main()
{
    ui::component menu;
    menu.add(new manager::saleMenu());
    menu.add(new menuComponent());
    menu.add(new billMenu());
    try {
        menu.add(new storageMenu());
        menu.show();
    }
    catch (char const* e) {
        cout << e << '\n';
    }
    catch (...) {
        cout << "Um\n";
    }
    //ERROR_LOG& log = ERROR_LOG::instantiate();
}