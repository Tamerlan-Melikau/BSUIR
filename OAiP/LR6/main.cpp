#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

struct Person {
    char lastName[50];
    int weight;
    int height;
};

int hashFunc(int height, int M) {
    return height % M;
}

int main() {
    srand(time(NULL));
    int n = 8;
    Person* arr = new Person[n];
    int* r = new int[100];
    for (int i = 0; i < 100; i++) {
        r[i] = rand() % 9 + 1;
    }
    for(int i = 0; i < n; i++){
    std::cout << "Enter person " << i+1 << ":" << std::endl;
    std::cout << "  Last name: ";
    std::cin >> arr[i].lastName;
    std::cout << "  Weight: ";
    std::cin >> arr[i].weight;
    std::cout << "  Height (key): ";
    std::cin >> arr[i].height;
    }

    int M = 10;
    Person* table = new Person[M];
    for (int i = 0; i < M; i++) {
        table[i].height = -1;
        strcpy(table[i].lastName, "");
        table[i].weight = 0;
    }

    for(int i = 0; i < n; i++){
        int index = hashFunc(arr[i].height, M);
        int attempt = 0;

        if (table[index].height == -1) {
            table[index] = arr[i];
        }
        else {
            int newIndex = (index + r[attempt]) % M;
            attempt++;

            while (table[newIndex].height != -1 && attempt< 100) {
                newIndex = (index + r[attempt]) % M;
                attempt++;
            }
            
            if (table[newIndex].height  == -1) {
                table[newIndex] = arr[i];
                std::cout << "Collision! Inserted " << arr[i].height  << " into cell " << newIndex << std::endl;
            } else {
                std::cout << "Table is full!" << std::endl;
            }
        }
    }

    std::cout << "\nArr:" << std::endl;
    for(int i = 0; i < n; i++){
        std::cout << i+1 << ". " << arr[i].lastName << ", weight: " << arr[i].weight << ", height: " << arr[i].height << std::endl;
    }
    
    std::cout << "\nHash table:" << std::endl;
    for(int i = 0; i < M; i++){
        if (table[i].height != -1) {
            std::cout << "Person " << i << ": " << table[i].lastName << ", weight: " << table[i].weight << ", height: " << table[i].height << std::endl;
        } else {
            std::cout << "-1" << std::endl;
        }
    }
    
    int searchKey;
    std::cout << "\nEnter height to search: ";
    std::cin >> searchKey;
    
    int index = hashFunc(searchKey, M);
    int startIndex = index;
    int attempt = 0;
    bool found = false;
    
    while (table[index].height != -1) {
        if (table[index].height == searchKey) {
            std::cout << "Last name: " << table[index].lastName << std::endl;
            std::cout << "Weight: " << table[index].weight << std::endl;
            std::cout << "Height: " << table[index].height << std::endl;
            std::cout << "Position in hash table: " << index << std::endl;
            found = true;
            break;
        }
        index = (startIndex + r[attempt]) % M;
        attempt++;
        if (attempt >= 100 || index == startIndex) break;
    }
    
    if (!found) {
        std::cout << "Person with height " << searchKey << " not found!" << std::endl;
    }
    
    delete[] arr;
    delete[] table;
    delete[] r;
    
    return 0;
}