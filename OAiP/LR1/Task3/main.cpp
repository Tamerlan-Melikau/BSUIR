#include <iostream>
#include <math.h>

int main()
{
    double x,y,z;
    std::cout << "Enter three numbers:";
    if (!(std::cin >> x >> y >> z))
    {
        std::cout << "Incorrect data input\n";

        return 1;
    }
    double n = x - y;
    double m = std::fabs(n);
    double t = y + pow((x - 1), 1.0/3.0);
    double k = m*(pow(sin(z), 2) + tan(z));
    if (t < 0)
    {
        std::cout << "Incorrect data input\n";

        return 1;
    }
    if (k == 0)
    {
        std::cout << "Incorrect data input\n";

        return 1;
    }
    double f = pow(t, 0.25)/k;
    std::cout << "Result: " << f << std::endl;

    return 0;
}