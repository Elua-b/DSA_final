#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#define FILE_NAME "patient.txt"
using namespace std;
// import integer
typedef int integer;
// patient class to hold patient details
class Patient {
private:
    int id;
    string name;
    string dob;
    string gender;
public:
    // Constructor to initialize patient details
    Patient(int id, string name , string dob,string gender) :
            id(id),
            name(name),
            dob(dob),
            gender(gender){};
    // Getter for patient ID
    int getId() {
        return id;
    }
    // Getter for patient's first name
    string getName() {
        return name;
    }
    // Getter for patient's last name
    string getDob() {
        return dob;
    }
    // Getter for patient's full name
    string getGender() {
        return gender;
    }
    // Setter for patient's first name
    void setName(string newFirstName) {
        name = newFirstName;
    }
};
class Doctor {
private:
    int id;
    string name;
    string specialization;
    string gender;
public:
    // Constructor to initialize patient details
    Doctor(int id, string name , string specialization) :
            id(id),
            name(name),
            specialization(specialization){}
    // Getter for doctor ID
    int getId() {
        return id;
    }
    // Getter for doctor's first name
    string getName() {
        return name;
    }
};
// class Apppointments {
// private:
//     int appointment_id;
//     int patient_id;
//     int doctor_id;
//     string appointment_date;
// public:
//     // Constructor to initialize patient details
//    Apppointments(int appointment_id, int patient_id , int doctor_id , string appointment_id) :
//             id(id),
//             name(name),
//             specialization(specialization){}
//     // Getter for doctor ID
//     int getId() {
//         return id;
//     }
//     // Getter for doctor's first name
//     string getName() {
//         return name;
//     }
// };
void startMessage(){
    cout<<" Menu: "<<endl;
    cout<<"1. Register a patient: "<<endl;
    cout<<"2. Register a doctor: "<<endl;
    cout<<"3. Register an appointment: "<<endl;
    cout<<"4. Display patients: "<<endl;
    cout<<"5. Display Doctors: "<<endl;
    cout<<"6. Display Appointments: "<<endl;
    cout<<"7. Exit: "<<endl;
}
// Node class for linked list
class Node {
public:
    Patient patient;
    Node* next;
    Node(Patient patient) : patient(patient), next(nullptr) {}
};
// Node class for linked list
class Node2 {
public:
    Doctor doctor;
    Node2* next;
    Node2(Doctor doctor):doctor(doctor), next(nullptr) {}
};
class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}
    // Function to add a patient to the list
    void addpatient(Patient patient) {
        Node* newNode = new Node(patient);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    // Function to print the list of patients
    void printPatients() {
        cout << "patients" << endl;
        cout << "---------------------" << endl;
        Node* temp = head;
        int index = 1;
        while (temp) {
            cout << "(" << index << ") : " << temp->patient.getId() << " " << temp->patient.getName() << " " << temp->patient.getGender() << endl;
            temp = temp->next;
            index++;
        }
        cout << "---------------------" << endl;
    }
    // Function to find a patient by ID
    bool isIdTaken(int id) {
        Node* temp = head;
        while (temp) {
            if (temp->patient.getId() == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};
// Function to validate name (no numbers allowed)
bool isValidName(string name) {
    return regex_match(name, regex("^[A-Za-z]+$"));
};
void processCommands() {
    LinkedList patientList;
    string input;
    string command;
    do {
        cout << ">";
        getline(cin, input);
        istringstream iss(input);
        iss >> command;
        // Convert the command to lowercase for case-insensitive comparison
        for (size_t i = 0; i < command.length(); i++) {
            command[i] = tolower(command[i]);
        }
        // Process the command
        if (command == "1") {
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
            patientList. printPatients();
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
        } else if (command == "2") {
            int number_of_patients;
            cout << "How many patients do you want to add?" << endl;
            cin >> number_of_patients;
            cin.ignore(); // Ignore the newline character left in the buffer
            cout << "Enter patients data in format : <patient_id> <name> <dob> <gender>" << endl;
            // Get patients data
            for (int i = 0; i < number_of_patients; i++) {
                string input, id, name, dob, gender;
                cout << "Enter the data for patient (" << i + 1 << ")" << endl;
                getline(cin, input);
                istringstream patient_ss(input);
                if (patient_ss >> id >> name >> dob>> gender) {
                    // Validate names
                    if (!isValidName(name)) {
                        cerr << "Invalid name format. Names must contain only letters." << endl;
                        i--; // Ask for the current patient data again
                        continue;
                    }
                    // Check if ID is taken, if so prompt to enter a different ID
                    if (patientList.isIdTaken(stoi(id))) {
                        cerr << "A patient with ID " << id << " already exists. Please use a different ID." << endl;
                        i--; // Ask for the current patient data again
                    } else {
                        Patient patient(stoi(id), name, dob, stof(gender));
                        patientList.addpatient(patient);
                        cout<<"try again taken"<<endl;
                    }
                } else {
                    cerr << "Invalid input format" << endl;
                    i--; // Ask for the current patient data again
                }
            }
            cout << "Finished adding patients" << endl;
        } else {
            // Invalid command entered
            if (command != "exit") {
                cout << "Invalid command. Below is the help option to provide you a list of commands." << endl;
            }
        }
    } while (command != "exit");
}
int main(){
    startMessage();
    processCommands();
    return 0;
}