#include <iostream>
#include <cstring>
#include <cstdio>

struct Student {
    char surname[100];
};

struct Speciality {
    char name[100];
    Student* students;
    int studentCount;
    int studentCapacity;
};

struct Faculty {
    char name[100];
    Speciality* specialities;
    int specialityCount;
    int specialityCapacity;
};

struct University {
    char name[100];
    Faculty* faculties;
    int facultyCount;
    int facultyCapacity;
};

University university;
const char* filename = "university.txt";

// Initialize university
void initUniversity() {
    std::cout << "Enter university name: ";
    std::cin.ignore(); // Clear buffer
    std::cin.getline(university.name, 100);
    
    university.facultyCapacity = 5;
    university.facultyCount = 0;
    university.faculties = new Faculty[university.facultyCapacity];
    
    std::cout << "University '" << university.name << "' created.\n";
}

// Functions for managing faculties
void addFaculty() {
    if (university.facultyCount >= university.facultyCapacity) {
        Faculty* newFaculties = new Faculty[university.facultyCapacity * 2];
        for (int i = 0; i < university.facultyCount; i++) {
            newFaculties[i] = university.faculties[i];
        }
        delete[] university.faculties;
        university.faculties = newFaculties;
        university.facultyCapacity *= 2;
    }

    Faculty& faculty = university.faculties[university.facultyCount];
    
    std::cout << "Enter faculty name: ";
    std::cin.ignore();
    std::cin.getline(faculty.name, 100);
    
    faculty.specialityCapacity = 5;
    faculty.specialityCount = 0;
    faculty.specialities = new Speciality[faculty.specialityCapacity];
    
    university.facultyCount++;
    std::cout << "Faculty '" << faculty.name << "' added.\n";
}

void addSpeciality(int facultyIndex) {
    if (facultyIndex < 0 || facultyIndex >= university.facultyCount) {
        std::cout << "Invalid faculty index\n";
        return;
    }
    
    Faculty& faculty = university.faculties[facultyIndex];
    
    if (faculty.specialityCount >= faculty.specialityCapacity) {
        Speciality* newSpecialities = new Speciality[faculty.specialityCapacity * 2];
        for (int i = 0; i < faculty.specialityCount; i++) {
            newSpecialities[i] = faculty.specialities[i];
        }
        delete[] faculty.specialities;
        faculty.specialities = newSpecialities;
        faculty.specialityCapacity *= 2;
    }
    
    Speciality& speciality = faculty.specialities[faculty.specialityCount];
    
    std::cout << "Enter speciality name: ";
    std::cin.ignore();
    std::cin.getline(speciality.name, 100);
    
    speciality.studentCapacity = 10;
    speciality.studentCount = 0;
    speciality.students = new Student[speciality.studentCapacity];
    
    faculty.specialityCount++;
    std::cout << "Speciality '" << speciality.name 
              << "' added to faculty '" << faculty.name << "'\n";
}

void addStudent(int facultyIndex, int specialityIndex) {
    if (facultyIndex < 0 || facultyIndex >= university.facultyCount) {
        std::cout << "Invalid faculty index\n";
        return;
    }
    
    Faculty& faculty = university.faculties[facultyIndex];
    
    if (specialityIndex < 0 || specialityIndex >= faculty.specialityCount) {
        std::cout << "Invalid speciality index\n";
        return;
    }
    
    Speciality& speciality = faculty.specialities[specialityIndex];
    
    if (speciality.studentCount >= speciality.studentCapacity) {
        Student* newStudents = new Student[speciality.studentCapacity * 2];
        for (int i = 0; i < speciality.studentCount; i++) {
            newStudents[i] = speciality.students[i];
        }
        delete[] speciality.students;
        speciality.students = newStudents;
        speciality.studentCapacity *= 2;
    }
    
    Student& student = speciality.students[speciality.studentCount];
    
    std::cout << "Enter student surname: ";
    std::cin.ignore();
    std::cin.getline(student.surname, 100);
    
    speciality.studentCount++;
    
    std::cout << "Student '" << student.surname << "' added to speciality '" 
              << speciality.name << "' of faculty '" << faculty.name << "'\n";
}

// View all data
void viewAllData() {
    std::cout << "\n-------------------------------------------\n";
    std::cout << "UNIVERSITY: " << university.name << std::endl;
    std::cout << "--------------------------------------------\n\n";
    
    if (university.facultyCount == 0) {
        std::cout << "University has no faculties\n";
        return;
    }
    
    for (int i = 0; i < university.facultyCount; i++) {
        Faculty& faculty = university.faculties[i];
        std::cout << "FACULTY #" << (i+1) << ": " << faculty.name << std::endl;
        std::cout << "-------------------------------------------\n";
        
        if (faculty.specialityCount == 0) {
            std::cout << "Faculty has no specialities\n";
        } else {
            for (int j = 0; j < faculty.specialityCount; j++) {
                Speciality& speciality = faculty.specialities[j];
                std::cout << "  SPECIALITY #" << (j+1) << ": " << speciality.name << "\n";
                
                if (speciality.studentCount == 0) {
                    std::cout << "    No students\n";
                } else {
                    std::cout << "    STUDENTS (" << speciality.studentCount << "):\n";
                    for (int k = 0; k < speciality.studentCount; k++) {
                        Student& student = speciality.students[k];
                        std::cout << "    - " << student.surname << std::endl;
                    }
                }
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "Total faculties: " << university.facultyCount << std::endl;
}

// Delete student
void deleteStudent() {
    std::cout << "\nDELETE STUDENT\n";
    
    if (university.facultyCount == 0) {
        std::cout << "University has no faculties\n";
        return;
    }
    
    std::cout << "Enter faculty index (1-" << university.facultyCount << "): ";
    int facultyIndex;
    std::cin >> facultyIndex;
    facultyIndex--; // Convert to 0-indexing
    
    if (facultyIndex < 0 || facultyIndex >= university.facultyCount) {
        std::cout << "Invalid faculty index\n";
        return;
    }
    
    Faculty& faculty = university.faculties[facultyIndex];
    std::cout << "Faculty: " << faculty.name << std::endl;
    
    if (faculty.specialityCount == 0) {
        std::cout << "Faculty has no specialities\n";
        return;
    }
    
    std::cout << "Enter speciality index (1-" << faculty.specialityCount << "): ";
    int specialityIndex;
    std::cin >> specialityIndex;
    specialityIndex--;
    
    if (specialityIndex < 0 || specialityIndex >= faculty.specialityCount) {
        std::cout << "Invalid speciality index\n";
        return;
    }
    
    Speciality& speciality = faculty.specialities[specialityIndex];
    std::cout << "Speciality: " << speciality.name << std::endl;
    
    if (speciality.studentCount == 0) {
        std::cout << "This speciality has no students\n";
        return;
    }
    
    std::cout << "Enter student index (1-" << speciality.studentCount << "): ";
    int studentIndex;
    std::cin >> studentIndex;
    studentIndex--;
    
    if (studentIndex < 0 || studentIndex >= speciality.studentCount) {
        std::cout << "Invalid student index\n";
        return;
    }
    
    // Delete student
    for (int i = studentIndex; i < speciality.studentCount - 1; i++) {
        speciality.students[i] = speciality.students[i + 1];
    }
    speciality.studentCount--;
    
    std::cout << "Student deleted\n";
}

// Edit student
void editStudent() {
    std::cout << "\nEDIT STUDENT\n";
    
    if (university.facultyCount == 0) {
        std::cout << "University has no faculties\n";
        return;
    }
    
    std::cout << "Enter faculty index (1-" << university.facultyCount << "): ";
    int facultyIndex;
    std::cin >> facultyIndex;
    facultyIndex--;
    
    if (facultyIndex < 0 || facultyIndex >= university.facultyCount) {
        std::cout << "Invalid faculty index\n";
        return;
    }
    
    Faculty& faculty = university.faculties[facultyIndex];
    std::cout << "Faculty: " << faculty.name << std::endl;
    
    if (faculty.specialityCount == 0) {
        std::cout << "Faculty has no specialities\n";
        return;
    }
    
    std::cout << "Enter speciality index (1-" << faculty.specialityCount << "): ";
    int specialityIndex;
    std::cin >> specialityIndex;
    specialityIndex--;
    
    if (specialityIndex < 0 || specialityIndex >= faculty.specialityCount) {
        std::cout << "Invalid speciality index\n";
        return;
    }
    
    Speciality& speciality = faculty.specialities[specialityIndex];
    std::cout << "Speciality: " << speciality.name << std::endl;
    
    if (speciality.studentCount == 0) {
        std::cout << "This speciality has no students\n";
        return;
    }
    
    std::cout << "Enter student index (1-" << speciality.studentCount << "): ";
    int studentIndex;
    std::cin >> studentIndex;
    studentIndex--;
    
    if (studentIndex < 0 || studentIndex >= speciality.studentCount) {
        std::cout << "Invalid student index\n";
        return;
    }
    
    Student& student = speciality.students[studentIndex];
    
    std::cout << "\nCurrent student data:\n";
    std::cout << "Surname: " << student.surname << std::endl;
    
    std::cout << "\nEnter new data:\n";
    std::cout << "Enter surname: ";
    std::cin.ignore();
    std::cin.getline(student.surname, 100);
    
    std::cout << "Student data updated\n";
}

// Sort students by surname
void sortStudents(int facultyIndex, int specialityIndex) {
    if (facultyIndex < 0 || facultyIndex >= university.facultyCount) {
        std::cout << "Invalid faculty index\n";
        return;
    }
    
    Faculty& faculty = university.faculties[facultyIndex];
    
    if (specialityIndex < 0 || specialityIndex >= faculty.specialityCount) {
        std::cout << "Invalid speciality index\n";
        return;
    }
    
    Speciality& speciality = faculty.specialities[specialityIndex];
    
    if (speciality.studentCount < 2) {
        std::cout << "Not enough students to sort\n";
        return;
    }
    
    int sortChoice;
    std::cout << "\nChoose sorting type:\n";
    std::cout << "1. By surname (ascending)\n";
    std::cout << "2. By surname (descending)\n";
    std::cout << "Your choice: ";
    std::cin >> sortChoice;
    
    for (int i = 0; i < speciality.studentCount - 1; i++) {
        for (int j = 0; j < speciality.studentCount - i - 1; j++) {
            bool swap = false;
            
            if (sortChoice == 1) {
                if (strcmp(speciality.students[j].surname, speciality.students[j+1].surname) > 0) swap = true;
            } else if (sortChoice == 2) {
                if (strcmp(speciality.students[j].surname, speciality.students[j+1].surname) < 0) swap = true;
            } else {
                std::cout << "Invalid choice!\n";
                return;
            }
            
            if (swap) {
                Student temp = speciality.students[j];
                speciality.students[j] = speciality.students[j+1];
                speciality.students[j+1] = temp;
            }
        }
    }
    
    std::cout << "Students sorted\n";
}

// Save to file
void saveToFile() {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        std::cout << "Error opening file for writing\n";
        return;
    }
    
    // Save university data
    fwrite(&university, sizeof(University), 1, file);
    
    // Save faculties
    for (int i = 0; i < university.facultyCount; i++) {
        Faculty& faculty = university.faculties[i];
        fwrite(&faculty, sizeof(Faculty), 1, file);
        
        // Save specialities for each faculty
        for (int j = 0; j < faculty.specialityCount; j++) {
            Speciality& speciality = faculty.specialities[j];
            fwrite(&speciality, sizeof(Speciality), 1, file);
            
            // Save students for each speciality
            fwrite(speciality.students, sizeof(Student), speciality.studentCount, file);
        }
    }
    
    fclose(file);
    std::cout << "Data saved to file\n";
}

// Load from file
void loadFromFile() {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        std::cout << "Error opening file for reading or file does not exist\n";
        return;
    }
    
    // Clear current data
    // Clear all students
    for (int i = 0; i < university.facultyCount; i++) {
        Faculty& faculty = university.faculties[i];
        for (int j = 0; j < faculty.specialityCount; j++) {
            Speciality& speciality = faculty.specialities[j];
            delete[] speciality.students;
        }
        delete[] faculty.specialities;
    }
    
    // Clear faculties
    delete[] university.faculties;
    
    // Load university data
    fread(&university, sizeof(University), 1, file);
    
    // Allocate memory for faculties
    university.faculties = new Faculty[university.facultyCapacity];
    
    // Load faculties
    for (int i = 0; i < university.facultyCount; i++) {
        Faculty& faculty = university.faculties[i];
        fread(&faculty, sizeof(Faculty), 1, file);
        
        // Allocate memory for specialities
        faculty.specialities = new Speciality[faculty.specialityCapacity];
        
        // Load specialities for each faculty
        for (int j = 0; j < faculty.specialityCount; j++) {
            Speciality& speciality = faculty.specialities[j];
            fread(&speciality, sizeof(Speciality), 1, file);
            
            // Allocate memory for students
            speciality.students = new Student[speciality.studentCapacity];
            
            // Load students for each speciality
            fread(speciality.students, sizeof(Student), speciality.studentCount, file);
        }
    }
    
    fclose(file);
    std::cout << "Data loaded from file\n";
}

// Clean up memory
void cleanup() {
    // Clear all students
    for (int i = 0; i < university.facultyCount; i++) {
        Faculty& faculty = university.faculties[i];
        for (int j = 0; j < faculty.specialityCount; j++) {
            Speciality& speciality = faculty.specialities[j];
            delete[] speciality.students;
        }
        delete[] faculty.specialities;
    }
    
    // Clear faculties
    delete[] university.faculties;
}

int main() {
    // Create BSUIR university by default
    strcpy(university.name, "BSUIR");
    university.facultyCapacity = 5;
    university.facultyCount = 0;
    university.faculties = new Faculty[university.facultyCapacity];
    
    std::cout << "University created: " << university.name << "\n";
    
    int choice;
    do {
        std::cout << "\n-------------------------------------------\n";
        std::cout << "UNIVERSITY MANAGEMENT SYSTEM '" << university.name << "'\n";
        std::cout << "-------------------------------------------\n";
        std::cout << "1. Add faculty\n";
        std::cout << "2. Add speciality to faculty\n";
        std::cout << "3. Add student to speciality\n";
        std::cout << "4. View all data\n";
        std::cout << "5. Delete student\n";
        std::cout << "6. Edit student\n";
        std::cout << "7. Sort students on speciality\n";
        std::cout << "8. Save data to file\n";
        std::cout << "9. Load data from file\n";
        std::cout << "0. Exit\n";
        std::cout << "Select menu item: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addFaculty();
                break;
            case 2:
                if (university.facultyCount == 0) {
                    std::cout << "Add at least one faculty first!\n";
                } else {
                    std::cout << "Enter faculty index (1-" << university.facultyCount << "): ";
                    int index;
                    std::cin >> index;
                    addSpeciality(index - 1);
                }
                break;
            case 3:
                if (university.facultyCount == 0) {
                    std::cout << "Add at least one faculty first!\n";
                } else {
                    std::cout << "Enter faculty index (1-" << university.facultyCount << "): ";
                    int facIndex;
                    std::cin >> facIndex;
                    std::cout << "Enter speciality index: ";
                    int specIndex;
                    std::cin >> specIndex;
                    addStudent(facIndex - 1, specIndex - 1);
                }
                break;
            case 4:
                viewAllData();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                editStudent();
                break;
            case 7:
                if (university.facultyCount == 0) {
                    std::cout << "Add at least one faculty first!\n";
                } else {
                    std::cout << "Enter faculty index (1-" << university.facultyCount << "): ";
                    int facIndex;
                    std::cin >> facIndex;
                    std::cout << "Enter speciality index: ";
                    int specIndex;
                    std::cin >> specIndex;
                    sortStudents(facIndex - 1, specIndex - 1);
                }
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

    cleanup();
    return 0;
}