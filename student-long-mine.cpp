#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm> // for std::all_of
#include <cctype>    // for std::isdigit and std::isalpha


#include <iomanip>   // for std::setw
using namespace std;

struct Course {
    string course_id;
    string course_name;

    Course(string id, string name) : course_id(id), course_name(name) {}
};

struct Student {
    string student_id;
    string student_name;
    vector<Course> courses;

    Student(string id, string name) : student_id(id), student_name(name) {}
};

struct StudentNode {
    Student student;
    StudentNode* next;

    StudentNode(Student stud) : student(stud), next(nullptr) {}
};

class StudentLinkedList {
public:
    StudentNode* head;

    StudentLinkedList() : head(nullptr) {}

    void add_student(string student_id, string student_name) {
        if (!is_numeric(student_id)) {
            cout << "Student ID must be numeric." << endl;
            return;
        }
        if (!is_alpha(student_name)) {
            cout << "Student name must contain only alphabetic characters." << endl;
            return;
        }
        if (find_student(student_id)) {
            cout << "Student with ID " << student_id << " already exists." << endl;
            return;
        }
        Student new_student(student_id, student_name);
        StudentNode* new_node = new StudentNode(new_student);
        if (!head) {
            head = new_node;
        } else {
            StudentNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
        cout << "Student added successfully." << endl;
    }

    Student* find_student(string student_id) {
        StudentNode* current = head;
        while (current) {
            if (current->student.student_id == student_id) {
                return &(current->student);
            }
            current = current->next;
        }
        return nullptr;
    }

    Student* find_student_by_name(string student_name) {
        StudentNode* current = head;
        while (current) {
            if (current->student.student_name == student_name) {
                return &(current->student);
            }
            current = current->next;
        }
        return nullptr;
    }

    void enroll_in_course(string student_id, Course course) {
        Student* student = find_student(student_id);
        if (student) {
            for (const auto& c : student->courses) {
                if (c.course_id == course.course_id) {
                    cout << "Student is already enrolled in this course." << endl;
                    return;
                }
            }
            student->courses.push_back(course);
            cout << "Student enrolled in course successfully." << endl;
        } else {
            cout << "Student not found." << endl;
        }
    }

    void delete_student(string student_id) {
        if (head == nullptr) {
            cout << "Student list is empty." << endl;
            return;
        }

        if (head->student.student_id == student_id) {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Student with ID " << student_id << " deleted successfully." << endl;
            return;
        }

        StudentNode* current = head;
        while (current->next) {
            if (current->next->student.student_id == student_id) {
                StudentNode* temp = current->next;
                current->next = current->next->next;
                delete temp;
                cout << "Student with ID " << student_id << " deleted successfully." << endl;
                return;
            }
            current = current->next;
        }

        cout << "Student with ID " << student_id << " not found." << endl;
    }

    void list_students() {
        if (head == nullptr) {
            cout << "Student list is empty." << endl;
            return;
        }

        StudentNode* current = head;
        cout << "List of Students:" << endl;
        while (current) {
            cout << "Student ID: " << current->student.student_id << ", Student Name: " << current->student.student_name << endl;
            current = current->next;
        }
    }

    static bool is_numeric(const string& str) {
        return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
    }

    static bool is_alpha(const string& str) {
        return !str.empty() && all_of(str.begin(), str.end(), ::isalpha);
    }
};

class CourseManager {
public:
    vector<Course> available_courses;

    void add_course(Course course) {
        if (!StudentLinkedList::is_numeric(course.course_id)) {
            cout << "Course ID must be numeric." << endl;
            return;
        }
        if (!std::all_of(course.course_name.begin(), course.course_name.end(), ::isalpha)) {
            cout << "Course name must contain only alphabetic characters." << endl;
            return;
        }
        if (is_course_available(course.course_id)) {
            cout << "Course with ID " << course.course_id << " already exists." << endl;
            return;
        }
        available_courses.push_back(course);
        cout << "Course added successfully." << endl;
    }

    void delete_course(string course_id) {
        auto it = find_if(available_courses.begin(), available_courses.end(),
                          [course_id](const Course& c) { return c.course_id == course_id; });

        if (it != available_courses.end()) {
            available_courses.erase(it);
            cout << "Course with ID " << course_id << " deleted successfully." << endl;
        } else {
            cout << "Course with ID " << course_id << " not found." << endl;
        }
    }

    void list_courses() {
        if (available_courses.empty()) {
            cout << "Course list is empty." << endl;
            return;
        }

        cout << "List of Courses:" << endl;
        for (const auto& course : available_courses) {
            cout << "Course ID: " << course.course_id << ", Course Name: " << course.course_name << endl;
        }
    }

    bool is_course_available(string course_id) {
        for (const auto& course : available_courses) {
            if (course.course_id == course_id) {
                return true;
            }
        }
        return false;
    }

    Course* get_course(string course_id) {
        for (auto& course : available_courses) {
            if (course.course_id == course_id) {
                return &course;
            }
        }
        return nullptr;
    }
};

void enroll_student(StudentLinkedList& student_list, CourseManager& course_manager, string student_id, string course_id) {
    if (student_id.empty() || course_id.empty()) {
        cout << "Student ID and Course ID cannot be empty." << endl;
        return;
    }
    if (!StudentLinkedList::is_numeric(student_id)) {
        cout << "Student ID must be numeric." << endl;
        return;
    }
    if (!StudentLinkedList::is_numeric(course_id)) {
        cout << "Course ID must be numeric." << endl;
        return;
    }
    if (course_manager.is_course_available(course_id)) {
        Course* course = course_manager.get_course(course_id);
        if (course) {
            student_list.enroll_in_course(student_id, *course);
        }
    } else {
        cout << "Course " << course_id << " is not available." << endl;
    }
}

void search_student(StudentLinkedList& student_list, string student_name) {
    Student* student = student_list.find_student_by_name(student_name);
    if (student == nullptr) {
        cout << "Student not found!" << endl;
    } else {
        cout << left << setw(20) << "Student Name" << "Courses" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << left << setw(20) << student->student_name;
        for (size_t i = 0; i < student->courses.size(); ++i) {
            if (i != 0) cout << ", ";
            cout << student->courses[i].course_name;
        }
        cout << endl;
    }
}

void search_course(CourseManager& course_manager, string course_id) {
    Course* course = course_manager.get_course(course_id);
    if (course == nullptr) {
        cout << "Course with ID " << course_id << " not found." << endl;
    } else {
        cout << "Course ID: " << course->course_id << ", Course Name: " << course->course_name << endl;
    }
}

void save_to_csv(StudentLinkedList& student_list, const string& filename = "students.csv") {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Student ID,Student Name,Courses\n";
        StudentNode* current = student_list.head;
        while (current) {
            vector<string> course_names;
            course_names.reserve(current->student.courses.size());
            for (const auto& course : current->student.courses) {
                course_names.push_back(course.course_name);
            }
            file << current->student.student_id << "," << current->student.student_name << ",";
            for (size_t i = 0; i < course_names.size(); ++i) {
                file << course_names[i];
                if (i < course_names.size() - 1) {
                    file << "; ";
                }
            }
            file << "\n";
            current = current->next;
        }
        file.close();
        cout << "Data saved to " << filename << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}
void display_menu() {
    cout << "1. Add Course" << endl;
    cout << "2. Add Student" << endl;
    cout << "3. Enroll Student in Course" << endl;
    cout << "4. List Courses" << endl;
    cout << "5. List Students" << endl;
    cout << "6. Delete Course" << endl;
    cout << "7. Delete Student" << endl;
    cout << "8. Search Student by Name" << endl;
    cout << "9. Search Course by ID" << endl;
    cout << "10. Save Data to CSV" << endl;
    cout << "11. Exit" << endl;
    cout << "Enter your choice: ";
}
int main() {
    CourseManager course_manager;
    StudentLinkedList student_list;

    int choice;
    do {
        display_menu();
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 11: ";
        }

        switch (choice) {
            case 1: {
                string course_id, course_name;
                do {
                    cout << "Enter course ID: ";
                    cin >> course_id;
                    if (course_id.empty() || !StudentLinkedList::is_numeric(course_id)) {
                        cout << "Course ID must be numeric and non-empty." << endl;
                    }

                } while (course_id.empty() || !StudentLinkedList::is_numeric(course_id));

                cout << "Enter course name: ";
                cin.ignore();
                getline(cin, course_name);

                course_manager.add_course(Course(course_id, course_name));
                break;
            }
            case 2: {
                string student_id, student_name;
                do {
                    cout << "Enter student ID: ";
                    cin >> student_id;
                    if (student_id.empty() || !StudentLinkedList::is_numeric(student_id)) {
                        cout << "Student ID must be numeric and non-empty." << endl;
                    }
                } while (student_id.empty() || !StudentLinkedList::is_numeric(student_id));

                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, student_name);

                student_list.add_student(student_id, student_name);
                break;
            }
            case 3: {
                string student_id, course_id;
                cout << "Enter student ID: ";
                cin >> student_id;
                cout << "Enter course ID: ";
                cin >> course_id;

                enroll_student(student_list, course_manager, student_id, course_id);
                break;
            }
            case 4: {
                course_manager.list_courses();
                break;
            }
            case 5: {
                student_list.list_students();
                break;
            }
            case 6: {
                string course_id;
                cout << "Enter course ID to delete: ";
                cin >> course_id;

                course_manager.delete_course(course_id);
                break;
            }
            case 7: {
                string student_id;
                cout << "Enter student ID to delete: ";
                cin >> student_id;

                student_list.delete_student(student_id);
                break;
            }
            case 8: {
                string student_name;
                cout << "Enter student name to search: ";
                cin.ignore();
                getline(cin, student_name);

                search_student(student_list, student_name);
                break;
            }
            case 9: {
                string course_id;
                cout << "Enter course ID to search: ";
                cin >> course_id;

                search_course(course_manager, course_id);
                break;
            }
            case 10: {
                save_to_csv(student_list);
                break;
            }
            case 11: {
                cout << "Exiting program..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please enter a number between 1 and 11." << endl;
        }
    } while (choice != 11);

    return 0;
}