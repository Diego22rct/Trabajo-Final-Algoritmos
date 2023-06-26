#ifndef __COURSEMANAGER_HPP__
#define __COURSEMANAGER_HPP__

#include "Course.hpp"
#include "HT.hpp"
#include <string>
#include <fstream>
using namespace std;

class CourseManager {
private:
    HT<Course>* courses;

public:
    CourseManager(int capacity) {
        courses = new HT<Course>(capacity);
        loadCourses();
    }

    ~CourseManager() {
        delete courses;
    }

    void addCourse(string courseCode, Course course) {
        courses->insert(courseCode, course);
    }

    Course getCourse(string courseCode) {
        return courses->search(courseCode);
    }

    void removeCourse(string courseCode) {
        courses->remove(courseCode);
    }

    void displayCourses() {
        this->courses->display([](Course course) {
            cout << course.toString() << endl;
            });
    }

    void loadCourses() {
        ifstream file("courses.csv", ios::in);
        string idx, name, code;
        if (file.is_open()) {
            while (getline(file, idx, ';') && getline(file, name, ';') && getline(file, code, ';')) {
                Course course(stoi(idx), name, code);
                addCourse(code, course);
            }
            file.close();
        }
        else {
            cout << "Error opening file" << endl;
        }
    }
};

#endif
