#ifndef _FORUM_HPP_
#define _FORUM_HPP_
#include <iostream>
#include <string>
#include <fstream>
#include "Vector.hpp"
#include "Message.hpp"
#include "Student.hpp"
#include "Professor.hpp"
#include "Graph.hpp"

using namespace std;

class Forum
{
private:
	string forumName;
	Graph<Message>* messages;
	int size;
public:
	Forum(string forumName = "", int size = 0) : forumName(forumName), size(size)
	{
		messages = new Graph<Message>(100);
		readForum();
	}
	~Forum() {}

	//Leer foro
	void readForum() {
		ifstream file("Forum1.txt");
		if (file.fail()) {
			cout << "No se pudo abrir el archivo" << endl;
		}
		else {
			string id;
			string codeUser;
			string text;
			while (getline(file, id, ';') && getline(file, codeUser, ';') && getline(file, text)) {
				Message message(id, codeUser, text);
				// Add to graph
				messages->addNode(message);
				this->size++;
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
			for (int i = 0; i < this->size; i++) {
				file << messages->getVertex(i).getId() << ";" << messages->getVertex(i).getCodeUser() << ";" << messages->getVertex(i).getText() << endl;
			}
			cout << "Foro guardado" << endl;
		}
		file.close();
	}
	//agregar mensaje
	void addMessage(Student* u, string msg) {
		Message message(to_string(this->size + 1), u->getId(), "Student add: " + msg);
		messages->addNode(message);
		if (this->size > 0) {
			messages->addEdge(messages->getVertex(this->size - 1), messages->getVertex(this->size));
		}
		this->size++;
		saveForum();
	}
	void addMessageProfessor(Professor* p, string msg) {
		Message message(to_string(this->size + 1), p->getId(), "Professor add: " + msg);
		messages->addNode(message);
		if (this->size > 0) {
			messages->addEdge(messages->getVertex(this->size - 1), messages->getVertex(this->size));
		}
		this->size++;
		saveForum();
	}

	void showMesages() {
		if (this->size == 0) {
			cout << "No hay mensajes en el foro, Se el primero\n";
		}
		else
		{
			for (int i = 0; i < this->size; i++) {
				cout << messages->getVertex(i).getId() << " " << messages->getVertex(i).getCodeUser() << " " << messages->getVertex(i).getText() << endl;
			}
		}
	}
	string getforumName() {
		return forumName;
	}
};

#endif //�!_FORUM_HPP_