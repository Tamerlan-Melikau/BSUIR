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
    int n, m;

    std::cout << "Enter vertices: ";
    std::cin >> n;
    std::cout << "Enter edges: ";
    std::cin >> m;

    a = new double*[n];
    for(int i = 0; i < n; i++) {
        a[i] = new double[m];
    }

    std::cout << "Enter elements:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    auto matrix = createMatrix(n, n);

    int stolb = 0;
    for(int i = 0; i < m; i++) {
        int first = -1, second = -1;
        for(int j = 0; j < n; j++) {
            if(a[j][i] == 1) {
                if(first == -1) first = j;
                else second = j;
            }
        }
        if(second != -1) {
            matrix[first][second] = 1;
            matrix[second][first] = 1;
        }
    }

    std::cout << "\nMatrix of adjacency:\n";
    printMatrix(matrix);

    for(int i = 0; i < n; i++) delete[] a[i];
    delete[] a;

    return 0;
}