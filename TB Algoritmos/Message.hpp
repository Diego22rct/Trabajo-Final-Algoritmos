#ifndef _MESSAGE_HPP
#define _MESSAGE_HPP

#include <string>
#include <iostream>

using namespace std;

class Message
{
private:
	string id;
	string codeUser;
	string text;

public:
	Message(string id = "", string codeUser = "", string text = "") : id(id), codeUser(codeUser), text(text)
	{
	}

	~Message()
	{
	}

	friend ostream& operator<<(ostream& os, const Message& message)
	{
		os << message.id << " " << message.codeUser << " " << message.text << endl;
		return os;
	}

	bool operator==(Message other)
	{
		return id == other.id;
	}
	//setters and getters
	void setId(string id) { this->id = id; }
	void setCodeUser(string codeUser) { this->codeUser = codeUser; }
	void setText(string text) { this->text = text; }

	string getId() { return id; }
	string getCodeUser() { return codeUser; }
	string getText() { return text; }

};

#endif // !_MESSAGE_HPP