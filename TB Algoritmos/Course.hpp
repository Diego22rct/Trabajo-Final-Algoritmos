#ifndef __COURSE_HPP__
#define __COURSE_HPP__
#include <string>
using namespace std;

class Course {
private:
    string courseName;
    string courseCode;
public:
    Course(string courseName = "", string courseCode = "") 
        : courseName(courseName), courseCode(courseCode) {
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
