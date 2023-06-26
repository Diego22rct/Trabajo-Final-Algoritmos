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

};
#endif
