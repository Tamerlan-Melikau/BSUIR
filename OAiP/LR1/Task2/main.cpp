#include <iostream>
#include <math.h>
#include <iomanip>
int main()
{
    double a;
    std::cout << "Entry a number:";
    if (!(std::cin >> a))
    {
        std::cout << "Incorrect data input\n";

        return 1;
    }
    double p = 3.1415926;
    double z1 = cos(a) + sin(a) + cos(3*a) + sin(3*a);
    double z2 = 2*sqrt(2)*cos(a)*sin(p/4 + 2*a);
    if (z1 = z2)
    {
        std::cout << "Results are equal\n";
        std::cout << z1 << "\n";
        std::cout << z2;
    } 
    else 
    {
        std::cout << "Results are not equal\n";
        std::cout << z1 << "\n";
        std::cout << z2;
    }
   
    return 0;
}