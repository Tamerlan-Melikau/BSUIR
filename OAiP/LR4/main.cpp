#include <iostream>
#include <cstring>

struct Stack {
    char info;
    Stack *next;
};

struct NumStack {
    double info;
    NumStack *next;
};

void push(Stack*& head, char a) {
    Stack* t = new Stack;
    t->info = a;
    t->next = head;
    head = t;
}

char pop(Stack*& head) {
    if (head == NULL) return 0;
    char value = head->info;
    Stack* t = head;
    head = head->next;
    delete t;
    return value;
}

void pushNum(NumStack*& head, double a) {
    NumStack* t = new NumStack;
    t->info = a;
    t->next = head;
    head = t;
}

double popNum(NumStack*& head) {
    if (head == NULL) return 0;
    double value = head->info;
    NumStack* t = head;
    head = head->next;
    delete t;
    return value;
}

int prior(char a) {
    if (a == '+' || a == '-') return 1;
    if (a == '*' || a == '/') return 2;
    return 0;
}

int main() {
    char mas[100];
    std::cout << "Enter problem: ";
    std::cin.getline(mas, 100);
    int length = strlen(mas);

    char rez[200] = "";
    int j = 0;
    Stack* stack = NULL;

    for (int i = 0; i < length; i++) {
        char ch = mas[i];
        
        if (ch >= 'a' && ch <= 'z') {
            rez[j++] = ch;
            rez[j++] = ' ';  
        }
        else if (ch == '(') {
            push(stack, ch);
        }
        else if (ch == ')') {
            while (stack != NULL && stack->info != '(') {
                rez[j++] = pop(stack);
                rez[j++] = ' ';
            }
            if (stack != NULL) pop(stack);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (stack != NULL && prior(stack->info) >= prior(ch)) {
                rez[j++] = pop(stack);
                rez[j++] = ' ';
            }
            push(stack, ch);
        }
    }

    while (stack != NULL) {
        rez[j++] = pop(stack);
        rez[j++] = ' ';
    }

    std::cout << "RPN: " << rez << std::endl;

    NumStack* numStack = NULL;
    double values[26] = {0};
    bool value_set[26] = {false};
    double a, b;

    for (int i = 0; i < strlen(rez); i++) {
        char ch = rez[i];
        
        if (ch >= 'a' && ch <= 'z') {
            if (value_set[ch - 'a'] == false ) {
                std::cout << "Value for " << ch << ": ";
                std::cin >> values[ch - 'a'];
                value_set[ch - 'a'] = true;
            }
            pushNum(numStack, values[ch - 'a']);
        }
        else if (ch == '+') {
            b = popNum(numStack);
            a = popNum(numStack);
            pushNum(numStack, a + b);
        }
        else if (ch == '-') {
            b = popNum(numStack);
            a = popNum(numStack);
            pushNum(numStack, a - b);
        }
        else if (ch == '*') {
            b = popNum(numStack);
            a = popNum(numStack);
            pushNum(numStack, a * b);
        }
        else if (ch == '/') {
            b = popNum(numStack);
            a = popNum(numStack);
            if (b == 0) {
                std::cout << "Incorrect data input" << std::endl;
                return 1;
            }
            pushNum(numStack, a / b);
        }
    }

    std::cout << "Result: " << popNum(numStack) << std::endl;

    return 0;

}