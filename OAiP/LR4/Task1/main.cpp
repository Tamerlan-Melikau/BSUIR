#include <iostream>
using namespace std;

int main() {
    double N[20];
    double x;
    int n = 0;
    char choice;
    
    do {
        cout << "Enter nuber: ";
        cin >> x;
        N[n] = x;
        n++;
        
        if (n >= 20) {
            cout << "Maximum reached (20 numbers)" << endl;
            break;
        }
        
        cout << "Want to enter another number? (y/n): ";
        cin >> choice;
        
    } while (choice == 'y' || choice == 'Y');

    cout << "Entered numbers: ";
    for (int i = 0; i < n; i++) {
        cout << N[i] << " ";
    }
    cout << endl;

    int positiveIndex = -1;
    for (int i = 0; i < n; i++) {
        if (N[i] > 0) {
            positiveIndex = i;
            break;
        }
    }
    
    if (positiveIndex == -1) {
        cout << "No positive numbers!" << endl;
    } else {
        double sum = 0;
        for (int i = positiveIndex + 1; i < n; i++) {
            sum += N[i];
        }
        cout << "First positive number: " << N[positiveIndex] << endl;
        cout << "Sum of numbers after it: " << sum << endl;
    }
    
    return 0;
}