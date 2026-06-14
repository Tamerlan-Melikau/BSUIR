#include <iostream>

int findMax(int arr[], int a, int b) {
    if (a == b) {
        return arr[a];
    }
    
    int c = a + (b - a) / 2;
    
    int maxLeft = findMax(arr, a, c);
    int maxRight = findMax(arr, c + 1, b);
    
    return (maxLeft > maxRight) ? maxLeft : maxRight;
}

int findMax2(int arr[], int a, int b) {
    int max = arr[a];
    
    for (int i = a + 1; i <= b; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    return max;
}

int main() {
    int n;
    
    std::cout << "Enter size: ";
    std::cin >> n;
    
    if (n <= 0) {
        std::cout << "Incorrect data input\n";
        return 1;
    }
    
    int* t = new int[n];
    std::cout << "Enter elements: \n";
    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
    }
    std::cout << "\n";
    
    int maxElement = findMax(t, 0, n - 1);
    int maxElement2 = findMax2(t, 0, n - 1);
    
    std::cout << "Max is (recursy): " << maxElement << "\n";
    std::cout << "Max is (without): " << maxElement2 << "\n";    

    
    delete[] t;

    return 0;
}