#include <iostream>
#include <math.h>
#include <iomanip>

double findMinimum(double firstNumber, double secondNumber);
double findMaximum(double firstNumber, double secondNumber);

int main(){
    double F,x,y,a;
    std::cout << "Enter x: ";
    if (!(std::cin >> x)){
        std::cout << "Incorrect data input";

        return 1;
    }
    std::cout << "Enter y: ";
    if (!(std::cin >> y)){
        std::cout << "Incorrect data input";

        return 1;
    }
    std::cout << "Enter a: ";
    if (!(std::cin >> a)){
        std::cout << "Incorrect data input";

        return 1;
    }

    if (a < 0){
        F = findMaximum(sqrt(x), y) + a;
    }
    else if (a == 0){
        F = findMinimum(x, a);
    }
    else {
        F = sqrt(pow(x,2) + pow(y,2)) + exp(y-x);
    }

    std::cout << "Result: " << F;

    return 0;
}

double findMinimum(double firstNumber, double secondNumber){
    if(firstNumber < secondNumber){
        return firstNumber;
    }
    else{
        return secondNumber;
    }
}

double findMaximum(double firstNumber, double secondNumber){
    if(firstNumber > secondNumber){
        return firstNumber;
    }
    else{
        return secondNumber;
    }
}