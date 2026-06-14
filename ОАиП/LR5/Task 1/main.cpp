#include <iostream>
#include <iomanip>

int main(){
    double **a;
    int n, m;

    std::cout << "Enter number of rows (n) ";
    std::cin >> n;
    std::cout << "Enter number of columns (m) ";
    std::cin >> m;

    a = new double*[n];
    for(int i = 0; i < n; i++) {
        a[i] = new double[m];
    }

    std::cout << "Enter all items through the space";

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    std::cout << "Entered matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cout << std::setw(5) << a[i][j] << " ";
        }
        std::cout << std::endl;
    }

    int pos = -1;
    bool flag = false;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] > 0){
                pos = i;
                flag = true;
                std::cout << "The first of the lines containing a wish to have one positive element is below the number " << i + 1;
                
                break;
            }
        }

        if (flag){
            break;
        }
    } 

    for(int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
}