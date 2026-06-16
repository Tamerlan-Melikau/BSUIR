#include <iostream>
#include <math.h>
#include <iomanip>

int main()
{
    double z;
    std::cout <<"Enter a number:";
    if (!(std::cin>>z))
    {
        std::cout<< "Incorrect data input\n";

        return 1;
    }

    double x;

    if(z <= 0){
        x = pow(z,2) + 5;
    }
    else{
        x = 1.0/sqrt(z - 1);
    }

    double y = sin(pow(pow(x,2) - 1,3)) + log(abs(x)) + exp(x);
    
    std::cout<<y;

    return 0;
}