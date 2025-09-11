#include <bits/stdc++.h>
using namespace std;

// ===============================
// Class Appointment - Quản lý lịch hẹn
// ===============================
class Appointment {
private:
    string date;    // định dạng: dd/mm/yy
    string time;
    string reason;
    string status;   // trạng thái: Scheduled, Completed, Canceled
    int patientID;
    int doctorID;
    string location;
    int duration;    // phút

public:
    // Hàm khởi tạo lịch hẹn với date theo định dạng dd/mm/yy
    Appointment(string d, string t, string r, int pID, int dID,string loc = "Clinic Room 1", int dur = 30): date(d), time(t), reason(r), patientID(pID), doctorID(dID),location(loc), duration(dur), status("Scheduled") {}

    // Cập nhật trạng thái lịch hẹn
    void updateStatus(string newStatus) { status = newStatus; }

    // Đổi ngày/giờ hẹn
    void reschedule(string newDate, string newTime) {
        date = newDate;
        time = newTime;
        cout << "Appointment rescheduled to " << date << " at " << time << endl;
    }

    // Hiển thị thông tin lịch hẹn
    void displayInfo() const {
        cout << "Appointment: " << date << " " << time<< " | Reason: " << reason<< " | Status: " << status<< " | PatientID: " << patientID<< " | DoctorID: " << doctorID<< " | Location: " << location<< " | Duration: " << duration << " minutes"<< endl;
    }

    // Getter
    int getPatientID() const { return patientID; }
    int getDoctorID() const { return doctorID; }
    string getStatus() const { return status; }
    string getReason() const { return reason; }
};

// ===============================
// Class Patient - Quản lý bệnh nhân
// ===============================
class Patient {
protected:
    string name;
    int id;
    int age;
    string gender;
    string phoneNumber;
    vector<string> medicalHistory;

public:
    // Hàm khởi tạo bệnh nhân
    Patient(string n, int i, int a, string g, string phone): name(n), id(i), age(a), gender(g), phoneNumber(phone) {}

    // Đặt lịch hẹn
    virtual void scheduleAppointment(vector<Appointment>& appointments,string date, string time, string reason,int doctorID, string l = "Clinic Room 1",int d = 30) {
        appointments.push_back(Appointment(date, time, reason, id, doctorID, l, d));
        cout << "Patient " << name << " scheduled an appointment on "<< date << " at " << time << " for " << reason << endl;
    }

    // Thêm bệnh sử
    void addHistory(string record) { medicalHistory.push_back(record); }

    // Hiển thị thông tin bệnh nhân
    virtual void displayInfo() const {
        cout << "[ID: " << id << "] " << name<< ", Age: " << age<< " ("<<getAgeGroup()<<"),"<< " Gender: " << gender<< ", Phone: " << phoneNumber << endl;

        cout << "Medical History: ";
        if (medicalHistory.empty()) cout << "None";
        for (auto& h : medicalHistory) cout << h << "; ";
        cout << endl;
    }

    // Hủy lịch hẹn
    void cancelAppointment(vector<Appointment>& appointments, int i) {
        if (i >= 0 && i < (int)appointments.size()) {
            if (appointments[i].getPatientID() == id) {
                appointments[i].updateStatus("Canceled");
                cout << "Patient " << name << " canceled appointment #" << i + 1 << endl;
            } else {
                cout << "Error: Appointment does not belong to this patient." << endl;
            }
        }
    }
    // Nhập bệnh án cho bệnh nhân
    void inputMedicalHistory() {
        int n;
        cout << "Enter number of medical history records for patient " << name << ": ";
        cin >> n;
        cin.ignore(); // clear the leftover newline in buffer
        for (int i = 0; i < n; i++) {
            string record;
            cout << "  Enter record #" << i+1 << ": ";
            getline(cin, record);
            medicalHistory.push_back(record);
        }
    cout << " Added " << n << " medical history records for " << name << endl;
}
    // Phân loại nhóm tuổi
    string getAgeGroup() const {
        if (age < 18) return "Child";
        else if (age < 60) return "Adult";
        else return "Senior";
    }

    // Getter
    int getID() const { return id; }
};
// ===============================
// Class Medicine-Quản lí thuốc
// ===============================
class Medicine{
    private:
        string name;        //tên thuốc
        string dosage;      //liều lượng
        string frequency;   //tần suất
        string startDate;   //ngày bắt đầu
        string endDate;     //ngày kết thúc
    public:
        Medicine(string n, string d, string f, string s,string e): name(n),dosage(d),frequency(f),startDate(s),endDate(e){}
        void displayInfo() const {
            cout << name << " | Dosage: " << dosage << " | Frequency: " << frequency<< " | Start: " << startDate<< " | End: " << endDate << endl;
        }
        string getName()const{ return name;}
};


// ===============================
// Class ChronicPatient - Bệnh nhân mãn tính (kế thừa Patient)
// ===============================
class ChronicPatient : public Patient {
private:
    string conditionType;
    string lastCheckupDate;
    vector<Medicine> medicationList;

public:
    // Hàm khởi tạo bệnh nhân mãn tính
    ChronicPatient(string n, int i, int a, string g, string phone,string cond, string lastCheck): Patient(n, i, a, g, phone),conditionType(cond), lastCheckupDate(lastCheck) {}

    // Đặt lịch hẹn có cảnh báo đặc biệt
    void scheduleAppointment(vector<Appointment>& appointments,string date, string time, string reason,int doctorID, string location = "Clinic Room 1",int duration = 30) override {
        appointments.push_back(Appointment(date, time, reason + " (Chronic)", id, doctorID, location, duration));
        cout << "Chronic Patient " << name << " scheduled an appointment on "<< date << " at " << time << endl;
    }

    // Thêm thuốc điều trị
    void addMedication(const Medicine& med) { medicationList.push_back(med); }

    // Hiển thị danh sách thuốc
    void listMedications() const {
        cout << "Medications for " << name << ":" << endl;
        if (medicationList.empty()) {
            cout << " None" << endl;
        } else {
            for (auto& m : medicationList) {
                m.displayInfo();
            }
        }
    }


    // Hiển thị thông tin chi tiết bệnh nhân mãn tính
    void displayInfo() const override {
        cout << "[ID: " << id << "] " << name<< ", Age: " << age<< " (" << getAgeGroup() << ")"<< ", Gender: " << gender<< ", Phone: " << phoneNumber<< ", Condition: " << conditionType<< ", Last Checkup: " << lastCheckupDate << endl;
        cout << "Medical History: ";
        if (medicalHistory.empty()) cout << "None";
        for (auto& h : medicalHistory) cout << h << "; ";
        cout << endl;

        listMedications();
    }
};

// ===============================
// Class Doctor - Quản lý bác sĩ
// ===============================
class Doctor {
private:
    string name;
    int id;
    string specialty;
    int yearsExperience;
    string availability;

public:
    // Hàm khởi tạo bác sĩ
    Doctor(string n, int i, string s, int y, string avail): name(n), id(i), specialty(s), yearsExperience(y), availability(avail) {}

    // Xem lịch hẹn
    void viewAppointment(const Appointment& app) {
        cout << "Doctor " << name << " reviewing -> ";
        app.displayInfo();
    }

    // Cập nhật trạng thái lịch hẹn
    void updateAppointment(Appointment& app, string newStatus) {
        app.updateStatus(newStatus);
        cout << "Doctor " << name << " updated appointment status to " << newStatus << endl;
    }

    // Hiển thị thông tin bác sĩ
    void displayInfo() const {
        cout << "[ID: " << id << "] " << name<< ", Specialty: " << specialty<< ", Experience: " << yearsExperience << " years"<< ", Availability: " << availability << endl;
    }

    // Getter
    int getID() const { return id; }

};
// ===============================
// Class Nurse-Quản lí Y tá
// ===============================

class Nurse {
private:
    string name;
    int id;
    string shift; // ví dụ: "Morning", "Evening", "Night"
public:
    Nurse(string n, int i, string s): name(n), id(i), shift(s) {}
    void displayInfo() const {
        cout << "[ID: " << id << "] " << name << ", Shift: " << shift << endl;
    }
};

// ===============================
// Hàm Menu
// ===============================
void showMenu() {
    cout << "\n========= CLINIC MANAGEMENT SYSTEM =========\n";
    cout << "1. Add new Patient\n";
    cout << "2. Schedule Appointment\n";
    cout << "3. Show All Patients\n";
    cout << "4. Show Chronic Patients Only\n";
    cout << "5. Show Regular Patients Only\n";
    cout << "6. Show All Appointments\n";
    cout << "0. Exit\n";
    cout << "============================================\n";
    cout << "Choose an option: ";
}

int main() {
    vector<Appointment> appointments;
    vector<Patient*> patients;

    // ==================== EXAMPLES ====================
    // Tạo bác sĩ
    Doctor d1("Dr. Smith", 201, "Cardiology", 15, "Mon-Fri 9:00-17:00");
    Doctor d2("Dr. John", 202, "General Medicine", 8, "Mon-Sat 8:00-14:00");

    // Tạo y tá
    Nurse n1("Eva", 36, "Morning");
    Nurse n2("Muda", 72, "Night");

    // Tạo bệnh nhân
    Patient* p1 = new Patient("Alice", 101, 30, "Female", "0123-456-789");
    ChronicPatient* p2 = new ChronicPatient("Bob", 102, 65, "Male", "0987-654-321", "Diabetes", "15/06/2023");

    // Lịch sử bệnh án
    p1->addHistory("Visited for flu (10/11/2024)");
    p2->addHistory("Diabetes checkup (10/06/2025)");

    // Thuốc cho Bob
    Medicine m1("Metformin", "500mg", "2 times/day", "01/09/2025", "01/12/2025");
    Medicine m2("Insulin", "10 units", "Once/day", "01/09/2025", "01/12/2025");
    p2->addMedication(m1);
    p2->addMedication(m2);

    // Đặt lịch khám
    cout<<"=== The schedule has been arranged ===\n";
    p1->scheduleAppointment(appointments, "15/09/2025", "10:00", "Regular Checkup", d2.getID(), "Clinic Room 2", 30);
    p2->scheduleAppointment(appointments, "20/09/2025", "09:00", "Diabetes Follow-up", d1.getID(), "Clinic Room 1", 45);

    // Đưa vào danh sách
    patients.push_back(p1);
    patients.push_back(p2);

    // ==================== HIỂN THỊ EXAMPLE ====================
   cout << "\n=== Patient Info ===\n";
    for (auto p : patients) {
        if (!dynamic_cast<ChronicPatient*>(p)) {  // chỉ bệnh nhân thường
            p->displayInfo();
            cout << "--------------------------------\n";
        }
    }

    cout << "\n=== Chronic Patient Info ===\n";
    for (auto p : patients) {
        if (dynamic_cast<ChronicPatient*>(p)) {  // chỉ bệnh nhân mãn tính
            p->displayInfo();
            cout << "--------------------------------\n";
        }
    }

    cout << "\n=== Doctor Info ===\n";
    d1.displayInfo();
    d2.displayInfo();

    cout << "\n=== Nurse Info ===\n";
    n1.displayInfo();
    n2.displayInfo();

    cout << "\n=== Appointment List ===\n";
    for (auto& app : appointments) app.displayInfo();
    // ==================== MENU ====================
    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            // Add new patient
            string name, gender, phone;
            int id, age;
            cout << "\nEnter patient ID: "; cin >> id; cin.ignore();
            cout << "Name: "; getline(cin, name);
            cout << "Age: "; cin >> age; cin.ignore();
            cout << "Gender: "; getline(cin, gender);
            cout << "Phone number: "; getline(cin, phone);

            char type;
            cout << "Chronic patient? (y/n): "; cin >> type; cin.ignore();

            if (type == 'y' || type == 'Y') {
                string cond, lastCheck;
                cout << "Enter type of chronic condition: "; getline(cin, cond);
                cout << "Enter last checkup date (dd/mm/yyyy): "; getline(cin, lastCheck);

                ChronicPatient* cp = new ChronicPatient(name, id, age, gender, phone, cond, lastCheck);

                // Add medications
                int medCount;
                cout << "Enter number of medications: "; cin >> medCount; cin.ignore();
                for (int j = 0; j < medCount; j++) {
                    string medName, dosage, freq, start, end;
                    cout << "Medication #" << j+1 << " name: "; getline(cin, medName);
                    cout << "Dosage: "; getline(cin, dosage);
                    cout << "Frequency: "; getline(cin, freq);
                    cout << "Start date: "; getline(cin, start);
                    cout << "End date: "; getline(cin, end);
                    cp->addMedication(Medicine(medName, dosage, freq, start, end));
                }
                cp->inputMedicalHistory();
                patients.push_back(cp);
            } else {
                Patient* p = new Patient(name, id, age, gender, phone);
                p->inputMedicalHistory();
                patients.push_back(p);
            }
            cout << "Patient added successfully!\n";
        }
        else if (choice == 2) {
            // Schedule appointment
            if (patients.empty()) {
                cout << "No patients available!\n";
                continue;
            }
            cout << "\nChoose patient by index:\n";
            for (int i = 0; i < (int)patients.size(); i++) {
                cout << i+1 << ". "; patients[i]->displayInfo();
            }
            int idx; cin >> idx; cin.ignore();
            if (idx < 1 || idx > patients.size()) {
                cout << "Invalid choice!\n";
                continue;
            }

            string date, time, reason;
            int docChoice;
            cout << "Enter date (dd/mm/yyyy): "; getline(cin, date);
            cout << "Enter time (hh:mm): "; getline(cin, time);
            cout << "Enter reason: "; getline(cin, reason);
            cout << "Choose doctor (1. Dr. Smith, 2. Dr. John): "; cin >> docChoice; cin.ignore();

            int docID = (docChoice == 1 ? d1.getID() : d2.getID());
            patients[idx-1]->scheduleAppointment(appointments, date, time, reason, docID);
        }
        else if (choice == 3) {
            cout << "\n=== ALL PATIENTS ===\n";
            for (auto p : patients) p->displayInfo();
        }
        else if (choice == 4) {
            cout << "\n=== CHRONIC PATIENTS ===\n";
            for (auto p : patients) {
                if (dynamic_cast<ChronicPatient*>(p)) p->displayInfo();
            }
        }
        else if (choice == 5) {
            cout << "\n=== REGULAR PATIENTS ===\n";
            for (auto p : patients) {
                if (!dynamic_cast<ChronicPatient*>(p)) p->displayInfo();
            }
        }
        else if (choice == 6) {
            cout << "\n=== APPOINTMENTS ===\n";
            for (auto& app : appointments) app.displayInfo();
        }
    } while (choice != 0);

    // Free memory
    for (auto p : patients) delete p;

    cout << "Exiting program...\n";
    return 0;

}
