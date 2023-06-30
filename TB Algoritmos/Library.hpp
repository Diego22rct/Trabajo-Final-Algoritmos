#ifndef __LIBRARY_HPP__
#define __LIBRARY_HPP__
#include "Book.hpp"
#include "HT.hpp"
#include <fstream>

class Library
{
private:
	HT<Book>* books;
	size_t capacity;

public:
	Library(size_t capacity = 100) : capacity(capacity)
	{
		books = new HT<Book>(capacity);
		readFile();
	}

	~Library()
	{
		saveFile();
	}

	void readFile() {
		ifstream file("books.csv", ios::in);
		string line;
		string titleF;
		string nameF;
		string lastNameF;
		string dateF;

		while (file >> titleF >> nameF >> lastNameF >> dateF) 
		{
			Book book(titleF, nameF, lastNameF, dateF);
			books->insert(book.getTitle(), book);
		}
	}

	void saveFile() {
		ofstream file("books.csv", ios::out);

	}

	void addBook(Book book) {
		books->insert(book.getTitle(), book);
	}

	void showBooks() {
		books->display([](Book book) -> void {
			cout << book << endl;
			});
	}
};

#endif // !__LIBRARY_HPP__
