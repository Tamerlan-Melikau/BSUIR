#include <iostream>
#include <string>

int main() {
    std::string L;
    std::cout << "Enter the line:";
    getline(std::cin, L);
    int length = L.length();
    std::cout << "Length: " << length << std::endl;;

    int counter = 0;
    if(length % 5 == 0){
        for(int i = 0; i < length; i++){
            if(L[i] == '[' || 
               L[i] == ']' || 
               L[i] == '(' || 
               L[i] == ')' || 
               L[i] == '{' || 
               L[i] == '}' || 
               L[i] == '<' || 
               L[i] == '>') {
                counter++;
            }
        }
        std::cout << "Number of brackets of all types: " << counter;
    }
}