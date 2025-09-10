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
        cout << "Patient " << name << " scheduled an appointment on "
             << date << " at " << time << " for " << reason << endl;
    }

    // Thêm bệnh sử
    void addHistory(string record) { medicalHistory.push_back(record); }

    // Hiển thị thông tin bệnh nhân
    virtual void displayInfo() const {
        cout << "Patient [ID: " << id << "] " << name<< ", Age: " << age<< ", Gender: " << gender<< ", Phone: " << phoneNumber << endl;

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
// Class ChronicPatient - Bệnh nhân mãn tính (kế thừa Patient)
// ===============================
class ChronicPatient : public Patient {
private:
    string conditionType;
    string lastCheckupDate;
    vector<string> medicationList;

public:
    // Hàm khởi tạo bệnh nhân mãn tính
    ChronicPatient(string n, int i, int a, string g, string phone,
                   string cond, string lastCheck)
        : Patient(n, i, a, g, phone),
          conditionType(cond), lastCheckupDate(lastCheck) {}

    // Đặt lịch hẹn có cảnh báo đặc biệt
    void scheduleAppointment(vector<Appointment>& appointments,string date, string time, string reason,int doctorID, string location = "Clinic Room 1",int duration = 30) override {
        cout << "Note: Chronic patient requires regular check-ups every 3 months." << endl;
        appointments.push_back(Appointment(date, time, reason + " (Chronic)", id, doctorID, location, duration));
        cout << "Chronic Patient " << name << " scheduled an appointment on "
             << date << " at " << time << endl;
    }

    // Thêm thuốc điều trị
    void addMedication(string med) { medicationList.push_back(med); }

    // Hiển thị danh sách thuốc
    void listMedications() const {
        cout << "Medications for " << name << ": ";
        if (medicationList.empty()) cout << "None";
        for (auto& m : medicationList) cout << m << "; ";
        cout << endl;
    }

    // Hiển thị thông tin chi tiết bệnh nhân mãn tính
    void displayInfo() const override {
        cout << "Chronic Patient [ID: " << id << "] " << name<< ", Age: " << age<< " (" << getAgeGroup() << ")"<< ", Gender: " << gender<< ", Phone: " << phoneNumber<< ", Condition: " << conditionType<< ", Last Checkup: " << lastCheckupDate << endl;

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
        cout << "Doctor [ID: " << id << "] " << name<< ", Specialty: " << specialty<< ", Experience: " << yearsExperience << " years"<< ", Availability: " << availability << endl;
    }

    // Getter
    int getID() const { return id; }

};
int main() {
    vector<Appointment> appointments;
    //Example
    // ==================== Tạo bác sĩ ====================
    Doctor d1("Dr. Smith", 201, "Cardiology", 15, "Mon-Fri 9:00-17:00");
    Doctor d2("Dr. John", 202, "General Medicine", 8, "Mon-Sat 8:00-14:00");

    // ==================== Tạo bệnh nhân ====================
    Patient p1("Alice", 101, 30, "Female", "0123-456-789");
    ChronicPatient p2("Bob", 102, 65, "Male", "0987-654-321", "Diabetes", "15/06/2023");

    // ==================== Đặt lịch hẹn ====================
    p1.scheduleAppointment(appointments, "15/09/2025", "10:00", "Regular Checkup", d2.getID(), "Clinic Room 2", 30);
    p2.scheduleAppointment(appointments, "20/09/2025", "09:00", "Diabetes Follow-up", d1.getID(), "Clinic Room 1", 45);

    // ==================== Thêm lịch sử bệnh án ====================
    p1.addHistory("Visited for flu (10/11/2024)");
    p2.addHistory("Diabetes checkup (10/06/2025)");

    // ==================== Thêm thuốc cho bệnh nhân mãn tính ====================
    p2.addMedication("Metformin");
    p2.addMedication("Insulin");

    // ==================== Hiển thị thông tin bệnh nhân ====================
    cout << "\n=== Patient Info ===" << endl;
    p1.displayInfo();
    p2.displayInfo();

    // ==================== Hiển thị thông tin bác sĩ ====================
    cout << "\n=== Doctor Info ===" << endl;
    d1.displayInfo();
    d2.displayInfo();

    // ==================== Hiển thị danh sách lịch hẹn ====================
    cout << "\n=== Appointment List ===" << endl;
    for (auto& app : appointments) app.displayInfo();

    // ==================== Bác sĩ cập nhật trạng thái ====================
    cout << "\n=== Updating Appointment ===" << endl;
    d1.updateAppointment(appointments[1], "Completed");

    // ==================== Bệnh nhân hủy lịch hẹn ====================
    cout << "\n=== Canceling Appointment ===" << endl;
    p1.cancelAppointment(appointments, 0);

    // ==================== Bệnh nhân đổi lịch (reschedule) ====================
    cout << "\n=== Rescheduling Appointment ===" << endl;
    appointments[1].reschedule("22/09/2025", "11:00");

    // ==================== Danh sách lịch hẹn cuối cùng ====================
    cout << "\n=== Final Appointment List ===" << endl;
    for (auto& app : appointments) app.displayInfo();


    //Nhập thông tin bệnh nhân vào từ bàn phím
    int N;
    vector<Patient*> patients;
    cout<<"Enter the number of the patients: "<<endl;
    cin>>N;
    for (int i = 0; i < N; i++) {
        cout << "\n=== Enter the information of the patients #" << i+1 << " ===" << endl;
        string name, gender, phone;
        int id, age;
        cout << "Enter ID: "; cin >> id;
        cin.ignore();
        cout << "Name: "; getline(cin, name);
        cout << "Age: "; cin >> age;
        cin.ignore();
        cout << "Gender: "; getline(cin, gender);
        cout << "Phone number: "; getline(cin, phone);

        char type;
        cout << "Chronic patient? (y/n): ";
        cin >> type;
        cin.ignore();

        if (type == 'y' || type == 'Y') {
            string cond, lastCheck;
            cout << "Enter type of chronic condition: ";
            getline(cin, cond);
            cout << "Enter last checkup date (dd/mm/yyyy): ";
            getline(cin, lastCheck);

            patients.push_back(new ChronicPatient(name, id, age, gender, phone, cond, lastCheck));
        } else {
            patients.push_back(new Patient(name, id, age, gender, phone));
        }

        // Nhập hồ sơ bệnh án
        patients.back()->inputMedicalHistory();
    }
    // Đặt lịch hẹn cho bệnh nhân
    cout << "\n=== Schedule Appointments for Patients ===" << endl;
    for (auto& p : patients) {
        string date, time, reason;
        int choice;
        cout << "\nEnter date (dd/mm/yyyy): "; getline(cin, date);
        cout << "Enter time (hh:mm): "; getline(cin, time);
        cout << "Enter reason for visit: "; getline(cin, reason);

        cout << "Choose doctor (1. Dr. Smith, 2. Dr. John): ";
        cin >> choice;
        cin.ignore();

        int docID = (choice == 1 ? d1.getID() : d2.getID());
        p->scheduleAppointment(appointments, date, time, reason, docID);
    }
    // Hiển thị thông tin bệnh nhân
    cout << "\n=== Patient Info ===" << endl;
    for (auto& p : patients) {
        p->displayInfo();
        cout << endl;
    }

    cout << "\n=== Doctor Info ===" << endl;
    d1.displayInfo();
    d2.displayInfo();

    cout << "\n=== Appointment List ===" << endl;
    for (auto& app : appointments) app.displayInfo();

    // Giải phóng bộ nhớ
    for (auto& p : patients) delete p;
    return 0;
}
