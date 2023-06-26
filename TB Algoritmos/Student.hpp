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
    DLL<Course*> enrolledCourses;
    DLL<Course*> availableCourses;

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
    DLL<Course*>& getEnrolledCourses() {
        return enrolledCourses;
    }
    //void loadCourses() {
    //    ifstream file("courses.csv");
    //    string idx, name, code, major;
    //    int term;
    //    while (getline(file, idx, ','), getline(file, name, ','), getline(file, code, ','), getline(file, major, ','), file >> term) {
    //        availableCourses.pushBack(new Course(stoi(idx), name, code, major, term));
    //    }
    //    file.close();
    //}

    DLL<Course*>& getEnrolledCourses() {
        return enrolledCourses;
    }

    void loadCourses() {
        ifstream file("courses.txt");
        string idx, name, code, major;
        int term;
        while (getline(file, idx, ','), getline(file, name, ','), getline(file, code, ','), getline(file, major, ','), file >> term) {
            availableCourses.pushBack(new Course(stoi(idx), name, code, major, term));
        }
        file.close();
    }

    void saveCourse(Course* course) {
        ofstream file;
        file.open("coursesEnrolled.txt", ios::app);
        file << getName() << "," << course->getCourseCode() << "," << course->getCourseName() << "\n";
        file.close();
    }

    void loadEnrolledCourses() {
        ifstream file("coursesEnrolled.txt");
        string name, courseCode, courseName;
        while (getline(file, name, ','), getline(file, courseCode, ','), getline(file, courseName)) {
            if (name == getName()) {
                Course* course = new Course(0, courseName, courseCode, "", 0);
                enrolledCourses.pushBack(course);
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