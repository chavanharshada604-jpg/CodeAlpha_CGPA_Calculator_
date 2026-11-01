
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Subject {
public:
    string subjectName;
    int credit;
    float gradePoint;

    // constructor
    Subject(string name, int cr, float gp) {
        subjectName = name;
        credit = cr;
        gradePoint = gp;
    }
};

class Student {
public:
    string name;
    vector<Subject> subjects;

    // constructor
    Student(string studentName) {
        name = studentName;
    }

    void addSubject(string subjectName, int credit, float gradePoint) {
        Subject newSubject(subjectName, credit, gradePoint);
        subjects.push_back(newSubject);
    }

    float calculateCGPA() {
        int totalCredit = 0;
        float weightGradePoint = 0;
        for (const Subject &subject : subjects) {
            totalCredit += subject.credit;
            weightGradePoint += subject.credit * subject.gradePoint;
        }
        return (totalCredit > 0) ? weightGradePoint / totalCredit : 0;
    }

    void displayCGPA() {
        cout << "\nStudent Name: " << name << endl;
        cout << fixed << setprecision(2);
        cout << "CGPA: " << calculateCGPA() << endl;
    }
};

int main() {
    string studentName;
    int numSubjects;

    cout << "Enter student name: ";
    getline(cin, studentName);

    Student student(studentName);

    cout << "Enter the number of subjects: ";
    cin >> numSubjects;
    cin.ignore(); // ignore the newline character

    for (int i = 0; i < numSubjects; i++) {
        string subjectName;
        int credit;
        float gradePoint;

        cout << "Enter subject name: ";
        getline(cin, subjectName);

        cout << "Enter credits for " << subjectName << ": ";
        cin >> credit;

        cout << "Enter grade points for " << subjectName << ": ";
        cin >> gradePoint;
        cin.ignore(); // ignore the newline character

        // add the subject to the student's record
        student.addSubject(subjectName, credit, gradePoint);
    }

    // calculate and display the CGPA
    student.displayCGPA();

    return 0;
}
