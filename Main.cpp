#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

struct Course {
    string name;
    string grade;      // e.g. A, B+, C
    double gradePoint; // 4.0 scale
    double credits;
};

// Convert letter grade to grade point (4.0 scale). Returns -1 if invalid.
double gradeToPoint(string g) {
    for (char &c : g) c = toupper(c);
    if (g == "A+" || g == "A") return 4.0;
    if (g == "A-") return 3.7;
    if (g == "B+") return 3.3;
    if (g == "B")  return 3.0;
    if (g == "B-") return 2.7;
    if (g == "C+") return 2.3;
    if (g == "C")  return 2.0;
    if (g == "C-") return 1.7;
    if (g == "D")  return 1.0;
    if (g == "F")  return 0.0;
    return -1;
}

int readInt(const string &msg, int minV) {
    int x;
    while (true) {
        cout << msg;
        if (cin >> x && x >= minV) return x;
        cout << "  Invalid input. Enter a number >= " << minV << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readCredits(const string &msg) {
    double x;
    while (true) {
        cout << msg;
        if (cin >> x && x > 0) return x;
        cout << "  Invalid input. Credit hours must be > 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    cout << "=====================================\n";
    cout << "         CGPA CALCULATOR\n";
    cout << "=====================================\n";
    cout << "Grades: A, A-, B+, B, B-, C+, C, C-, D, F (4.0 scale)\n\n";

    int semesters = readInt("Enter number of semesters: ", 1);

    double overallPoints = 0, overallCredits = 0;
    vector<double> semGPA;

    for (int s = 1; s <= semesters; s++) {
        cout << "\n----- Semester " << s << " -----\n";
        int n = readInt("Number of courses: ", 1);
        vector<Course> courses;
        double semPoints = 0, semCredits = 0;

        for (int i = 1; i <= n; i++) {
            Course c;
            cout << "\nCourse " << i << " name: ";
            cin >> ws;
            getline(cin, c.name);

            while (true) {
                cout << "Grade: ";
                cin >> c.grade;
                c.gradePoint = gradeToPoint(c.grade);
                if (c.gradePoint >= 0) break;
                cout << "  Invalid grade! Try again.\n";
            }
            c.credits = readCredits("Credit hours: ");

            semPoints  += c.gradePoint * c.credits;   // grade x credit hours
            semCredits += c.credits;
            courses.push_back(c);
        }

        double gpa = semPoints / semCredits;
        semGPA.push_back(gpa);
        overallPoints  += semPoints;
        overallCredits += semCredits;

        // Display individual course grades
        cout << "\nSemester " << s << " Report\n";
        cout << left << setw(22) << "Course" << setw(8) << "Grade"
             << setw(10) << "Credits" << "Points\n";
        cout << string(48, '-') << "\n";
        for (const Course &c : courses) {
            cout << left << setw(22) << c.name << setw(8) << c.grade
                 << setw(10) << fixed << setprecision(2) << c.credits
                 << c.gradePoint * c.credits << "\n";
        }
        cout << string(48, '-') << "\n";
        cout << "Total Credits : " << semCredits << "\n";
        cout << "Total Points  : " << fixed << setprecision(2) << semPoints << "\n";
        cout << "Semester GPA  : " << gpa << "\n";
    }

    double cgpa = overallPoints / overallCredits;

    cout << "\n=====================================\n";
    cout << "           FINAL RESULT\n";
    cout << "=====================================\n";
    for (int i = 0; i < (int)semGPA.size(); i++)
        cout << "Semester " << i + 1 << " GPA : " << fixed << setprecision(2) << semGPA[i] << "\n";
    cout << "Total Credits  : " << overallCredits << "\n";
    cout << "Overall CGPA   : " << fixed << setprecision(2) << cgpa << "\n";
    cout << "=====================================\n";
    return 0;
}
