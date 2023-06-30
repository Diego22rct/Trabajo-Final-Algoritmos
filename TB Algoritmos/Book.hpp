#ifndef __BOOK_HPP__
#define __BOOK_HPP__
#include <iostream>
#include <string>

using namespace std;

class Book
{
private:
    string title;
    string name;
    string lastName;
    string date;

public:
    Book(string title = "", string name = "", string lastName = "", string date = "") : title(title), date(date), name(name), lastName(lastName)
    {
    }

    ~Book()
    {
    }

    friend ostream& operator<<(ostream& os, const Book& book)
    {
        os << book.title << " " << book.date << " " << book.name << " " << book.lastName << endl;
        return os;
    }

    bool operator==(Book other)
    {
        return title == other.title;
    }

    // setters and getters

    void setTitle(string title) { this->title = title; }
    void setDate(string date) { this->date = date; }

    string getTitle() { return title; }
    string getDate() { return date; }
    string getName() { return name; }
    string getLastName() { return lastName; }
};



#endif // !__BOOK_HPP__
