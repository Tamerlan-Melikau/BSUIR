#include <iostream>
#include <cstring>

struct Tree{
    int info;
    Tree* left;
    Tree* right;
    int number;
    char name[30];
};

Tree* List(int inf) {
    Tree *t = new Tree;
    t->info = inf;
    t->left = NULL;
    t->right = NULL;
    t->name[0] = '\0';
    return t;
}

void Add_List(Tree*& root, int key) {
    if(root == NULL) {
        root = List(key);
        return;
    }
    
    Tree* current = root;
    Tree* parent = NULL;
    
    while(current != NULL) {
        parent = current;
        
        if (key == current->info) {
            std::cout << "Duplicate Key: " << key << std::endl;
            return;
        }
        else if (key < current->info){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    
    Tree* newNode = List(key);
    if(key < parent->info){
        parent->left = newNode;
    }
    else{
        parent->right = newNode;
    }
}

void PrintTree(Tree* root, std::string indent = "", bool isLeft = true) {
    if (root == NULL) return;
    
    PrintTree(root->right, indent + (isLeft ? "│   " : "    "), false);
    
    std::cout << indent;
    if (isLeft) {
        std::cout << "└── ";
    } else {
        std::cout << "┌── ";
    }
    std::cout << root->info;
    if (root->name[0] != '\0') {
        std::cout << " [" << root->name << "]";
    }
    std::cout << std::endl;
    
    PrintTree(root->left, indent + (isLeft ? "    " : "│   "), true);
}

Tree* findNode(Tree* root, int key) {
    Tree* current = root;
    while (current != NULL) {
        if (key == current->info) {
            return current;
        }
        else if (key < current->info) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return NULL;
}

void addInfo(Tree*& root) {
    int n;
    std::cout << "Do u want to add? (Yes - 1): ";
    std::cin >> n;

    while(n == 1){
        int number;
        char name[30];
        
        std::cout << "Enter number: ";
        std::cin >> number;
        
        Tree* existingNode = findNode(root, number);
        if (existingNode != NULL) {
            std::cout << "Node with this key already exists\n";
            std::cout << "Do u want to change name?(1 - Yes)\n";
            int choces;
            std::cin >> choces;
            if(choces == 1){
                std::cout << "Enter name: ";
                std::cin >> existingNode->name;
            }
        } else {
            std::cout << "Enter name: ";
            std::cin >> name;
            Add_List(root, number);
            Tree* newNode = findNode(root, number);
            strcpy(newNode->name, name);
        }
        std::cout << "Do u want to add? (Yes - 1): ";
        std::cin >> n;
    }
}

void findInfoByKey(Tree* root) {
    int key;
    std::cout << "Enter number of key: ";
    std::cin >> key;
    
    Tree* node = findNode(root, key);
    if (node != NULL) {
        std::cout << "Info by key: " << node->name << std::endl;
    } else {
        std::cout << "Key not found\n";
    }
}

Tree* findMin(Tree* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Tree* deleteNode(Tree* root, int key) {
    if (root == NULL) return NULL;
    
    if (key < root->info) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->info) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == NULL) {
            Tree* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Tree* temp = root->left;
            delete root;
            return temp;
        }
        
        Tree* temp = findMin(root->right);
        root->info = temp->info;
        strcpy(root->name, temp->name);
        root->right = deleteNode(root->right, temp->info);
    }
    return root;
}

void deleteInfoByKey(Tree*& root) {
    if (root == NULL) {
        std::cout << "Tree is empty\n";
        return;
    }
    int key;
    std::cout << "Enter key to delete: ";
    std::cin >> key;
    Tree* node = findNode(root, key);
    if (node == NULL) {
        std::cout << "Key not found\n";
        return;
    }
    root = deleteNode(root, key);
}

void printAllInfo(Tree* root) {
    if (root == NULL) {
        std::cout << "Tree is empty\n";
        return;
    }
    
    std::cout << "\nTree structure:\n";
    PrintTree(root);
}

void printPreOrder(Tree* root) {
    if (root == NULL) return;
    std::cout << root->info;
    if (root->name[0] != '\0') {
        std::cout << " (" << root->name << ")";
    }
    std::cout << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(Tree* root) {
    if (root == NULL) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    std::cout << root->info;
    if (root->name[0] != '\0') {
        std::cout << " (" << root->name << ")";
    }
    std::cout << " ";
}

void printInOrder(Tree* root) {
    if (root == NULL) return;
    printInOrder(root->left);
    std::cout << root->info;
    if (root->name[0] != '\0') {
        std::cout << " (" << root->name << ")";
    }
    std::cout << " ";
    printInOrder(root->right);
}

void printAllTraversals(Tree* root) {
    if (root == NULL) {
        std::cout << "Tree is empty.\n";
        return;
    }
        
    std::cout << "\n1. Прямой обход:\n";
    printPreOrder(root);
    std::cout << std::endl;
    
    std::cout << "\n2. Обратный обход:\n";
    printPostOrder(root);
    std::cout << std::endl;
    
    std::cout << "\n3. Симметричный обход:\n";
    printInOrder(root);
    std::cout << std::endl;
}

int task(Tree* root) {
    if (root == NULL) return 0;
    int count = 0;

    if (root->left != NULL && root->right != NULL) {
        count = 1;
    }
    
    return count + task(root->left) + task(root->right);
}

int main() {
    Tree* root = NULL;
    addInfo(root);

    if (root != NULL) {
        std::cout << "\nInitial tree:" << std::endl;
        PrintTree(root);
    } else {
        std::cout << "Tree is empty" << std::endl;
    }

    while (true){
        std::cout << "\n=== Menu ===\n";
        std::cout << "1. Add info\n";
        std::cout << "2. Find info by key\n";
        std::cout << "3. Delete info by key\n";
        std::cout << "4. Print tree\n";
        std::cout << "5. Make a task\n";
        std::cout << "6. Print records\n";

        int choice;
        std::cout << "Enter number: ";
        std::cin >> choice;

        switch (choice){
        case 1:
            addInfo(root);
            PrintTree(root);
            break;
            
        case 2:
            findInfoByKey(root);
            break;
            
        case 3:
            deleteInfoByKey(root);
            break;
            
        case 4:
            printAllInfo(root);
            break;
            
        case 5: {
            int count = task(root);
            std::cout << "Number of nodes with two children: " << count << std::endl;
            break;
        }
        case 6:
            printAllTraversals(root);
            break;
            
        case 0:
            std::cout << "Program finished\n";
            return 0;
            
        default:
            std::cout << "Invalid choice! Try again\n";
            break; 
        }
    }
    
    return 0;
}