// importing libraries
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//import integer
typedef int integer;
//using namespace std
using namespace std;
//creating a struct for patient, doctor and appointment
struct Patient{
    integer id;
    string name;
    string dob;
    string gender;

    Patient(integer id,  string &name,  string &dob,  string &gender) :  id(id),name(name),dob(dob),gender(gender){}

};
struct Doctor {
    integer id;
    string name;
    string specialization;

    Doctor(integer id,  string &name,  string &specialization) : id(id), name(name), specialization(specialization) {}
};
struct Appointment {
    integer id;
    integer patient_id;
    integer doctor_id;
    string date;

    Appointment(integer id, integer patient_id, integer doctor_id,  string &date) : id(id), patient_id(patient_id), doctor_id(doctor_id), date(date) {}
};
//creating a linked list for doctor, patient and appointment
//doctor node
struct Doctor_node {
    Doctor data;
    Doctor_node* next;
    Doctor_node(Doctor data):data(data), next(nullptr){
    }
};
//patient node
struct Patient_node {
     Patient data;
     Patient_node* next;


     Patient_node(Patient data):data(data), next(nullptr){}
};
//doctorLinkedList
struct Doctor_linked_list {
     Doctor_node* head;
    Doctor_linked_list() {
        this->head = NULL;
    }
       //add doctor
    void add_doctor(Doctor data) {
        Doctor_node* new_doctor = new Doctor_node(data);
        if (this->head == NULL) {
            this->head = new_doctor;
        } else {
            Doctor_node* temp = this->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_doctor;
        }
    }
    //verify if id added exists
     bool verify_id(integer id) {
        Doctor_node* temp = this->head;
        while (temp != NULL) {
            if (temp->data.id == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    //display doctors
    void display_doctors() {
        Doctor_node* temp = this->head;
        cout << "AVAILABLE DOCTORS:" <<  endl;
        cout << "----------------------------"<<endl;
        cout << "----------------------------"<<endl;
        //if no doctor found
        if (temp == NULL) {
            cout << "No doctors available" << endl;
            return;
        }
        while (temp != NULL) {
            cout << "Doctor ID: " << temp->data.id << ",";
            cout << "Doctor Name: " << temp->data.name << ",";
            cout << "Doctor Specialization: " << temp->data.specialization << endl;
            cout << "---------------------------------" << endl;
            temp = temp->next;
        }

    }

};

//patientLinkedList
struct Patient_linked_list {
    Patient_node* head;
    Patient_linked_list() {
        this->head = NULL;
    }
    //add patient function
    void add_patient(Patient data) {
        Patient_node* new_patient = new Patient_node(data);
        if (this->head == NULL) {
            this->head = new_patient;
        } else {
            Patient_node* temp = this->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_patient;
        }
    }
    //validate if id is anumber
    bool is_number(const string& s) {
        return !s.empty() && std::find_if(s.begin(),
            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }
    //verify if date is in  providded format
    bool is_date(const string& s) {
        if (s.length() != 10) {
            return false;
        }
        if (s[4] != '-' || s[7] != '-') {
            return false;
        }
        if (!is_number(s.substr(0, 4)) || !is_number(s.substr(5, 2)) || !is_number(s.substr(8, 2))) {
            return false;
        }
        return true;
    }
    //verify if id added exists
      bool verify_id(integer id) {
        Patient_node* temp = this->head;
        while (temp != NULL) {
            if (temp->data.id == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    //display patients
    void display_patients() {
        Patient_node* temp = this->head;
        cout << "AVAILABLE PATIENTS:" <<  endl;
        cout << "----------------------------"<<endl;
        cout << "----------------------------"<<endl;
        //if no patient found
        if (temp == NULL) {
            cout << "No patients available" << endl;
            return;
        }
        while (temp != NULL) {
            cout << "Patient ID: " << temp->data.id <<  ",";;
            cout << "Patient Name: " << temp->data.name <<  ",";;
            cout << "Patient DOB: " << temp->data.dob << endl;
            cout << "---------------------------------" << endl;
            temp = temp->next;
        }
    }
};
//appointment node
struct Appointment_node {
    Appointment data;
    Appointment_node* next;
    Appointment_node(Appointment data):data(data), next(nullptr){
    }
};
//appointmentLinkedList
struct Appointment_linked_list {
    Appointment_node* head;
    Appointment_linked_list() {
        this->head = NULL;
    }
    //add appointment function
    void add_appointment(Appointment data) {
        Appointment_node* new_appointment = new Appointment_node(data);
        if (this->head == NULL) {
            this->head = new_appointment;
        } else {
            Appointment_node* temp = this->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_appointment;
        }
    }
    //verify if id added exists
    bool verify_id(integer id) {
        Appointment_node* temp = this->head;
        while (temp != NULL) {
            if (temp->data.id == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
//display appointments
    void display_appointments() {
        Appointment_node* temp = this->head;
        cout <<"AVAILABLE APPOINTMENTS:" <<  endl;
        cout <<"----------------------------"<<endl;
        cout << "----------------------------"<<endl;

    //if no appointment found
        if (temp == NULL) {
            cout << "No appointments available" << endl;
            return;
        }
    while (temp != NULL) {

            cout << "Appointment ID: " << temp->data.id <<  ",";
            cout << "Patient ID: " << temp->data.patient_id <<  ",";
            cout << "Doctor ID: " << temp->data.doctor_id <<  ",";
            cout << "Date: " << temp->data.date << endl;
            cout << "---------------------------------" << endl;
            temp = temp->next;
        }
    }
};
//main function

int main (){
 // implement all what was done above
    Doctor_linked_list doctors;
    Patient_linked_list patients;
    Appointment_linked_list appointments;
    int choice;
    cout<<"Welcome to --------"<<endl;
    cout << "Ruhengeri  Hospital Management System" << endl;
    cout << "---------------------------------" << endl;
    cout << "----------------------------"<<endl;
    do {


         cout << "Menu:" << endl;
        cout << "1. REGISTER a Doctor" << endl;
        cout << "2. REGISTER a Patient" << endl;
        cout << "3. REGISTER an  Appointment" << endl;
        cout << "4. Display Doctors" << endl;
        cout << "5. Display Patients" << endl;
        cout << "6. Display Appointments" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
        int id;
        string name;
        string specialization;
        cout<<"DOCTOR REGISTRATION"<<endl;
        cout<<"---------------------"<<endl;
        cout << "Enter Doctor ID: ";
        cin >> id;
        cout << "Enter Doctor Name: ";
        cin >> name;
        cout << "Enter Doctor Specialization: ";
        cin >> specialization;
        ///verify if doctor exists by id
        if(doctors.verify_id(id)){
            cout<<"Doctor already exists"<<endl;
            break;
        }
        if(specialization.empty()){
            cout<<"Specialization cannot be empty"<<endl;
            break;
        }
        if(name.empty()){
            cout<<"Name cannot be empty"<<endl;
            break;
        }

        Doctor new_doctor(id, name, specialization);
        doctors.add_doctor(new_doctor);
        cout<<"---Doctor added successfully---"<<endl;
        break;
        }
        case 2: {
        int id;
        string name;
        string dob;
        string gender;
        cout<<"PATIENT REGISTRATION"<<endl;
        cout<<"---------------------"<<endl;
        cout << "Enter Patient ID: ";
        cin >> id;
        cout << "Enter Patient Name: ";
        cin >> name;
        cout << "Enter Patient DOB(YYYY-MM-DD) : ";
        cin >> dob;
        cout<<"Enter Patient Gender: ";
        cin>>gender;
        ///verify if patient exists by id
        if(patients.verify_id(id)){
            cout<<"Patient already exists"<<endl;
            break;
        }
        if(dob.empty()){
            cout<<"DOB cannot be empty"<<endl;
            break;
        }
        if(name.empty()){
            cout<<"Name cannot be empty"<<endl;
            break;
        }
        if(gender.empty()){
            cout<<"Gender cannot be empty"<<endl;
        }
        Patient new_patient(id, name, dob,gender);
        patients.add_patient(new_patient);
        cout<<"---Patient added successfully---"<<endl;
        break;
        }
        case 3: {
        int id;
        int patient_id;
        int doctor_id;
        string date;
        cout<<"APPOINTMENT REGISTRATION"<<endl;
        cout<<"---------------------"<<endl;
        cout << "Enter Appointment ID: ";
        cin >> id;
        cout << "Enter Patient ID: ";
        cin >> patient_id;
        cout << "Enter Doctor ID: ";
        cin >> doctor_id;
        cout << "Enter Date(YYYY-MM-DD): ";
        cin >> date;
        if(!patients.verify_id(patient_id)){
            cout<<"Either Patient or Doctor does not exist"<<endl;
            break;
        }
        if(!doctors.verify_id(doctor_id)){
            cout<<"Either Patient or Doctor does not exist"<<endl;
            break;
        }
        if(appointments.verify_id(id)){
            cout<<"Appointment already exists"<<endl;
            break;
        }
        Appointment new_appointment(id, patient_id, doctor_id, date);
        appointments.add_appointment(new_appointment);
        cout<<"---Appointment added successfully---"<<endl;
        break;
        }
        case 4: {
        doctors.display_doctors();
        break;
        }
        case 5: {
        patients.display_patients();
        break;
        }
        case 6: {
        appointments.display_appointments();
        break;
        }
        case 7: {
        cout << "Exiting..." << endl;
        break;
        }
        default: {
        cout << "Invalid choice" << endl;
        break;
        }
        }

    } while (choice != 7);
    return 0;
}