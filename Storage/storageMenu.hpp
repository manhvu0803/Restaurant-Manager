#ifndef STORAGEMENU_HPP
#define STORAGEMENU_HPP

#include "../ui.hpp"
#include <iostream>
#include "Storage.h"

using namespace std;

class storageMenu: public ui::component
{	
	private:
		Storage stor;
		
		void findID()
		{
			cout << "Find ingredient by ID\nID: ";
			int id;
			ui::input(id);
			Ingredients* ing = stor.findID(id);
			if (ing) ing->print();
            else cout << "Ingredient not found";
		}

		void findLabel()
		{			
			cout << "Find ingredient by label\nLabel: ";
			string label;
			ui::input(label);
			Ingredients* ing = stor.findLabel(label);
			if (ing) ing->print();
            else cout << "Ingredient not found";
		}

		void exportStorage()
		{
			cout << "Exporting to storage.txt\n";
			stor.exp();			
		}
	
	public:
		storageMenu(): component("Storage manager")
		{
			component::add(new ui::option(bind(&storageMenu::findID, this), "Find ingredients by ID"));
			component::add(new ui::option(bind(&storageMenu::findLabel, this), "Find ingredients by label"));
			component::add(new ui::option(bind(&storageMenu::exportStorage, this), "Export storage to text file"));
		}
};

#endif // STORAGEMENU_HPP