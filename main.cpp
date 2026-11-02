#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// 1. ABSTRACTION (Abstract Base Class using pure virtual functions)
class BasePatient {
public:
    virtual void getDetails() = 0;              
    virtual void displayDetails() const = 0;    
    virtual float calculateBill() const = 0;   
    virtual void saveToFile() const = 0;        
    virtual ~BasePatient() {}                   
};

// 2. ENCAPSULATION & INHERITANCE (Patient inherits from BasePatient)
class Patient : public BasePatient {
private:
    int id;
    string name;
    int age;

protected:
    Patient(int id = 0, string name = "", int age = 0) 
        : id(id), name(name), age(age) {}

public:
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }

    void setPatientDetails() {
        cout << "Enter Patient ID: ";
        cin >> id;
        cout << "Enter Patient Name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Enter Patient Age: ";
        cin >> age;
    }

    void displayPatientDetails() const {
        cout << "\nPatient ID: " << id;
        cout << "\nPatient Name: " << name;
        cout << "\nPatient Age: " << age;
    }
};

// INHERITANCE (InPatient inherits from Patient)
class InPatient : public Patient {
private:
    int days;
    float chargePerDay;

public:
    InPatient() : Patient(), days(0), chargePerDay(0.0f) {}

    // 3. POLYMORPHISM (Overriding Base Class Functions)
    void getDetails() override {
        setPatientDetails();
        cout << "Enter Number of Days: ";
        cin >> days;
        cout << "Enter Charge Per Day: ";
        cin >> chargePerDay;
    }

    float calculateBill() const override {
        return days * chargePerDay;
    }

    // 4. OVERLOADING (Function Overloading: adding a discount version)
    float calculateBill(float discountPercent) const {
        float total = calculateBill();
        return total - (total * (discountPercent / 100.0f));
    }

    void displayDetails() const override {
        displayPatientDetails();
        cout << "\nHospital Stay: " << days << " days";
        cout << "\nCharge Per Day: Rs. " << chargePerDay;
        cout << "\nTotal Bill: Rs. " << calculateBill();
    }

    // 5. FILE HANDLING (Writing to a file)
    void saveToFile() const override {
        ofstream file("hospital_records.txt", ios::app);
        if (file.is_open()) {
            file << "Type: InPatient\n";
            file << "Patient ID: " << getId() << "\n";
            file << "Patient Name: " << getName() << "\n";
            file << "Patient Age: " << getAge() << "\n";
            file << "Hospital Stay: " << days << " days\n";
            file << "Total Bill: Rs. " << calculateBill() << "\n";
            file << "------------------------\n";
            file.close();
            cout << "\nRecord saved successfully to file!";
        } else {
            cout << "\nError: Unable to open file!";
        }
    }
};

int main() {
    BasePatient* patientPtr = nullptr;
    int choice;

    do {
        cout << "\n\n===== HOSPITAL MANAGEMENT SYSTEM =====";
        cout << "\n1. Add In-Patient Record";
        cout << "\n2. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                patientPtr = new InPatient(); // Polymorphic instantiation
                patientPtr->getDetails();
                
                cout << "\n--- Patient Receipt ---";
                patientPtr->displayDetails();
                patientPtr->saveToFile();
                
                delete patientPtr; // Clean up memory
                patientPtr = nullptr;
                break;

            case 2:
                cout << "\nThank you for using the system!";
                break;

            default:
                cout << "\nInvalid choice! Please try again.";
        }
    } while (choice != 2);

    return 0;
}