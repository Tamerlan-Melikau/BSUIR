#include <iostream>

struct TwoWay {
    int data;
    TwoWay* next;
    TwoWay* prev;
};

void createnewrecord(TwoWay*& head, TwoWay*& tail){
    while (head != NULL) {
        TwoWay* temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;

    int n;
    std::cout << "Enter amounts of elements: ";
    std::cin >> n;

    for(int i = 0; i < n; i++){
        int element;
        std::cout << "Enter " << i + 1 << " element: ";
        std::cin >> element;

        TwoWay* new_node = new TwoWay;
        new_node->data = element;
        new_node->next = NULL;
        new_node->prev = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }  
    }
}

void print(TwoWay* head){
    TwoWay* current = head;
    while(current != NULL){
        std::cout << current->data << "\n";
        current = current->next;
    }
}

void printreverse(TwoWay* tail){
    TwoWay* current = tail;
    while(current != NULL){
        std::cout << current->data << "\n";
        current = current->prev;
    }
}

void addtoend(TwoWay*& head, TwoWay*& tail){
    int n;
    std::cout << "Enter amounts of elements: ";
    std::cin >> n;

    for(int i = 0; i < n; i++){
        int element;
        std::cout << "Enter " << i + 1 << " element: ";
        std::cin >> element;
        TwoWay* new_node = new TwoWay;
        new_node->data = element;
        new_node->next = NULL;
        new_node->prev = NULL;
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    } 
}

void addtobegin(TwoWay*& head, TwoWay*& tail){
    int n;
    std::cout << "Enter amounts of elements: ";
    std::cin >> n;

    for(int i = 0; i < n; i++){
        int element;
        std::cout << "Enter " << i + 1 << " element: ";
        std::cin >> element;
        TwoWay* new_node = new TwoWay;
        new_node->data = element;
        new_node->next = NULL;
        new_node->prev = NULL;
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        }
        else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }
}

double average(TwoWay* head){
    if (head == NULL) return 0;
    
    double sum = 0;
    double count = 0;
    TwoWay* current = head;
    
    while (current != NULL) {
        sum += current->data;
        count++;
        current = current->next;
    }
    
    return sum / count;
}

void task(TwoWay*& head, TwoWay*& tail){
    if (head == NULL) {
        std::cout << "List is empty!" << std::endl;
        return;
    }

    double a = average(head);
    std::cout << "Average: " << a << "\n";

    TwoWay* current = head;
    
    while(current){
        TwoWay* next = current->next;
        
        if(current->data < a){
            if(current->prev) 
                current->prev->next = current->next;
            else 
                head = current->next;
                    
            if(current->next) 
                current->next->prev = current->prev;
            else 
                tail = current->prev;
            
            delete current;
        }
        current = next;
    }
}

int main() {
    TwoWay* head = NULL;
    TwoWay* tail = NULL;

    while(true) {
        int choice;
        std::cout << "\nWhat do you want to do?\n";
        std::cout << "1. Create new records\n";
        std::cout << "2. Check records\n";
        std::cout << "3. Add records to begin\n";
        std::cout << "4. Add records to end\n";
        std::cout << "5. Check reverse\n";
        std::cout << "6. Make a task\n";
        std::cout << "7. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> choice;
        
        switch (choice) {
        case 1:
            createnewrecord(head, tail);
            break;
        case 2:
            print(head);
            break;
        case 3:
            addtobegin(head, tail);
            break;
        case 4:
            addtoend(head, tail);
            break;
        case 5:
            printreverse(tail);
            break;
        case 6:
            task(head, tail);
            break;
        case 7:
            return 0;
        default:
            std::cout << "Invalid choice, try again\n";
            return 0;
        }
    }
}