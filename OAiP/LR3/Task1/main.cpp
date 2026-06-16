#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double a, b, h;
    
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
    
    std::cout << "Enter h: ";
    if (!(std::cin >> h) || h <= 0) {
        std::cout << "Incorrect data input";
        
        return 1;
    }


    int counter = 1;
    double min_y, max_y;

    std::cout << "\n Номер | Аргумент x | Функция y\n";
    std::cout << "----------------------------------\n";

    for (double x = a; x <= b; x += h) {
        double y = exp(x) + sqrt(1 + exp(2*x)) - 2;

        if (counter==1){
            min_y=y;
            max_y=y;
        }
        
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
        
        std::cout << std::setw(6) << counter << " | " 
                  << std::setw(10) << std::fixed << std::setprecision(4) << x << " | "
                  << std::setw(12) << std::fixed << std::setprecision(6) << y << std::endl;
        
        counter++;
    }

    std::cout << "\n Minimum function value: " << min_y;
    std::cout << "\n Maximum function value: " << max_y;

    return 0;
}