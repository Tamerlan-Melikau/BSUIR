#include <iostream>
#include <math.h>
#include <iomanip>

int main(){
    int t;
    double x,X;
    double a,c,z;

    std::cout<<"Choose a number of the function:\n 1) f(x) = 2x\n 2) f(x) = x^2\n 3) f(x) = x/3\n";

    if (!(std::cin >> t))
    {
        std::cout << "Incorrect data input\n";

        return 1;
    }

    std::cout << "Enter z: ";
    std::cin >> z;

    if (z <= 1) {
        x = pow(z, 2) + 1;
    } else {
        x = 1 / sqrt(z - 1);
    }

    switch (t) {
        case 1:
            X = 2 * x;
            break;
        case 2:
         std::cout << "case2";
            X = pow(x, 2);
            break;
        case 3:
            X = x / 3.0;
            
        default:
         std::cout << "asdfghjkl";
         X = x;
        
       
    }

    std::cout << "Enter a: ";
    std::cin >> a;
    std::cout << "Enter c: ";
    std::cin >> c;

    double y = a*pow(sin(pow(X,2)-1),3) + c*log(abs(x)) + exp(x);
    
    std::cout << "Result: " << y;
}   