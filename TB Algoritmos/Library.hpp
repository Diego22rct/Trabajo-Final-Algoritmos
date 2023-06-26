#ifndef __LIBRARY_HPP__
#define __LIBRARY_HPP__

#include "Book.hpp"
#include "HT.hpp"

#include <fstream>

class Library
{
private:
	HT<Book*>* books;
	size_t quantity;
	size_t capacity;
public:
	Library(size_t quantity = 0, size_t capacity = 100) : quantity(quantity), capacity(capacity)
	{
		books = new HT<Book*>(capacity);
		readFile();
	}

	~Library()
	{
		saveFile();
		delete books;
	}
	void readFile() {
		//Delimiter ;
		ifstream file("books.csv");
		string line;
		string titleF;
		string nameF;
		string lastNameF;
		string dateF;
		if (file.is_open()) {
			while (file.eof())
			{
				getline(file, titleF, ';');
				getline(file, nameF, ';');
				getline(file, lastNameF, ';');
				getline(file, dateF, '\n');
				auto book = new Book(titleF, nameF, lastNameF, dateF);
				books->insert(book->getTitle(), book);
			}
			cout << "File readed" << endl;
		}
		else
		{
			cout << "Error opening file" << endl;
		}
		file.close();
	}

	void saveFile() {
		ofstream file("books.csv");
		if (file.is_open()) {
			auto show = [&file](Book* book) -> void {
				file << book->getTitle() << ";" << book->getName() << ";" << book->getLastName() << ";" << book->getDate() << endl;
			};
			cout << "File saved" << endl;
		}
		else
		{
			cout << "Error opening file" << endl;
		}
		file.close();
	}

	void addBook(Book* book) {
		books->insert(book->getTitle(), book);
	}

	void showBooks() {
		books->display([](Book* book) -> void {
			cout << book << endl;
			});
	}
};

#endif // !__LIBRARY_HPP__
