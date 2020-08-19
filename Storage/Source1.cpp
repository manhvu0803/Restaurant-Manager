#include <iostream>
#include "Storage.h"
using namespace std;
int main()
{
	Storage a;
	a.imp();
	a.find("Fuck")->change("Fack");
	a.print();
	return 0;
}