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
		ifstream file("books.csv");
		string line;
		string titleF;
		string nameF;
		string lastNameF;
		string dateF;

		if (file.is_open()) {
			while (getline(file, titleF, ';')) {
				getline(file, nameF, ';');
				getline(file, lastNameF, ';');
				getline(file, dateF, '\n');
				Book book = Book(titleF, nameF, lastNameF, dateF);
				books->insert(book.getTitle(), book);
			}
			cout << "File readed" << endl;
		}
		else
		{
			throw "Error opening file";
		}
	}

	void saveFile() {
		//ofstream file("books.csv");
		//if (file.is_open()) {
		//	books->display([&](Book book) -> void {
		//		file << book.getTitle() << ";" << book.getName() << ";" << book.getLastName() << ";" << book.getDate() << endl;
		//		});
		//	cout << "File saved" << endl;
		//}
		//else
		//{
		//	throw runtime_error("Error opening file");
		//}
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
