#include <iostream>
#include <cstring>
#include <cstdio>

struct Student {
    char surname[100];
    int group;
    int physics;
    int math;
    int informatics;
    double average;
};

int studentCount = 0;
int studentCapacity = 10;
Student* students = new Student[studentCapacity];
const char* filename = "students.txt";

void calculateAverage(Student& student) {
    student.average = (student.physics + student.math + student.informatics) / 3.0;
}

void cleanRecords() {
    delete[] students;
    students = new Student[10];
    studentCapacity = 10;
    studentCount = 0;
    std::cout << "Database cleaned. Ready to create new records\n";
}

void addRecord() {
    if (studentCount >= studentCapacity) {
        Student* newStudents = new Student[studentCapacity * 2];
        for (int i = 0; i < studentCount; i++) {
            newStudents[i] = students[i];
        }
        delete[] students;
        students = newStudents;
        studentCapacity *= 2;
    }

    Student student;
    std::cout << "Enter surname: ";
    std::cin >> student.surname;
    std::cout << "Enter group number: ";
    std::cin >> student.group;
    std::cout << "Enter physics grade: ";
    std::cin >> student.physics;
    std::cout << "Enter math grade: ";
    std::cin >> student.math;
    std::cout << "Enter informatics grade: ";
    std::cin >> student.informatics;

    calculateAverage(student);

    students[studentCount] = student;
    studentCount++;

    std::cout << "Record added\n";
}

void viewRecords() {
    if (studentCount == 0) {
        std::cout << "No records to view\n";
        return;
    }

    std::cout << "\nList of all students:\n";
    std::cout << "-------------------------\n";
    
    for (int i = 0; i < studentCount; i++) {
        std::cout << "Student #" << (i + 1) << ":\n";
        std::cout << "Surname: " << students[i].surname << std::endl;
        std::cout << "Group: " << students[i].group << std::endl;
        std::cout << "Physics: " << students[i].physics << std::endl;
        std::cout << "Math: " << students[i].math << std::endl;
        std::cout << "Informatics: " << students[i].informatics << std::endl;
        std::cout << "Average grade: " << students[i].average << std::endl;
        std::cout << "------------------------\n";
    }
    std::cout << "Total students: " << studentCount << std::endl;
}

void solveIndividualTask() {
    if (studentCount == 0) {
        std::cout << "No records for analysis\n";
        return;
    }

    int count = 0;

    std::cout << "\nStudents with physics grade 7 or 8 and math grade 9 or 10:\n";
    std::cout << "----------------------------------------------------------------\n";

    for (int i = 0; i < studentCount; i++) {
        bool physicsCondition = (students[i].physics == 7 || students[i].physics == 8);
        bool mathCondition = (students[i].math == 9 || students[i].math == 10);
        
        if (physicsCondition && mathCondition) {
            count++;
            std::cout << "Student #" << count << ":\n";
            std::cout << "Surname: " << students[i].surname << std::endl;
            std::cout << "Group: " << students[i].group << std::endl;
            std::cout << "Physics: " << students[i].physics << std::endl;
            std::cout << "Math: " << students[i].math << std::endl;
            std::cout << "Informatics: " << students[i].informatics << std::endl;
            std::cout << "Average grade: " << students[i].average << std::endl;
            std::cout << "------------------------\n";
        }
    }

    if (count > 0) {
        std::cout << "Students found: " << count << std::endl;
    } else {
        std::cout << "No students with the specified grades found\n";
    }
}

void deleteRecord() {
    if (studentCount == 0) {
        std::cout << "No records to delete\n";
        return;
    }

    int recordNumber;
    std::cout << "Enter record number to delete (1-" << studentCount << "): ";
    std::cin >> recordNumber;

    if (recordNumber < 1 || recordNumber > studentCount) {
        std::cout << "Invalid record number\n";
        return;
    }

    for (int i = recordNumber - 1; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentCount--;
    std::cout << "Record #" << recordNumber << " deleted\n";
}

void editRecord() {
    if (studentCount == 0) {
        std::cout << "No records to edit\n";
        return;
    }

    int recordNumber;
    std::cout << "Enter record number to edit (1-" << studentCount << "): ";
    std::cin >> recordNumber;

    if (recordNumber < 1 || recordNumber > studentCount) {
        std::cout << "Invalid record number\n";
        return;
    }

    Student& student = students[recordNumber - 1];

    std::cout << "Current data of record #" << recordNumber << ":\n";
    std::cout << "Surname: " << student.surname << std::endl;
    std::cout << "Group: " << student.group << std::endl;
    std::cout << "Physics: " << student.physics << std::endl;
    std::cout << "Math: " << student.math << std::endl;
    std::cout << "Informatics: " << student.informatics << std::endl;

    std::cout << "\nEnter new data:\n";
    std::cout << "Enter surname: ";
    std::cin >> student.surname;
    std::cout << "Enter group number: ";
    std::cin >> student.group;
    std::cout << "Enter physics grade: ";
    std::cin >> student.physics;
    std::cout << "Enter math grade: ";
    std::cin >> student.math;
    std::cout << "Enter informatics grade: ";
    std::cin >> student.informatics;

    calculateAverage(student);
    std::cout << "Record edited\n";
}

void sortRecords() {
    if (studentCount == 0) {
        std::cout << "No records to sort\n";
        return;
    }

    int sortChoice;
    std::cout << "\nChoose sorting type:\n";
    std::cout << "1. By surname (ascending)\n";
    std::cout << "2. By surname (descending)\n";
    std::cout << "3. By average grade (ascending)\n";
    std::cout << "4. By average grade (descending)\n";
    std::cout << "Your choice: ";
    std::cin >> sortChoice;

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            bool swap = false;
            
            if (sortChoice == 1) {
                if (strcmp(students[j].surname, students[j+1].surname) > 0) swap = true;
            } else if (sortChoice == 2) {
                if (strcmp(students[j].surname, students[j+1].surname) < 0) swap = true;
            } else if (sortChoice == 3) {
                if (students[j].average > students[j+1].average) swap = true;
            } else if (sortChoice == 4) {
                if (students[j].average < students[j+1].average) swap = true;
            } else {
                std::cout << "Invalid choice!\n";
                return;
            }
            
            if (swap) {
                Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }

    if (sortChoice == 1) std::cout << "Records sorted by surname (ascending)\n";
    else if (sortChoice == 2) std::cout << "Records sorted by surname (descending)\n";
    else if (sortChoice == 3) std::cout << "Records sorted by average grade (ascending)\n";
    else if (sortChoice == 4) std::cout << "Records sorted by average grade (descending)\n";
}

void saveToFile() {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        std::cout << "Error opening file for writing\n";
        return;
    }
    
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    
    fclose(file);
    std::cout << "Data saved to file\n";
}

void loadFromFile() {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        std::cout << "Error opening file for reading\n";
        return;
    }
    
    int count;
    fread(&count, sizeof(int), 1, file);
    
    if (count > studentCapacity) {
        delete[] students;
        studentCapacity = count * 2;
        students = new Student[studentCapacity];
    }
    
    studentCount = count;
    fread(students, sizeof(Student), studentCount, file);
    
    fclose(file);
    std::cout << "Data loaded from file\n";
}

int main() {
    int choice;
    loadFromFile();
    do {
        std::cout << "\n Student Database Management Menu\n";
        std::cout << "1. Create database (clear all records)\n";
        std::cout << "2. View all records\n";
        std::cout << "3. Add record\n";
        std::cout << "4. Delete record\n";
        std::cout << "5. Edit record\n";
        std::cout << "6. Sort records\n";
        std::cout << "7. Solve individual task\n";
        std::cout << "8. Save data to file\n";
        std::cout << "9. Load data from file\n";
        std::cout << "0. Exit\n";
        std::cout << "Select menu item: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                cleanRecords();
                break;
            case 2:
                viewRecords();
                break;
            case 3:
                addRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                editRecord();
                break;
            case 6:
                sortRecords();
                break;
            case 7:
                solveIndividualTask();
                break;
            case 8:
                saveToFile();
                break;
            case 9:
                loadFromFile();
                break;
            case 0:
                std::cout << "Exiting program\n";
                break;
            default:
                std::cout << "Invalid choice\n";
        }
    } while (choice != 0);

    delete[] students;
    return 0;
}