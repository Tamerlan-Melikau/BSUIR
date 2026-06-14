#include <iostream>
#include <cstdlib>
#include <ctime>

struct Stack {
    int info;
    Stack* next;
};

void Sort_p(Stack **p) {
    Stack *t = NULL, *t1, *r;
    if ((*p)->next->next == NULL) return;
    do {
        for (t1=*p; t1->next->next != t; t1=t1->next)
            if (t1->next->info > t1->next->next->info){
                r = t1->next->next;
                t1->next->next = r->next;
                r->next = t1->next;
                t1->next = r;
            }
        t = t1->next;
    } while ((*p)->next->next != t);
}

void Sort_info(Stack *p) {
    Stack *t = NULL, *t1;
    int r;
    do {
        for (t1=p; t1->next != t; t1=t1->next)
            if (t1->info > t1->next->info) {
                r = t1->info;
                t1->info = t1->next->info;
                t1->next->info = r;
            }
        t = t1;
    } while (p->next != t);
}

void create(Stack*& head) {
    while (head != NULL) {
        Stack* temp = head;
        head = head->next;
        delete temp;
    }
    
    int n;
    std::cout << "Amount of numbers: ";
    std::cin >> n;

    srand(time(NULL));
    
    for(int i = 0; i < n; i++){
        int num = rand() % 201 - 100;
        
        std::cout << "Number " << i + 1 << ": " << num << std::endl;
        
        Stack* t = new Stack;
        t->info = num;
        t->next = head;
        head = t;
    }
}

void check(Stack* head) {
    if (head == NULL) {
        std::cout << "\nStack is empty\n";
        return;
    }
    
    std::cout << "\n---Stack---\n";
    Stack* current = head;
    while (current != NULL) {
        std::cout << current->info << std::endl;
        current = current->next;
    }
}

void add(Stack*& head) {
    int amount;
    int num;
    std::cout << "How many numbers do u want to add: ";
    std::cin >> amount;
    
    for(int i = 0; i < amount; i++){
        std::cout << "Enter number " << i + 1 << ": ";
        std::cin >> num;
        
        Stack* t = new Stack;
        t->info = num;
        t->next = head;
        head = t;
    }
}

double average(Stack* head) {
    if (head == NULL) return 0;
    
    double sum = 0;
    double count = 0;
    Stack* current = head;
    
    while (current != NULL) {
        sum += current->info;
        count++;
        current = current->next;
    }
    
    return sum / count;
}

void task(Stack*& head) {
    if (head == NULL) {
        std::cout << "\nStack is empty\n";
        return;
    }

    double a = average(head);
    std::cout << "Average: " << a << std::endl;
    
    Stack* removedElements = NULL;
    Stack* prev = NULL;
    Stack* current = head;
    
    std::cout << "Elements less than average: ";
    
    while (current != NULL) {
        if (current->info < a) {
            std::cout << current->info << " ";
            
            Stack* temp = new Stack;
            temp->info = current->info;
            temp->next = removedElements;
            removedElements = temp;
            
            if (prev == NULL) {
                head = current->next;
                delete current;
                current = head;
            } else {
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    if (removedElements == NULL) {
        std::cout << "No elements";
    } else {
        std::cout << "\n\nRemoved elements: \n";
        Stack* temp = removedElements;
        while (temp != NULL) {
            std::cout << temp->info << std::endl;
            temp = temp->next;
        }
        
        while (removedElements != NULL) {
            Stack* temp = removedElements;
            removedElements = removedElements->next;
            delete temp;
        }
    }
    std::cout << std::endl;
}

void addExtraElement(Stack*& head) {
    Stack* dummy = new Stack;
    dummy->info = 0;
    dummy->next = head;
    head = dummy;
}

void removeExtraElement(Stack*& head) {
    if (head != NULL) {
        Stack* dummy = head;
        head = head->next;
        delete dummy;
    }
}

int main() {
    Stack* numbers = NULL;
    
    while(true) {
        int choice;
        std::cout << "\nWhat do you want to do?\n";
        std::cout << "1. Create new records\n";
        std::cout << "2. Check records\n";
        std::cout << "3. Add records\n";
        std::cout << "4. Make a task\n";
        std::cout << "5. Sort using Sort_p (address exchange)\n";
        std::cout << "6. Sort using Sort_info (info exchange)\n";
        std::cout << "7. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> choice;
        
        switch (choice) {
        case 1:
            create(numbers);
            break;
        case 2:
            check(numbers);
            break;
        case 3:
            add(numbers);
            break;
        case 4:
            task(numbers);
            break;
        case 5:
            if (numbers == NULL || numbers->next == NULL) {
                std::cout << "Not enough elements to sort\n";
            } else {
                addExtraElement(numbers);
                Sort_p(&numbers);
                removeExtraElement(numbers);
                std::cout << "Stack sorted using Sort_p method\n";
            }
            break;
        case 6:
            if (numbers == NULL || numbers->next == NULL) {
                std::cout << "Not enough elements to sort\n";
            } else {
                Sort_info(numbers);
                std::cout << "Stack sorted using Sort_info method\n";
            }
            break;
        default:
            while (numbers != NULL) {
                Stack* temp = numbers;
                numbers = numbers->next;
                delete temp;
            }
            return 0;
        }
    }
    
    return 0;
} 