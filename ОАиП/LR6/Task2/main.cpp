#include <iostream>
#include <string>

int main() {
    std::string S;
    int k;
    std::cout << "Eneter the line: ";
    getline(std::cin, S);
    int length = S.length();
    
    std::cout << "Eneter position k: ";
    std::cin >> k;

    if (k < 0 || k >= length) {
        std::cout << "Position k outside the line" << std::endl;

        return 0;
    }
    
    int wordCount = 0;
    bool inWord = false;
    int currentWord = 0;

    for (int i = 0; i < length; i++) {
        if (S[i] == ' ') {
            inWord = false;
        } else {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        }
        
        if (i == k) {
            currentWord = wordCount;
        }
    }

    if (S[k] == ' ') {
        if (currentWord > 0) {
            std::cout << "Previous word number: " << currentWord << std::endl;
        } else {
            std::cout << "No previous word" << std::endl;
        }
    } else {
        std::cout << "Word number: " << currentWord << std::endl;
    }
    
    return 0;
}
