#ifndef __COURSEMANAGER_HPP__
#define __COURSEMANAGER_HPP__

#include "Course.hpp"
#include "HT.hpp"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class CourseManager {
private:
    HT<Course>* courses;

public:
    CourseManager(){
        courses = new HT<Course>(10);
        cout << "Cargando cursos..." << endl;
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
        //courses->remove(courseCode);
    }

    void displayCourses() {
        this->courses->display([](Course course) {
            cout << course.toString() << endl;
            });
    }

    void loadCourses() {
        ifstream file("CURSOS.csv");
        string idx, name, code;

        if (file.is_open()) {
            while (getline(file, idx, ';'), getline(file, name, ';'), getline(file, code)) {
				Course course(name, code);
				addCourse(code, course);
                cout << "Cargando curso: " << course.toString() << endl;
			}
			file.close();
		}
    }
};

#endif
