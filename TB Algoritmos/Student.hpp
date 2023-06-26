#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__
#include "User.hpp"
#include "Course.hpp"
#include "DLL.hpp"
#include <fstream>
using namespace std;

class Student : public User {
private:
    int cycle;
    string major;
    HT<Course>* enrolledCourses;
    HT<Course>* availableCourses;

public:
    Student(string name = " ", string id = " ", string email = " ", string major = " ", int cycle = 0, string password = " ")
        : User(id, name, email, password, "alumno"), major(major), cycle(cycle) {
        availableCourses = new HT<Course>(300);
        enrolledCourses = new HT<Course>(100);
    }

    ~Student() {
        delete availableCourses;
        delete enrolledCourses;
    }

    string getMajor() {
        return major;
    }

    int getCycle() {
        return cycle;
    }

    void addCourse(string courseCode, Course course) {
        availableCourses->insert(courseCode, course);
    }

    Course getCourse(string courseCode) {
        return availableCourses->search(courseCode);
    }

    void removeCourse(string courseCode) {
        availableCourses->remove(courseCode);
    }

    void showAvailableCourses() {
        availableCourses->display1([](Course& course) {
            cout << course.toString() << endl;
            });
    }

    void enrollCourse(string code) {
        Course courseToEnroll = getCourse(code);
        enrolledCourses->insert(code, courseToEnroll);
        cout << "Course enrolled" << endl;
        // saveCourse(&courseToEnroll);  // Aquí necesitas definir la función saveCourse
    }
};

#endif // __STUDENT_HPP__
