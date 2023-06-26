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
				cout << "Course name: " << course->getCourseName() << endl;
				cout << "Course code: " << course->getCourseCode() << endl;
				//cout << "Final grade: " << course->getFinalGrade() << endl;
				cout << "-------------------\n";
				});
        });

    }

    void modifyStudentGrade(DLL<Student*>& students, string studentId, string courseCode, double newGrade) {
        bool studentFound = false;
        bool courseFound = false;

        students.findAndApply(
			[studentId](Student* student) { return student->getId() == studentId; },
            [&studentFound, &courseFound, courseCode, newGrade](Student* student) {
				studentFound = true;
                student->getEnrolledCourses().findAndApply(
					[courseCode](Course* course) { return course->getCourseCode() == courseCode; },
                    [&courseFound, newGrade](Course* course) {
						courseFound = true;
						//course->setGrade(newGrade);
						cout << "Grade modified correctly." << endl;
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

        students.forEach([&courseFound, courseCode](Student* student) {
            student->getEnrolledCourses().findAndApply(
				[courseCode](Course* course) { return course->getCourseCode() == courseCode; },
                [&courseFound](Course* course) {
					courseFound = true;
					//course->setGrade(0);
				}
			);
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
