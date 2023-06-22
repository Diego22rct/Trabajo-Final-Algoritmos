#ifndef __REGISTRY__HPP__
#define __REGISTRY__HPP__
#include "Student.hpp"
#include "DLL.hpp"
#include "Professor.hpp"
#include "Administrator.hpp"

class Registry {
private:
    DLL<Student*> studentDatabase;
    DLL<Professor*> professorDatabase;
    DLL<Administrator*> adminDatabase;

public:
    Registry() {
        loadStudents();
        loadProfessors();
        loadAdmins();
    }

    ~Registry() {
        saveStudents();
        saveProfessors();
        saveAdmins();

        studentDatabase.forEach([&](Student* student) {
            delete student;
            });
        professorDatabase.forEach([&](Professor* professor) {
            delete professor;
            });
        adminDatabase.forEach([&](Administrator* admin) {
           delete admin;
            });
    }

    void saveStudents() {
        ofstream file("students.csv");
        if (file.is_open()) {
            studentDatabase.forEach([&](Student* student) {
                file << student->getName() << " " << student->getId() << " " << student->getEmail() << " "
                    << student->getCycle() << " " << student->getPassword() << endl;
                });
            file.close();
        }
        else {
            cout << "No se pudo abrir";
        }
    }

    void saveProfessors() {
        ofstream file("professors.txt");
        if (file.is_open()) {
            professorDatabase.forEach([&](Professor* professor) {
                file << professor->getName() << " " << professor->getId() << " " << professor->getEmail() << " "
                    << professor->getPassword() << endl;
                });
            file.close();
        }
    }

    void saveAdmins() {
        ofstream file("admins.txt");
        if (file.is_open()) {
            adminDatabase.forEach([&](Administrator* admin) {
                file << admin->getName() << " " << admin->getId() << " " << admin->getEmail() << " "
                    << " " << admin->getPassword() << endl;
                });
            file.close();
        }
    }

    void showStudents() {
        studentDatabase.forEach([](Student* s) {
            cout << s->getName() << ", " << s->getId() << ", " << s->getMajor() << ", " << s->getCycle() << "\n";
            });
    }

    void showProfessors() {
        professorDatabase.forEach([](Professor* p) {
            cout << p->getName() << ", " << p->getId() << ", " << "\n";
            });
    }

    void showAdmins() {
        adminDatabase.forEach([](Administrator* a) {
            cout << a->getName() << ", " << a->getId() << ", " << a->getEmail() << ", " << "\n";
            });
    }

    void loadStudents() {
        ifstream file("students.txt");
        string name, id, email, major, password;
        int cycle;

        if (file.is_open()) {
            while (file >> name >> id >> email >> major >> cycle >> password) {
                Student* student = new Student(name, id, email, major, cycle, password);
                studentDatabase.pushBack(student);
            }
            file.close();
        }
    }

    void loadProfessors() {
        ifstream file("professors.csv");
        string name, id, email, password;

        if (file.is_open()) {
            while (file >> name >> id >> email >> password) {
                Professor* professor = new Professor(id, name, email, password);
                professorDatabase.pushBack(professor);
            }
            file.close();
        }
    }

    void loadAdmins() {
        ifstream file("admins.csv");
        string name, id, email, role, password;

        if (file.is_open()) {
            while (file >> name >> id >> email >> role >> password) {
                Administrator* admin = new Administrator(id, name, email, role, password);
                adminDatabase.pushBack(admin);
            }
            file.close();
        }
    }

    bool verifyLogin(string id, string password, string role) {
        bool found = false;
        if (role == "alumno") {
            studentDatabase.forEach([&](Student* student) {
                if (student->getId() == id && student->getPassword() == password) {
                    system("cls");
                    cout << "Bienvenido " << student->getName() << endl;
                    studentMenu(student);
                    found = true;
                }
                });
        }
        else if (role == "profesor") {
            professorDatabase.forEach([&](Professor* professor) {
                if (professor->getId() == id && professor->getPassword() == password) {
                    system("cls");
                    cout << "Bienvenido " << professor->getName() << endl;
                    professorMenu(professor, studentDatabase);
                    found = true;
                }
                });
        }
        else if (role == "administrador") {
            adminDatabase.forEach([&](Administrator* admin) {
                if (admin->getId() == id && admin->getPassword() == password) {
                    system("cls");
                    cout << "Bienvenido " << admin->getName() << endl;
                    adminMenu(admin, professorDatabase, studentDatabase);
                    found = true;
                }
                });
        }
        return found;
    }

    void adminMenu(Administrator* admin, DLL<Professor*>& professorDatabase, DLL<Student*>& studentDatabase) {
        int option;
        do {
            cout << "==========Menu==========\n";
            cout << "1. Ver lista de alumnos\n";
            cout << "2. Ver lista de profesores\n";
            cout << "3. Agregar un alumno\n";
            cout << "4. Agregar un profesor\n";
            cout << "5. Eliminar un alumno\n";
            cout << "6. Eliminar un profesor\n";
            cout << "7. Salir\n";
            cout << "Ingrese una opcion: ";
            cin >> option;

            switch (option) {
            case 1: {
                cout << "Lista de alumnos:\n";
                admin->viewStudents(studentDatabase);
                break;
            }
            case 2: {
                cout << "Lista de profesores:\n";
                admin->viewProfessors(professorDatabase);
                break;
            }
            case 3: {
                cout << "Agregar un alumno:\n";
                string name, id, email, major, password;
                int cycle;
                cout << "Ingrese el nombre: ";
                cin >> name;
                cout << "Ingrese el código: ";
                cin >> id;
                cout << "Ingrese el correo: ";
                cin >> email;
                cout << "Ingrese el ciclo: ";
                cin >> cycle;
                cout << "Ingrese la contraseña: ";
                cin >> password;

                Student* newStudent = new Student(name, id, email, major, cycle, password);
                studentDatabase.pushBack(newStudent);
                saveStudents();
                cout << "Alumno agregado exitosamente.\n";
                break;
            }
            case 4: {
                cout << "Agregar un profesor:\n";
                string name, id, email, password;
                cout << "Ingrese el nombre: ";
                cin >> name;
                cout << "Ingrese el código: ";
                cin >> id;
                cout << "Ingrese el correo: ";
                cin >> email;
                cout << "Ingrese la contraseña: ";
                cin >> password;

                Professor* newProfessor = new Professor(name, id, email, password);
                professorDatabase.pushBack(newProfessor);
                saveProfessors();
                cout << "Profesor agregado exitosamente.\n";
                break;
            }
            case 5: {
                cout << "Eliminar un alumno:\n";
                string codeStudent;
                cout << "Ingrese el código del alumno: ";
                cin >> codeStudent;

                studentDatabase.popAllElementsIf([&](Student* student) {
                    return student->getId() == codeStudent;
                });
                cout << "Alumno eliminado exitosamente.\n";
                break;
            }
            case 6: {
                cout << "Eliminar un profesor:\n";
                string codeProfessor;
                cout << "Ingrese el código del profesor: ";
                cin >> codeProfessor;

                professorDatabase.popAllElementsIf([&](Professor* professor) {
                    return professor->getId() == codeProfessor;
                    });

                cout << "Profesor eliminado exitosamente.\n";
                break;
            }
            case 7:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (option != 7);
    }


    void professorMenu(Professor* professor, DLL<Student*>& students) {
        int option;
        do {
            cout << "==========Menu==========\n";
            cout << "1. Ver cursos dictados\n";
            cout << "2. Modificar las notas de un alumno\n";
            cout << "3. Eliminar nota de un alumno\n";
            cout << "4. Salir\n";
            cout << "Ingrese una opcion: ";
            cin >> option;

            switch (option) {
            case 1: {
                cout << "Cursos dictados:\n";
                //professor->verListaDeAlumnos(students);
                professor->viewCoursesStudents(students);
                break;
            }
            case 2: {
                professor->viewCoursesStudents(students);
                string codeCourse, codeStudent;
                double newGrade;
                cout << "Ingrese el código del alumno: ";
                cin >> codeStudent;
                cout << "Ingrese el código del curso: ";
                cin >> codeCourse;
                cout << "Ingrese la nueva nota: ";
                cin >> newGrade;
                professor->modifyStudentGrade(students, codeStudent, codeCourse, newGrade);
                break;
            }
            case 3: {
                professor->viewCoursesStudents(students);
                string codeCourse;
                cout << "Ingrese el código del curso: ";
                cin >> codeCourse;
                professor->removeStudentGrade(students, codeCourse);
                break;
            }
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (option != 4);
    }

    void studentMenu(Student* student) {
        int option;
        do {
            cout << "======Menu de opciones======\n";
            cout << "1. Ver cursos disponibles\n";
            cout << "2. Ver cursos matriculados\n";
            cout << "3. Matricularse en un curso\n";
            cout << "4. Ver notas de los cursos\n";
            cout << "5. Retirarse de un curso\n";
            cout << "6. Salir\n";
            cout << "Ingrese una opcion: ";
            cin >> option;

            switch (option) {
            case 1:
                student->showCourses();
                break;
            case 2:
                student->showEnrolledCourses();
                break;
            case 3: {
                cout << "Cursos disponibles:\n";
                student->showCourses();
                string codigoCurso;
                cout << "Ingrese el codigo del curso: ";
                cin >> codigoCurso;
                student->enrollCourse(codigoCurso);
                break;
            }
            case 4:
                student->checkGrades();
                break;
            case 5: {
                cout << "Cursos matriculados:\n";
                student->showEnrolledCourses();
                string codeCourse;
                cout << "Ingrese el codigo del curso que desea retirar: ";
                cin >> codeCourse;
                student->withdrawCourse();
                break;
            }
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (option != 6);
    }

    // Inicio Programa

    void iniciarPrograma() {
        srand(time(0));
        int option;
        do {
            cout << "Menu de registro\n";
            cout << "1. Registrarse\n";
            cout << "2. Iniciar sesion\n";
            cout << "3. Salir\n";
            cout << "Ingresa una opcion: ";
            cin >> option;

            switch (option) {
            case 1: {
                string name, id, email, password, role;
                cout << "Ingrese su nombre: ";
                cin >> name;
                cout << "Ingrese su codigo: ";
                cin >> id;
                cout << "Ingrese su correo: ";
                cin >> email;
                cout << "Ingrese su contrasena: ";
                cin >> password;
                cout << "Seleccione un rol (alumno,profesor,administrador): ";
                cin >> role;

                if (role == "alumno") {
                    string major;
                    int cycle;
                    cout << "Ingrese su carrera: ";
                    cin >> major;
                    cout << "Ingrese su ciclo: ";
                    cin >> cycle;
                    Student* studentRegistry = new Student(name, id, email, major, cycle, password);
                    studentRegistry->setPassword(password);
                    studentDatabase.pushBack(studentRegistry);
                    saveStudents();
                    cout << "Alumno registrado correctamente.\n";
                }
                else if (role == "profesor") {
                    Professor* profesorRegistry = new Professor(name, id, email, password);
                    profesorRegistry->setPassword(password);
                    professorDatabase.pushBack(profesorRegistry);
                    saveProfessors();
                    cout << "Profesor registrado correctamente.\n";
                }
                else if (role == "administrador") {
                    Administrator* administratorRegistry = new Administrator(name, id, email, password);
                    administratorRegistry->setPassword(password);
                    adminDatabase.pushBack(administratorRegistry);
                    saveAdmins();
                    cout << "Administrador registrado correctamente.\n";
                }
                else {
                    cout << "Opcion invalida. Intente de nuevo.\n";
                }
                break;
            }
            case 2: {
                string id, password, role;
                cout << "Ingrese su codigo: ";
                cin >> id;
                cout << "Ingrese su contrasena: ";
                cin >> password;
                cout << "Ingrese su rol: ";
                cin >> role;
                if (!verifyLogin(id, password, role)) {
                    cout << "No se pudo iniciar sesion" << endl;
                }
                break;
            }
            case 3:
                cout << "Saliendo del programa...\n";
                exit(0);
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (option != 3);
    }
};

#endif // !__REGISTRO__HPP__