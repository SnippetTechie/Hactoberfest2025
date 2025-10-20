#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

class Student {
private:
    int id;
    string name;
    int age;
    string course;
    float gpa;
    
public:
    Student(int id, string name, int age, string course, float gpa)
        : id(id), name(name), age(age), course(course), gpa(gpa) {}
    
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getCourse() const { return course; }
    float getGpa() const { return gpa; }
    
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setCourse(string c) { course = c; }
    void setGpa(float g) { gpa = g; }
    
    void display() const {
        cout << left << setw(10) << id 
             << setw(20) << name 
             << setw(8) << age 
             << setw(20) << course 
             << setw(8) << fixed << setprecision(2) << gpa << endl;
    }
    
    string serialize() const {
        return to_string(id) + "," + name + "," + to_string(age) + "," + 
               course + "," + to_string(gpa);
    }
};

class StudentManagementSystem {
private:
    vector<Student> students;
    int nextId;
    const string filename = "students.txt";
    
    int findStudentIndex(int id) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }
    
public:
    StudentManagementSystem() : nextId(1) {
        loadFromFile();
    }
    
    void addStudent() {
        string name, course;
        int age;
        float gpa;
        
        cout << "\n=== Add New Student ===" << endl;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter Age: ";
        cin >> age;
        
        cout << "Enter Course: ";
        cin.ignore();
        getline(cin, course);
        
        cout << "Enter GPA (0.0 - 4.0): ";
        cin >> gpa;
        
        if (gpa < 0.0 || gpa > 4.0) {
            cout << "\n❌ Invalid GPA! Must be between 0.0 and 4.0" << endl;
            return;
        }
        
        Student student(nextId++, name, age, course, gpa);
        students.push_back(student);
        
        cout << "\n✅ Student added successfully with ID: " << student.getId() << endl;
        saveToFile();
    }
    
    void displayAllStudents() {
        if (students.empty()) {
            cout << "\n❌ No students in the system!" << endl;
            return;
        }
        
        cout << "\n=== All Students ===" << endl;
        cout << string(70, '=') << endl;
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name" 
             << setw(8) << "Age" 
             << setw(20) << "Course" 
             << setw(8) << "GPA" << endl;
        cout << string(70, '=') << endl;
        
        for (const auto& student : students) {
            student.display();
        }
        cout << string(70, '=') << endl;
    }
    
    void searchStudent() {
        int id;
        cout << "\nEnter Student ID to search: ";
        cin >> id;
        
        int index = findStudentIndex(id);
        if (index == -1) {
            cout << "\n❌ Student with ID " << id << " not found!" << endl;
            return;
        }
        
        cout << "\n=== Student Found ===" << endl;
        cout << string(70, '=') << endl;
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name" 
             << setw(8) << "Age" 
             << setw(20) << "Course" 
             << setw(8) << "GPA" << endl;
        cout << string(70, '=') << endl;
        students[index].display();
    }
    
    void updateStudent() {
        int id;
        cout << "\nEnter Student ID to update: ";
        cin >> id;
        
        int index = findStudentIndex(id);
        if (index == -1) {
            cout << "\n❌ Student with ID " << id << " not found!" << endl;
            return;
        }
        
        cout << "\n=== Update Student Information ===" << endl;
        cout << "Current Information:" << endl;
        students[index].display();
        
        int choice;
        cout << "\nWhat would you like to update?" << endl;
        cout << "1. Name" << endl;
        cout << "2. Age" << endl;
        cout << "3. Course" << endl;
        cout << "4. GPA" << endl;
        cout << "5. Update All" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        cin.ignore();
        
        switch (choice) {
            case 1: {
                string name;
                cout << "Enter new name: ";
                getline(cin, name);
                students[index].setName(name);
                break;
            }
            case 2: {
                int age;
                cout << "Enter new age: ";
                cin >> age;
                students[index].setAge(age);
                break;
            }
            case 3: {
                string course;
                cout << "Enter new course: ";
                getline(cin, course);
                students[index].setCourse(course);
                break;
            }
            case 4: {
                float gpa;
                cout << "Enter new GPA: ";
                cin >> gpa;
                if (gpa >= 0.0 && gpa <= 4.0) {
                    students[index].setGpa(gpa);
                } else {
                    cout << "❌ Invalid GPA!" << endl;
                    return;
                }
                break;
            }
            case 5: {
                string name, course;
                int age;
                float gpa;
                
                cout << "Enter new name: ";
                getline(cin, name);
                cout << "Enter new age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter new course: ";
                getline(cin, course);
                cout << "Enter new GPA: ";
                cin >> gpa;
                
                if (gpa >= 0.0 && gpa <= 4.0) {
                    students[index].setName(name);
                    students[index].setAge(age);
                    students[index].setCourse(course);
                    students[index].setGpa(gpa);
                } else {
                    cout << "❌ Invalid GPA!" << endl;
                    return;
                }
                break;
            }
            default:
                cout << "❌ Invalid choice!" << endl;
                return;
        }
        
        cout << "\n✅ Student information updated successfully!" << endl;
        saveToFile();
    }
    
    void deleteStudent() {
        int id;
        cout << "\nEnter Student ID to delete: ";
        cin >> id;
        
        int index = findStudentIndex(id);
        if (index == -1) {
            cout << "\n❌ Student with ID " << id << " not found!" << endl;
            return;
        }
        
        cout << "\nAre you sure you want to delete this student?" << endl;
        students[index].display();
        cout << "Enter 'yes' to confirm: ";
        string confirm;
        cin >> confirm;
        
        if (confirm == "yes" || confirm == "YES" || confirm == "Yes") {
            students.erase(students.begin() + index);
            cout << "\n✅ Student deleted successfully!" << endl;
            saveToFile();
        } else {
            cout << "\n❌ Deletion cancelled!" << endl;
        }
    }
    
    void displayStatistics() {
        if (students.empty()) {
            cout << "\n❌ No students in the system!" << endl;
            return;
        }
        
        float totalGpa = 0;
        float maxGpa = students[0].getGpa();
        float minGpa = students[0].getGpa();
        map<string, int> courseCount;
        
        for (const auto& student : students) {
            totalGpa += student.getGpa();
            maxGpa = max(maxGpa, student.getGpa());
            minGpa = min(minGpa, student.getGpa());
            courseCount[student.getCourse()]++;
        }
        
        cout << "\n=== Student Statistics ===" << endl;
        cout << string(50, '=') << endl;
        cout << "Total Students: " << students.size() << endl;
        cout << "Average GPA: " << fixed << setprecision(2) 
             << totalGpa / students.size() << endl;
        cout << "Highest GPA: " << maxGpa << endl;
        cout << "Lowest GPA: " << minGpa << endl;
        
        cout << "\nStudents per Course:" << endl;
        for (const auto& pair : courseCount) {
            cout << "  " << pair.first << ": " << pair.second << " students" << endl;
        }
        cout << string(50, '=') << endl;
    }
    
    void sortByGpa() {
        if (students.empty()) {
            cout << "\n❌ No students in the system!" << endl;
            return;
        }
        
        sort(students.begin(), students.end(), 
             [](const Student& a, const Student& b) {
                 return a.getGpa() > b.getGpa();
             });
        
        cout << "\n✅ Students sorted by GPA (highest to lowest)" << endl;
        displayAllStudents();
    }
    
    void saveToFile() {
        ofstream file(filename);
        if (!file) {
            cout << "❌ Error opening file for writing!" << endl;
            return;
        }
        
        file << nextId << endl;
        for (const auto& student : students) {
            file << student.serialize() << endl;
        }
        
        file.close();
    }
    
    void loadFromFile() {
        ifstream file(filename);
        if (!file) {
            return;
        }
        
        file >> nextId;
        file.ignore();
        
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            vector<string> tokens;
            string token;
            for (char c : line) {
                if (c == ',') {
                    tokens.push_back(token);
                    token.clear();
                } else {
                    token += c;
                }
            }
            tokens.push_back(token);
            
            if (tokens.size() == 5) {
                int id = stoi(tokens[0]);
                string name = tokens[1];
                int age = stoi(tokens[2]);
                string course = tokens[3];
                float gpa = stof(tokens[4]);
                
                students.push_back(Student(id, name, age, course, gpa));
            }
        }
        
        file.close();
    }
};

int main() {
    StudentManagementSystem sms;
    int choice;
    
    cout << "\n╔══════════════════════════════════════════╗" << endl;
    cout << "║   STUDENT MANAGEMENT SYSTEM - C++        ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    
    do {
        cout << "\n┌─────────────────────────────────────────┐" << endl;
        cout << "│              MAIN MENU                  │" << endl;
        cout << "├─────────────────────────────────────────┤" << endl;
        cout << "│  1. Add Student                         │" << endl;
        cout << "│  2. Display All Students                │" << endl;
        cout << "│  3. Search Student                      │" << endl;
        cout << "│  4. Update Student                      │" << endl;
        cout << "│  5. Delete Student                      │" << endl;
        cout << "│  6. Display Statistics                  │" << endl;
        cout << "│  7. Sort Students by GPA                │" << endl;
        cout << "│  0. Exit                                │" << endl;
        cout << "└─────────────────────────────────────────┘" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                sms.addStudent();
                break;
            case 2:
                sms.displayAllStudents();
                break;
            case 3:
                sms.searchStudent();
                break;
            case 4:
                sms.updateStudent();
                break;
            case 5:
                sms.deleteStudent();
                break;
            case 6:
                sms.displayStatistics();
                break;
            case 7:
                sms.sortByGpa();
                break;
            case 0:
                cout << "\n👋 Thank you for using Student Management System!" << endl;
                cout << "Goodbye!\n" << endl;
                break;
            default:
                cout << "\n❌ Invalid choice! Please try again." << endl;
        }
        
    } while (choice != 0);
    
    return 0;
}
