#include <iostream>
#include <string>

int main() {
    std::string word;
    std::cout << "Enter the word: ";
    std::cin >> word;
    
    int left = 0;
    int right = word.length() - 1;
    bool isPal = true;
    
    while (left < right) {
        if (word[left] != word[right]) {
            isPal = false;
            break;
        }
        left++;
        right--;
    }
    
    if (isPal) {
        std::cout << "Yes, it’s a palindren" << std::endl;
    } else {
        std::cout << "No, it’s not a palindren" << std::endl;
    }
    
    return 0;
}