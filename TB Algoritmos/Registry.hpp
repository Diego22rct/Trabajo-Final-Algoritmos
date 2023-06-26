#ifndef __REGISTRY__HPP__
#define __REGISTRY__HPP__
#include "Student.hpp"
#include "DLL.hpp"
#include "Professor.hpp"
#include "Administrator.hpp"
#include "Forum.hpp"
#include "BST.hpp"
#include "Library.hpp"
using namespace std;

class Registry {
private:
    DLL<Student*> studentDatabase;
    DLL<Professor*> professorDatabase;
    DLL<Administrator*> adminDatabase;
    BST<Student*> studentTree;
    BST<Professor*> professorTree;
    BST<Administrator*> administratorTree;
    Forum forum;
    Library library;
public:
    Registry() :
        studentTree(
            [](Student* student) -> void {
                if (student) cout << student->getName() << " (" << student->getId() << ")\n";
            },
            [](Student* a, Student* b) -> bool {
                if (a && b) return a->getId() > b->getId();
                return false;
            },
            [](Student* a, Student* b) -> bool {
                if (a && b) return a->getId() == b->getId();
                return false;
            }
        ),
        professorTree(
            [](Professor* professor) -> void {
                if (professor) cout << professor->getName() << " (" << professor->getId() << ")\n";
            },
            [](Professor* a, Professor* b) -> bool {
                if (a && b) return a->getId() > b->getId();
                return false;
            },
            [](Professor* a, Professor* b) -> bool {
                if (a && b) return a->getId() == b->getId();
                return false;
            }
        ),
        administratorTree(
            [](Administrator* administrator) -> void {
                if (administrator) cout << administrator->getName() << " (" << administrator->getId() << ")\n";
            },
            [](Administrator* a, Administrator* b) -> bool {
                if (a && b) return a->getId() > b->getId();
                return false;
            },
            [](Administrator* a, Administrator* b) -> bool {
                if (a && b) return a->getId() == b->getId();
                return false;
            }
        )
    {
        loadStudents();
      
        loadProfessors();
        
        loadAdmins();
    
        forum = Forum("Forum1");
        library = Library(0, 150);
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
        ofstream file("students.csv", ios::ate);
        if (file.is_open()) {
            studentDatabase.forEach([&](Student* student) {
				file << student->getName() << " " << student->getId() << " " << student->getEmail() << " "
					<< student->getMajor() << " " << student->getCycle() << " " << student->getPassword() << endl;
				});
			file.close();
		}
    }

    void saveProfessors() {
        ofstream file("professors.csv", ios::ate);
        if (file.is_open()) {
            professorDatabase.forEach([&](Professor* professor) {
				file << professor->getName() << " " << professor->getId() << " " << professor->getEmail() << " "
					<< " " << professor->getPassword() << endl;
				});
			file.close();
		}
    }

    void saveAdmins() {
        ofstream file("admins.csv", ios::ate);
        if (file.is_open()) {
            adminDatabase.forEach([&](Administrator* admin) {
				file << admin->getName() << " " << admin->getId() << " " << admin->getEmail() << " "
					<< " " << admin->getPassword() << endl;
				});
			file.close();
		}
    }

    void loadStudents() {
        ifstream file("students.csv");
        string name, id, email, major, password;
        int cycle;

        if (file.is_open()) {
            while (file >> name >> id >> email >> major >> cycle >> password) {
                Student* student = new Student(name, id, email, major, cycle, password);
                studentDatabase.pushBack(student);
                studentTree.insert(student);
            }
            file.close();
        }
        else
        {
            cout << "read file error" << endl;
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
        else
        {
            cout << "read file error" << endl;
        }
    }

    void loadAdmins() {
        ifstream file("admins.csv");
        string name, id, email, role, password;

        if (file.is_open()) {
            while (file >> name >> id >> email >> password) {
                Administrator* admin = new Administrator(id, name, email, password);
                adminDatabase.pushBack(admin);
            }
            file.close();
        }
        else
        {
            cout << "read file error" << endl;
        }
    }

    bool verifyLogin(string id, string password, string role) {
        bool found = false;
        
        if (role == "alumno") {
            auto a = studentDatabase.getByCriteria(
                [&](Student* student) {
					return student->getId() == id && student->getPassword() == password;
				});
            if (a != nullptr) {
				found = true;
                system("cls");
                cout << "Bienvenido " << a->getName() << endl;
                studentMenu(a);
			}
        }
        else if (role == "profesor") {
            auto p = professorDatabase.getByCriteria(
                [&](Professor* professor) {
                    return professor->getId() == id && professor->getPassword() == password;
                });
            if (p != nullptr) {
                found = true;
                system("cls");
                cout << "Bienvenido " << p->getName() << endl;
                professorMenu(p, studentDatabase);
            }
        }

        else if (role == "administrador") {
            auto admin = adminDatabase.getByCriteria(
                [&](Administrator* admin) {
                    return admin->getId() == id && admin->getPassword() == password;
                });
            if (admin != nullptr) {
                found = true;
                system("cls");
                cout << "Bienvenido " << admin->getName() << endl;
                adminMenu(admin, studentTree, professorTree);
            }
        }
        return found;
    }

    void adminMenu(Administrator* admin, BST<Student*>& studentTree, BST<Professor*>& professorTree) {
        int option;
        do {
            cout << "==========Menu==========\n";
            cout << "1. Ver lista de alumnos\n";
            cout << "2. Ver lista de profesores\n";
            cout << "3. Buscar alumno por identificador\n";
            cout << "4. Buscar profesor por identificador\n";
            cout << "5. Buscar administrador por identificador\n";
            cout << "6. Agregar un alumno\n";
            cout << "7. Agregar un profesor\n";
            cout << "8. Eliminar un alumno\n";
            cout << "9. Eliminar un profesor\n";
            cout << "10. Salir\n";
            cout << "Ingrese una opcion: ";
            cin >> option;

            switch (option) {
            case 1: {
                cout << "Lista de alumnos:\n";
                studentTree.inOrder();
                break;   
            }
            case 2: {
                cout << "Lista de profesores:\n";
                professorTree.inOrder();
                break;
            }
            case 3: {
                cout << "Ingrese el identificador del alumno: ";
                string id;
                cin >> id;
                Student* keyStudent = new Student("", id, "", "", 0, "");
                /*Student* foundStudent = studentTree.find(keyStudent);
                if (foundStudent) {
                    cout << "Alumno encontrado: " << foundStudent->getName() << " (" << foundStudent->getId() << ")\n";
                }
                else {
                    cout << "Alumno no encontrado.\n";
                }*/
                auto s = studentTree.find(keyStudent);
                if (s != nullptr) {
					cout << "Alumno encontrado: " << s->getName() << " (" << s->getId() << ")\n";
				}
                else {
					cout << "Alumno no encontrado.\n";
				}
                break;
            }
            case 4: {
                cout << "Ingrese el identificador del profesor: ";
                string id;
                cin >> id;
                Professor* keyProfessor = new Professor("", id, "", "");
                auto p = professorTree.find(keyProfessor);
                if (p != nullptr) {
                    cout << "Profesor encontrado: " << p->getName() << " (" << p->getId() << ")\n";
                }
                else {
                    cout << "Profesor no encontrado.\n";
                }
                break;
            }
            case 5: {
                cout << "Ingrese el identificador del administrador: ";
                string id;
                cin >> id;
                Administrator* keyAdmin = new Administrator("", id, "", "");
                auto a = administratorTree.find(keyAdmin);
                if (a != nullptr) {
                    cout << "Administrador encontrado: " << a->getName() << " (" << a->getId() << ")\n";
                }
                else {
                    cout << "Administrador no encontrado.\n";
                }
                break;
            }
            case 6: {
                cout << "Agregar un alumno:\n";
                string name, id, email, major, password;
                int cycle;
                cout << "Ingrese el nombre: ";
                cin >> name;
                cout << "Ingrese el código: ";
                cin >> id;
                cout << "Ingrese el correo: ";
                cin >> email;
                cout << "Ingrese su carrera: ";
                cin >> major;
                cout << "Ingrese el ciclo: ";
                cin >> cycle;
                cout << "Ingrese la contraseña: ";
                cin >> password;

                Student* newStudent = new Student(name, id, email, major, cycle, password);
                studentTree.insert(newStudent);
                saveStudents();
                cout << "Alumno agregado exitosamente.\n";
                break;
            }
            case 7: {
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
                professorTree.insert(newProfessor);
                saveProfessors();
                cout << "Profesor agregado exitosamente.\n";
                break;
            }
            case 8: {
                cout << "Eliminar un alumno:\n";
                string codeStudent;
                cout << "Ingrese el código del alumno: ";
                cin >> codeStudent;

                Student* studentToDelete = new Student("", codeStudent, "", "", 0, "");
                studentTree.remove(studentToDelete);
                cout << "Alumno eliminado exitosamente.\n";
                break;
            }
            case 9: {
                cout << "Eliminar un profesor:\n";
                string codeProfessor;
                cout << "Ingrese el código del profesor: ";
                cin >> codeProfessor;

                Professor* professorToDelete = new Professor("", codeProfessor, "", "");
                professorTree.remove(professorToDelete);
                cout << "Profesor eliminado exitosamente.\n";
                break;
            }
            case 10:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (option != 10);
    }

    void professorMenu(Professor* professor, DLL<Student*>& students) {
        int option;
        do {
            cout << "==========Menu==========\n";
            cout << "1. Ver cursos dictados\n";
            cout << "2. Modificar las notas de un alumno\n";
            cout << "3. Eliminar nota de un alumno\n";
            cout << "4. Ingresar al foro\n";
            cout << "5. Salir\n";
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
            case 4: {
                forum.showMesages();
                cout << "Ingresar el mensaje\n";
                string message;
                getline(cin >> ws, message);
                forum.addMessageProfessor(professor, message);
            } break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (option != 5);
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
            cout << "6. Ingresar al foro\n";
            cout << "7. Ver Biblioteca\n";
            cout << "8. Salir\n";
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
            case 6: {
                cout << "Foro: " << forum.getforumName() << endl;
                forum.showMesages();
                string message;
                cout << "Ingrese el mensaje: ";
                getline(cin >> ws, message);
                forum.addMessage(student, message);
            }break;
            case 7: {
                cout << "Biblioteca" << endl;
                library.showBooks();
                string codeBook;
                cout << "Ingrese el codigo del libro que desea ver: ";

            } break;
            case 8:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (option != 8);
    }

    // Inicio Programa

    bool iniciarPrograma() {
        srand(time(0));
        int option;
        do {
            system("cls");
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
                cout << "Ingrese su rol (alumno, profesor, administrador ): ";
                cin >> role;
                if (!verifyLogin(id, password, role)) {
                    cout << "No se pudo iniciar sesion" << endl;
                }
                break;
            }
            case 3:
                cout << "Saliendo del programa...\n";
               //saveStudents();
                return false;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
            return true;
        } while (option != 3);
    }
};

#endif // !__REGISTRO__HPP__