#include <iostream>
#include "ui.hpp"

using namespace std;

class foo
{
    private:
        int a;

    public:
        foo(int x): a(x) {}

        void doSth()
        {
            ++a;
        }

        void output()
        {
            cout << a << '\n';        
        }
};

int main()
{
    foo t(4);
    ui::component menu;    
    ui::option a(bind(&foo::doSth, &t), "Do something");
    a.successMessage = "Done";
    ui::option a2(bind(&foo::output, &t), "Output");
    menu.add(a);
    menu.add(a2);
    menu.show();
}