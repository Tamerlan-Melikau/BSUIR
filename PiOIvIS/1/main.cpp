#include <iostream>
#include <iomanip>
#include <vector>

std::vector<std::vector<int>> createMatrix(int rows, int cols) {
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << std::setw(3) << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    double **a;
    int n;

    std::cout << "Enter size: ";
    std::cin >> n;

    a = new double*[n];
    for(int i = 0; i < n; i++) {
        a[i] = new double[n];
    }

    std::cout << "Enter elements:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    int edgeCount = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(a[i][j] == 1) edgeCount++;
        }
    }

    auto matrix = createMatrix(n, edgeCount);

    int stolb = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(a[i][j] == 1) {
                matrix[i][stolb] = 1;
                matrix[j][stolb] = 1;
                stolb++;
            }
        }
    }

    std::cout << "\nMatrix of incidet:\n";
    printMatrix(matrix);

    for(int i = 0; i < n; i++) delete[] a[i];
    delete[] a;

    return 0;
}