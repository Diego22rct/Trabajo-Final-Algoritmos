#ifndef __COURSE_HPP__
#define __COURSE_HPP__
#include <string>
#include <iostream>
using namespace std;

class Course {
private:
    int idx;
    string courseName;
    string courseCode;
    string major;
    int term;
    double finalGrade;
public:
    Course(int idx = 0, string courseName = "", string courseCode = "", string major = "", int term = 0, double finalGrade = 0.0)
        : idx(idx), courseName(courseName), courseCode(courseCode), major(major), term(term), finalGrade(finalGrade) {
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

    double getFinalGrade() {
        return finalGrade;
    }

    string getFinalGradeAsString() {
        return to_string(finalGrade);
    }

    void setGrade(double grade) {
        finalGrade = grade;
    }
};

#endif // !_COURSE_HPP_