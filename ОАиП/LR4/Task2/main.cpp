#include <iostream>
#include <cstdlib>
#include <math.h>

int main(){
    double arr[20];
    double x;
    int n = 0;
    char yon;
    int number;
    
    std::cout << ("Enter number yourself - 1, random - 2\n");
    
    if(!(std::cin >> number)){
        std::cout << ("Incorrect data input");
        return 1;
    }

    
    if (number == 1){
        std::cout << ("Enter number: \n");
        
        if(!(std::cin >> x)){
            std::cout << ("Incorrect data input");

            return 1;
        }
        
        arr[n] = x;
        n++;
        
        if (n >= 20) {
            std::cout << "Maximum reached (20 numbers)" << std::endl;
        } else {
            std::cout << ("Want to enter another number?(y/n)");
            
            if(!(std::cin >> yon)){
                std::cout << ("Incorrect data input");
                
                return 1;
            }
            
            while(yon == 'y'){
                if (n >= 20) {
                    std::cout << "Maximum reached (20 numbers)" << std::endl;
                    break;
                }
                
                std::cout << ("Enter a number: \n");
                
                if(!(std::cin >> x)){
                    std::cout << ("Incorrect data input");
                    return 1;
                }
                
                arr[n] = x;
                n++;

                if (n >= 20) {
                    std::cout << "Maximum reached (20 numbers)" << std::endl;
                    break;
                } else {
                    std::cout << ("Want to enter another number?(y/n)");
                    std::cin >> yon;
                }
            }
        }
    }
    else if (number == 2){
        std::cout << ("Do you want me to enter a number?(y/n)");
        std::cin >> yon;
        
        while (yon == 'y'){
            if (n >= 20) {
                std::cout << "Maximum reached (20 numbers)" << std::endl;
                break;
            }
            
            int randomNumber = (std::rand() % 201) - 100;
            std::cout << "Random number: " << randomNumber;
            arr[n] = randomNumber;
            n++;
            
            if (n >= 20) {
                std::cout << "Maximum reached (20 numbers)" << std::endl;
                break;
            } else {
                std::cout << ("\nWant to enter another number?(y/n)");
                std::cin >> yon;
            }
        }
    }

    int pos = -1;
    bool hasPositive = false;
    for (int i = 0; i < n; i++){
        
        if (arr[i] < 0){
            pos = i;
            std::cout <<"Position: "<< i << std::endl;
            hasPositive = true;
            break;
        }
    }
        
    if(!hasPositive){
        std::cout<< "No pos number found\n";

        return 1;
    }
    
    double sum = 0;
    if(pos%2 == 1){
        pos += 1;
    }
    else{
        pos += 2;
    }
    for (int i = pos; i < n; i += 2){
        sum += fabs(arr[i]);
    }

    std::cout << "Sum: " << sum;
}