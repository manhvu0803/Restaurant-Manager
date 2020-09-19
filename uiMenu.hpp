#ifndef UIMENU_HPP
#define UIMENU_HPP

#include "ui.hpp"
#include "Storage/Storage.h"
#include "menu.h"
#include "sales/bill.hpp"

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

class billMenu: public ui::component
{
	private:
		bill_manager& billManager;
		order& orderManager;

		void findBill();
	
	public:
		billMenu();
};

#endif // STORAGEMENU_HPP