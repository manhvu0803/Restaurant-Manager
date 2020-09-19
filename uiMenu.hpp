#ifndef UIMENU_HPP
#define UIMENU_HPP

#include "ui.hpp"
#include "Storage/Storage.h"
#include "menu.h"

using namespace std;

class storageMenu: public ui::component
{	
	private:
		Storage stor;
		
		void findID();
		void findLabel();
		void exportStorage();
	
	public:
		storageMenu();
};

class menuComponent: public ui::component
{
	private:
		Menu& menu;

	public:
		menuComponent();
};

#endif // STORAGEMENU_HPP