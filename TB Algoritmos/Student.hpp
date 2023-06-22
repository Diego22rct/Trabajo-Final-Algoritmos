#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__
#include "User.hpp"
#include "Course.hpp"
#include "DLL.hpp"
#include <fstream>

class Student : public User {
private:
    int cycle;
    string major;
    DLL<Course*> enrolledCourses;
    DLL<Course*> availableCourses;

public:
    Student(string name = " ", string id = " ", string email = " ",string major = " ", int cycle = 0, string password = " ")
        : User(id, name, email, password, "alumno"), major(major), cycle(cycle) {
        loadCourses();
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

    void loadCourses() {
        ifstream file("courses.csv");
        string idx, name, code, major;
        int term;
        while (getline(file, idx, ','), getline(file, name, ','), getline(file, code, ','), getline(file, major, ','), file >> term) {
            availableCourses.pushBack(new Course(stoi(idx), name, code, major, term));
        }
        file.close();
    }

    void saveCourse(Course* course) {
        ofstream file;
        file.open("enrolled_courses.csv", ios::app);
        file << getName() << "," << course->getCourseCode() << "," << course->getCourseName() << "\n";
        file.close();
    }

    void loadEnrolledCourses() {
        ifstream file("enrolled_courses.csv");
        string name, courseCode, courseName;
        while (getline(file, name, ','), getline(file, courseCode, ','), getline(file, courseName)) {
            if (name == getName()) {
                Course* course = new Course(0, courseName, courseCode, "", 0);
                enrolledCourses.pushBack(course);
            }
        }
        file.close();
    }

    void loadGrades() {
        ifstream file("grades.csv");
        string studentName, courseCode;
        double finalGrade;
        while (getline(file, studentName, ','), getline(file, courseCode, ','), file >> finalGrade) {
            if (studentName == getName()) {
                enrolledCourses.forEach([&](Course* c) {
                    if (c->getCourseCode() == courseCode) {
                        c->setGrade(finalGrade);
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

    void checkGrades() {
        if (enrolledCourses.isEmpty()) {
            cout << "No courses enrolled" << endl;
        }
        else {
            enrolledCourses.forEach([](Course* c) {
                cout << "Course name: " << c->getCourseName() << ", Final grade: " << c->getFinalGrade() << endl;
                });
        }
    }

    void addCourseByProfessor(Course* course) {
        enrolledCourses.pushBack(course);
    }

    bool removeCourseByProfessor(string courseCode) {
        bool courseRemoved = enrolledCourses.popElementIf([&](Course* c) {
            return c->getCourseCode() == courseCode;
            });
        return courseRemoved;
    }
};

#endif // __STUDENT_HPP__
