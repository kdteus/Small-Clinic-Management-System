# Small-Clinic-Management-System
## 📌 Overview
`smallclinic.cpp` – A simple Clinic Management System implemented using **Object-Oriented Programming (OOP)** in **C++**.
This system allows management of:  
- **Patients** (regular & chronic)  
- **Doctors**  
- **Appointments**  

It demonstrates key OOP concepts:  
- **Classes & Objects**  
- **Inheritance**  
- **Encapsulation**  
- **Polymorphism**  

The system supports:  
- Adding, editing, and displaying patients and doctors  
- Scheduling, canceling, and completing appointments  
- Maintaining medical history records for patients

---

## ⚙️ Build & Run Instructions

### On Linux / macOS / WSL
```bash
g++ smallclinic.cpp -o clinic
./clinic
```

### On Windows
```bash
g++ smallclinic.cpp -o clinic.exe
clinic.exe
```

##🤖 AI Disclosure
Author: Khong Dinh Tu-24110145 
Used ChatGPT for brainstorming ideas (e.g., methods for Appointment, how to override virtual functions, and improving code readability).
All code has been understood, tested, and personalized before submission.
##Reflection
## 📝 Reflection
Working on this Clinic Management System gave me hands-on experience with **core OOP principles** in a practical context.  

By creating a `Patient` base class and extending it with `ChronicPatient`, I was able to see how **inheritance** helps reduce code duplication while allowing specialized behavior for different patient types. Using **virtual functions** and **overriding** allowed the system to handle patients polymorphically, which made the code more flexible and easier to maintain.  

One of the main challenges was keeping **patient medical history** in sync with appointment changes. Adding, canceling, or completing appointments required careful attention to ensure that all related data across classes remained consistent. This highlighted the complexity of managing interrelated objects in real-world systems.  

Overall, the project strengthened my understanding of designing clean, modular, and extensible code. It also emphasized the importance of **data integrity** and thoughtful class design when building applications that involve multiple interacting entities.
