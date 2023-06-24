#ifndef _FORUM_HPP_
#define _FORUM_HPP_
#include <iostream>
#include <string>
#include <fstream>
#include "Vector.hpp"
#include "Message.hpp"
#include "Student.hpp"
#include "Professor.hpp"

using namespace std;

class Forum
{
private:
	string forumName;
	Vector<Message> messages;
public:
	Forum(string forumName = "") : forumName(forumName)
	{
		readForum();
	}
	~Forum() {}

	//Leer foro
	void readForum() {
		ifstream file;
		file.open("Forum1.txt", ios::in);
		if (file.fail()) {
			cout << "No se pudo abrir el archivo" << endl;
		}
		else {
			string id;
			string codeUser;
			string text;
			while (!file.eof()) {
				getline(file, id, ';');
				getline(file, codeUser, ';');
				getline(file, text, '\n');
				Message message(id, codeUser, text);
				messages.push_back(message);
			}
			cout << "Foro leido" << endl;
		}
		file.close();
	}
	//guardar foro
	void saveForum() {
		//sobre escribir todo el archivo
		ofstream file;
		file.open("Forum1.txt", ios::ate);
		if (file.fail()) {
			cout << "No se pudo abrir el archivo" << endl;
		}
		else {
			for (int i = 0; i < messages.size(); i++) {
				file << messages[i].getId() << ";" << messages[i].getCodeUser() << ";" << messages[i].getText() << endl;
			}
			cout << "Mensaje guardado" << endl;
		}
	}
	//agregar mensaje
	void addMessage(Student* u, string msg) {
		Message message(to_string(messages.size() + 1), u->getId(), msg);
		messages.push_back(message);
		saveForum();
	}
	void addMessageProfessor(Professor* p, string msg) {
		Message message(to_string(messages.size() + 1), p->getId(), "Professor add: " + msg);
		messages.push_back(message);
		saveForum();
	}

	void showMesages() {
		if (messages.size() == 1) {
			cout << "No hay mensajes en el foro, Se el primero\n";
		}
		else
		{
			for (int i = 0; i < messages.size()-1; i++) {
				cout << i << "ID: " + messages[i].getId() << " User: " << messages[i].getCodeUser() << ": " << messages[i].getText() << "\n";
			}
		}
	}
	string getforumName() {
		return forumName;
	}
};

#endif // !_FORUM_HPP_