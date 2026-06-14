#include <iostream>
#include <math.h>

int brain(double x, int n){
    int t;
    if(n == 0){
        return 1;
    }
    else{
        if(n % 2 == 0){
            return t = pow(x, n);
        }
        else{
            return t = pow(x, n);
        }
    }
}

double power(double base, double exp) {
    if (exp == 0) {
        return 1;
    }
    else {
        return base * power(base, exp - 1);
    }
}

int main() {
    double x;
    int n;
    double y;
    std::cout << "Enter x: ";
    if (!(std::cin >> x)) {
        std::cout << "Incorrect data input";

        return 1;
    }
    std::cout << "Enter n: ";
    if (!(std::cin >> n)) {
        std::cout << "Incorrect data input";

        return 1;
    }
    int t;

    if(n % 2 == 0){
        y = x * power(x, n - 1);
    }
    else{
        y = x * power(x, n - 1);
    }

    t = brain(x,n);


    std::cout << "Result with recursion: " << y << std::endl;
    std::cout << "Result without recursion: " << t << std::endl;

}