#ifndef __USER_HPP__
#define __USER_HPP__
#include <string>
using namespace std;

class User {
protected:
    string id;
    string name;
    string email;
    string password;
    string role;
public:
    User(string id = "", string name = "", string email = "", string password = "", string role = "") : id(id), name(name), email(email), password(password), role(role) {}

    string getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getEmail() {
        return email;
    }

    string getPassword() {
        return password;
    }

    string getRole() {
        return role;
    }

    void setId(string id) {
        this->id = id;
    }

    void setName(string name) {
        this->name = name;
    }

    void setEmail(string email) {
        this->email = email;
    }

    void setPassword(string password) {
        this->password = password;
    }

    void setRole(string role) {
        this->role = role;
    }
};

#endif // __USER_HPP__
