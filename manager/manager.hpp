#include <string>

class manager
{
    private:
        static const std::string dir;

    public:
        void showMonth(int m);
        void showDate(int m, int d);
        void showTotal();
};