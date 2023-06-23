#ifndef _FORUM_HPP_
#define _FORUM_HPP_
#include <iostream>
#include <string>
#include <fstream>
#include "Vector.hpp"
#include "Message.hpp"

using namespace std;

class Forum
{
private:
	string forumName;
	Vector<Message> messages;
public:
	Forum(string forumName = "") : forumName(forumName)
	{
		messages = Vector<Message>();
		cout << "Leyendo foro...";
		readForum();
		cout << "Foro leido" << endl;
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
				getline(file, id, ',');
				getline(file, codeUser, ',');
				getline(file, text, '\n');
				Message message(id, codeUser, text);
				messages.push_back(message);
			}
		}
		file.close();
	}
	//guardar foro
	void saveForum() {
		//save all in the file
		ofstream file;
		file.open("Forum1.txt", ios::out, ios::ate);
		for (int i = 0; i < messages.size(); i++) {
			file << messages[i].getId() << "," << messages[i].getCodeUser() << "," << messages[i].getText() << endl;
		}
	}
	//agregar mensaje
	void addMessage(Message msg) {
		messages.push_back(msg);
		cout << msg.getCodeUser() << msg.getText() << endl;
	}

	void showMesages() {
		cout << "Foro: " << forumName << endl;

		for (int i = 0; i < messages.size(); i++) {
			cout << "ID: " + messages[i].getId() << "- User: " << messages[i].getCodeUser() << ": " << messages[i].getText() << endl;
		}
	}
	void forumApp(string codeUser) {
		showMesages();
		cout << "Escriba su mensaje: ";
		string text;
		cin >> text;
		Message msg(to_string(messages.size() + 1), codeUser, text);
	}
};

#endif // !_FORUM_HPP_