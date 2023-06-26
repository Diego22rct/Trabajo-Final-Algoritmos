#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__
#include "User.hpp"
#include "Course.hpp"
#include "DLL.hpp"
#include "HT.hpp"
#include <fstream>
class Student : public User {
private:
    int cycle;
    string major;
    HT<Course>* enrolledCourses;

public:
    Student(string name = " ", string id = " ", string email = " ", string major = " ", int cycle = 0, string password = " ")
        : User(id, name, email, password, "alumno"), major(major), cycle(cycle) {
        loadEnrolledCourses();

    }
    string getMajor() {
        return major;
    }
    int getCycle() {
        return cycle;
    }

    void saveCourse(Course* course) {
        ofstream file;
        file.open("cursos_matriculados.txt", ios::app);
        file << getName() << "," << course->getCourseCode() << "," << course->getCourseName() << "\n";
        file.close();
    }
    void loadEnrolledCourses() {
        ifstream file("cursos_matriculados.txt");
        string name, courseCode, courseName;
        while (getline(file, name, ','), getline(file, courseCode, ','), getline(file, courseName)) {
            if (name == getName()) {
                Course* course = new Course(courseName, courseCode);
                enrolledCourses.pushBack(course);
            }
        }
        file.close();
    }
    void loadGrades() {
        ifstream file("Cursos.txt");
        string studentName, courseCode;
        double finalGrade;
        while (getline(file, studentName, ','), getline(file, courseCode, ','), file >> finalGrade) {
            if (studentName == getName()) {
                enrolledCourses.forEach([&](Course* c) {
                    if (c->getCourseCode() == courseCode) {
                       // c->setGrade(finalGrade);
                    }
                    });
            }
        }
        file.close();
    }
    void showCourses() {
        availableCourses.forEach([](Course* c) {
            cout << c->toString() << endl;
            });
    }
    void enrollCourse(string code) {
        Course* courseToEnroll = nullptr;
        availableCourses.forEach([&](Course* c) {
            if (c->getCourseCode() == code) {
                courseToEnroll = c;
            }
            });
        if (courseToEnroll != nullptr) {
            bool alreadyEnrolled = false;
            enrolledCourses.forEach([&](Course* c) {
                if (c->getCourseCode() == code) {
                    alreadyEnrolled = true;
                }
                });
            if (!alreadyEnrolled) {
                enrolledCourses.pushBack(courseToEnroll);
                cout << "Course enrolled" << endl;
                saveCourse(courseToEnroll);
            }
            else {
                cout << "You are already enrolled in this course." << endl;
            }
        }
        else {
            cout << "No course found with the provided code." << endl;
        }
    }
    void withdrawCourse() {
        if (enrolledCourses.isEmpty()) {
            cout << "No courses enrolled" << endl;
            return;
        }
        else {
            string code;
            cin >> code;
            bool courseWithdrawn = enrolledCourses.popElementIf([&](Course* c) {
                return c->getCourseCode() == code;
                });
            if (courseWithdrawn) {
                cout << "Course successfully withdrawn" << endl;
            }
            else {
                cout << "No course found with the provided code." << endl;
            }
        }
    }
    void showEnrolledCourses() {
        if (enrolledCourses.isEmpty()) {
            cout << "No courses enrolled." << endl;
            return;
        }
        enrolledCourses.forEach([](Course* c) {
            cout << c->toString() << endl;
            });
    }

};
#endif // __STUDENT_HPP__
