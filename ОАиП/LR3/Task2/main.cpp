#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double a, b, h, n;
    
    std::cout << "Enter a: ";
    if (!(std::cin >> a)) {
        std::cout << "Incorrect data input";
        return 1;
    }
    
    std::cout << "Enter b: ";
    if (!(std::cin >> b)) {
        std::cout << "Incorrect data input";
        return 1;
    }
    
    if (a > b) {
        std::cout << "Incorrect data input (a > b)";
        return 1;
    }

    std::cout << "Enter n: ";
    if (!(std::cin >> n)) {
        std::cout << "Incorrect data input";
        return 1;
    }
    
    std::cout << "Enter h: ";
    if (!(std::cin >> h) || h <= 0) {
        std::cout << "Incorrect data input";
        return 1;
    }

    std::cout << "\n N |Number of iterations | Sum | Function value | Delta |\n";
    std::cout << "---------------------------------------------------------------\n";

    int counter = 0;

    for (double x = a; x <= b; x += h) {
        double Y = (1 - (x*x / 2)) * cos(x) - (x/2 * sin(x));
        double S = 0;
   
        double term = 1.0; // (-1)^0 * (2*0²+1)/0! * x^0 = 1
        int k = 0;
        
        while (k <= n && fabs(S - Y) > 0.00000001) {
            S += term;
            
            if (k < n) {
                double current_numerator = 2.0 * k * k + 1.0;
                double next_numerator = 2.0 * (k + 1) * (k + 1) + 1.0;
                
                term = term * (-1.0) * (next_numerator / current_numerator) 
                       / ((2.0 * k + 1.0) * (2.0 * k + 2.0)) * x * x;
            }
            
            k++;
        }

        counter++;
        
        std::cout << std::setw(6) << counter << " | " 
                  << std::setw(10) << k << " | "
                  << std::setw(10) << S << " | "
                  << std::setw(12) << Y << " | "
                  << std::setw(12) << fabs(S - Y) << std::endl;
    }

    return 0;
}