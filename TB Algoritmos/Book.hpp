#ifndef __BOOK_HPP__
#define __BOOK_HPP__
#include <iostream>
#include <string>

using namespace std;

class Book
{
private:
	string title;
	struct Autor
	{
		string name;
		string lastName;
	};
	string date;
	Autor *autor;

public:
	Book(string title = "", string name = "", string lastName = "", string date = "") : title(title), date(date)
	{
		autor = new Autor;
		autor->name = name;
		autor->lastName = lastName;
	}
	~Book()
	{
	}

	friend ostream& operator<<(ostream& os, const Book& book)
	{
		os << book.title << " " << book.date << endl;
		return os;
	}

	bool operator==(Book other)
	{
		return title.compare(other.title) == 0;
	}

	//setters and getters

	void setTitle(string title) { this->title = title; }
	void setDate(string date) { this->date = date; }


	string getTitle() { return title; }
	string getDate() { return date; }
	string getName() { return autor->name; }
	string getLastName() { return autor->lastName; }
};


#endif // !__BOOK_HPP__
