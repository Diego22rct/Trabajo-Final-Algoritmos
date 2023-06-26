#ifndef __COURSE_HPP__
#define __COURSE_HPP__
#include <string>
#include <iostream>
using namespace std;

class Course {
private:
    string courseName;
    string courseCode;
public:
    Course(string courseName = "", string courseCode = "") 
        : courseName(courseName), courseCode(courseCode) {
    }

    friend ostream& operator<<(ostream& os, const Course& course) {
		os << course.courseName << " " << course.courseCode << "\n";
		return os;
	}

    string toString() {
        return courseName + " " + courseCode + "\n";
    }

    string getCourseName() {
        return courseName;
    }

    string getCourseCode() {
        return courseCode;
    }
};

#endif // !_COURSE_HPP_
