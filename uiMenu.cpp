#include "uiMenu.hpp"
#include <iostream>

using namespace std;

// Storage menu
void storageMenu::findID()
{
    cout << "Find ingredient by ID\nID: ";
    int id;
    ui::input(id);
    Ingredients* ing = stor.findID(id);
    if (ing) ing->print();
    else cout << "Ingredient not found";
}

void storageMenu::findLabel()
{
    cout << "Find ingredient by label\nLabel: ";
    string label;
    ui::input(label);
    Ingredients* ing = stor.findLabel(label);
    if (ing) ing->print();
    else cout << "Ingredient not found";
}

void storageMenu::exportStorage()
{
    cout << "Exporting to storage.txt\n";
    stor.exp();			
}

storageMenu::storageMenu(): component("Storage manager")
{
    component::add(new ui::option(bind(&storageMenu::findID, this), "Find ingredients by ID"));
    component::add(new ui::option(bind(&storageMenu::findLabel, this), "Find ingredients by label"));
    component::add(new ui::option(bind(&storageMenu::exportStorage, this), "Export storage to text file"));
}

// Menu component (dish menu)
menuComponent::menuComponent(): 
    menu(Menu::instantiate()), 
    component("Menu and dishes manager")
{
    component::add(new ui::option(bind(&Menu::iOutput, &menu), "Show menu"));
    component::add(new ui::option(bind(&Menu::iChangeDish, &menu), "Change a dish"));
    component::add(new ui::option(bind(&Menu::iNewDish, &menu), "Create a new dish"));
    component::add(new ui::option(bind(&Menu::iRemoveDish, &menu), "Remove a dish"));
}