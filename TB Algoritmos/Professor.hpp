#ifndef __PROFESSOR_HPP__
#define __PROFESSOR_HPP__
#include "User.hpp"
#include "Course.hpp"
#include "DLL.hpp"
#include "Student.hpp"

class Professor : public User {
public:
    Professor(string id = " ", string name = " ", string email = " ", string password = " ")
        : User(id, name, email, password, "profesor") {
    }

    void viewCoursesStudents(DLL<Student*>& students) {
        students.forEach([this](Student* student) {
            cout << "Student name: " << student->getName() << endl;
            cout << "Student ID: " << student->getId() << endl;
            cout << "Enrolled courses:\n";
            student->getEnrolledCourses().forEach([](Course* course) {
                cout << course->toString() << endl;
                });
            });
    }

    void modifyStudentGrade(DLL<Student*>& students, string studentId, string courseCode, double newGrade) {
        bool studentFound = false;
        bool courseFound = false;

        students.findAndApply(
            [studentId](Student* student) { return student->getId() == studentId; },
            [this, studentId, courseCode, newGrade, &studentFound, &courseFound](Student* student) {
                studentFound = true;
                cout << "Student found: " << student->getName() << endl;
                auto searchCriteria = [courseCode](Course* course) { return course->getCourseCode() == courseCode; };
                student->getEnrolledCourses().findAndApply(
                    searchCriteria,
                    [this, studentId, courseCode, newGrade, &courseFound](Course* course) {
                        course->setGrade(newGrade);
                        courseFound = true;
                        cout << "Course found and grade modified." << endl;
                    }
                );
            }
        );

        if (!studentFound) {
            cout << "Student not found." << endl;
        }
        else if (!courseFound) {
            cout << "Course not found for the specified student." << endl;
        }
    }

    void removeStudentGrade(DLL<Student*>& students, string courseCode) {
        bool courseFound = false;

        students.forEach([courseCode, &courseFound](Student* student) {
            int numCoursesBefore = student->getEnrolledCourses().size();
            student->getEnrolledCourses().popAllElementsIf([courseCode](Course* course) {
                return course->getCourseCode() == courseCode;
                });
            int numCoursesAfter = student->getEnrolledCourses().size();

            if (numCoursesBefore > numCoursesAfter) {
                courseFound = true;
            }
            });

        if (courseFound) {
            cout << "Grade deleted correctly." << endl;
        }
        else {
            cout << "Course not found." << endl;
        }
    }

    void addCourseToStudent(DLL<Student*>& students, string studentId, Course* newCourse) {
        bool studentFound = false;

        students.findAndApply(
            [studentId](Student* student) { return student->getId() == studentId; },
            [&studentFound, newCourse](Student* student) {
                studentFound = true;
                student->addCourseByProfessor(newCourse);
                cout << "Course added to student's courses." << endl;
            }
        );

        if (!studentFound) {
            cout << "Student not found." << endl;
        }
    }

    void removeCourseFromStudent(DLL<Student*>& students, string studentId, string courseCode) {
        bool studentFound = false;
        bool courseRemoved = false;

        students.findAndApply(
            [studentId](Student* student) { return student->getId() == studentId; },
            [&studentFound, courseCode, &courseRemoved](Student* student) {
                studentFound = true;
                courseRemoved = student->removeCourseByProfessor(courseCode);

                if (courseRemoved) {
                    cout << "Course removed from student's courses." << endl;
                }
            }
        );

        if (!studentFound) {
            cout << "Student not found." << endl;
        }
        else if (!courseRemoved) {
            cout << "Course not found in the student's courses." << endl;
        }
    }

};
#endif