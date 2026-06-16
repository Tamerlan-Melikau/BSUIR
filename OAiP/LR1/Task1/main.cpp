#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a;
    cout << "Enter a number:";
    cin >> a; 
    float z1 = sqrt(pow((3*a+2),2)-24*a)/(3*sqrt(a)-2/sqrt(a));
    float z2 = -sqrt(a);
    cout << z1 << "\n";
    cout << z2;

    return 0;
}    