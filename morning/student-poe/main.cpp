#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Student {
public:
    string name;
    int id;
    float gpa;

    Student(string n, int i, float g) {
        name = n;
        id = i;
        gpa = g;
    }
};

class StudentManager {
private:
    vector<Student> students;

public:
    void addStudent() {
        string name;
        int id;
        float gpa;

        cout << "Enter student name: ";
        getline(cin, name);
        cout << "Enter student ID: ";
        cin >> id;
        cout << "Enter student GPA: ";
        cin >> gpa;
        cin.ignore(); // Ignore the newline character

        students.push_back(Student(name, id, gpa));
        cout << "Student added: " << name << ", ID: " << id << ", GPA: " << gpa << endl;
    }

    void displayAllStudents() {
        cout << "Student List:" << endl;
        for (Student s : students) {
            cout << "Name: " << s.name << ", ID: " << s.id << ", GPA: " << s.gpa << endl;
        }
    }

    void searchStudents() {
        string searchTerm;
        cout << "Enter search term (name, ID, or GPA): ";
        getline(cin, searchTerm);

        bool found = false;
        cout << "Search results:" << endl;

        // Search by name
        for (Student s : students) {
            if (s.name.find(searchTerm) != string::npos) {
                cout << "Name: " << s.name << ", ID: " << s.id << ", GPA: " << s.gpa << endl;
                found = true;
            }
        }

        // Search by ID
        for (Student s : students) {
            if (to_string(s.id).find(searchTerm) != string::npos) {
                cout << "Name: " << s.name << ", ID: " << s.id << ", GPA: " << s.gpa << endl;
                found = true;
            }
        }

        // Search by GPA
        for (Student s : students) {
            if (to_string(s.gpa).find(searchTerm) != string::npos) {
                cout << "Name: " << s.name << ", ID: " << s.id << ", GPA: " << s.gpa << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No results found." << endl;
        }
    }

    void updateStudent() {
        int id;
        float newGPA;
        cout << "Enter student ID to update: ";
        cin >> id;
        cout << "Enter new GPA: ";
        cin >> newGPA;
        cin.ignore(); // Ignore the newline character

        for (Student& s : students) {
            if (s.id == id) {
                s.gpa = newGPA;
                cout << "Student " << s.name << "'s GPA updated to " << newGPA << "." << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }
};

int main() {
    StudentManager manager;
    int choice;

    while (true) {
        cout << "\nStudent Management Application" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Students" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";

        cin >> choice;
        cin.ignore(); // Ignore the newline character

        switch (choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.displayAllStudents();
                break;
            case 3:
                manager.searchStudents();
                break;
            case 4:
                manager.updateStudent();
                break;
            case 5:
                cout << "Exiting the application..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}//
// Created by User on 20/06/2024.
//
