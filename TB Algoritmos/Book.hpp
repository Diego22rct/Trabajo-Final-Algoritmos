#ifndef __BOOK_HPP__
#define __BOOK_HPP__
#include <iostream>
#include <string>

using namespace std;

class Book
{
private:
    string title;
    struct Author
    {
        string name;
        string lastName;
    };
    string date;
    Author* author;

public:
    Book(string title = "", string name = "", string lastName = "", string date = "") : title(title), date(date)
    {
        author = new Author;
        author->name = name;
        author->lastName = lastName;
    }

    ~Book()
    {
        delete author;
    }

    friend ostream& operator<<(ostream& os, const Book& book)
    {
        os << book.title << " " << book.date << " " << book.author->name << " " << book.author->lastName << endl;
        return os;
    }

    bool operator==(Book other)
    {
        return title.compare(other.title) == 0 && author->name == other.author->name && author->lastName == other.author->lastName && date == other.date;
    }

    // setters and getters

    void setTitle(string title) { this->title = title; }
    void setDate(string date) { this->date = date; }

    string getTitle() { return title; }
    string getDate() { return date; }
    string getName() { return author->name; }
    string getLastName() { return author->lastName; }
};



#endif // !__BOOK_HPP__
