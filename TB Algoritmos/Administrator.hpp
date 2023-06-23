#ifndef __ADMINISTRATOR_HPP__
#define __ADMINISTRATOR_HPP__
#include "User.hpp"
#include "DLL.hpp"
#include "Professor.hpp"
#include "Student.hpp"

class Administrator : public User {
private:
    string role;

public:
    Administrator(string id = " ", string name = " ", string email = " ", string password = " ")
        : User(id, name, email, password, "administrador"), role(role) {}

    string getRole() {
        return role;
    }

    void viewStudents(DLL<Student*>& studentsDB) {
        studentsDB.forEach([](Student* s) {
            cout << s->getName() << ", " << s->getId() << ", " << s->getMajor() << ", " << s->getCycle() << "\n";
            });
    }

    void viewProfessors(DLL<Professor*>& professorsDB) {
        professorsDB.forEach([](Professor* p) {
            cout << p->getName() << ", " << p->getId() << ", " << "\n";
            });
    }

    void addUserProfessor(DLL<Professor*>& professors, Professor* professor) {
        professors.pushBack(professor);
        cout << "Professor successfully added." << endl;
    }

    void addUserStudent(DLL<Student*>& students, Student* student) {
        students.pushBack(student);
        cout << "Student successfully added." << endl;
    }

    void deleteUserProfessor(DLL<Professor*>& professors, string id) {
        bool professorDeleted = false;

        professors.forEach([id, &professorDeleted](Professor* professor) {
            if (professor->getId() == id) {
                delete professor;
                professorDeleted = true;
            }
            });

        if (professorDeleted) {
            professors.popAllElementsIf([id](Professor* professor) {
                return professor->getId() == id;
                });
            cout << "Professor correctly deleted." << endl;
        }
        else {
            cout << "Professor not found." << endl;
        }
    }

    void deleteUserStudent(DLL<Student*>& students, string id) {
        bool studentDeleted = false;

        students.forEach([id, &studentDeleted](Student* student) {
            if (student->getId() == id) {
                delete student;
                studentDeleted = true;
            }
            });

        if (studentDeleted) {
            students.popAllElementsIf([id](Student* student) {
                return student->getId() == id;
                });
            cout << "Student correctly deleted." << endl;
        }
        else {
            cout << "Student not found." << endl;
        }
    }

    void updateUserProfessor(DLL<Professor*>& professors, Professor* updatedProfessor) {
        string id = updatedProfessor->getId();

        professors.forEach([id, updatedProfessor](Professor* professor) {
            if (professor->getId() == id) {
                *professor = *updatedProfessor;
                cout << "Professor's information correctly updated." << endl;
            }
            });
    }

    void updateUserStudent(DLL<Student*>& students, Student* updatedStudent) {
        string id = updatedStudent->getId();

        students.forEach([id, updatedStudent](Student* student) {
            if (student->getId() == id) {
                *student = *updatedStudent;
                cout << "Student's information correctly updated." << endl;
            }
            });
    }
};

#endif // !_ADMINISTRATOR_HPP_
