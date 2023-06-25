#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__
template <class T>
class Queue
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node(T data) : data(data), next(nullptr) {}
	};
	Node* head;
	Node* tail;
	int length;

public:
	Queue() : head(nullptr), tail(nullptr), length(0)
	{
	}

	~Queue()
	{
	}

	void enQueue(const T& value)
	{
		Node* newNode = new Node(value);
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			tail->next = newNode;
			tail = tail->next;
		}
		length++;
	}

	T deQueue()
	{
		if (head == nullptr)
		{
			throw "Queue is empty";
		}
		else
		{
			T value = head->data;
			Node* temp = head;
			head = head->next;
			delete temp;
			length--;
			return value;
		}
	}

	T front()
	{
		if (head == nullptr)
		{
			throw "Queue is empty";
		}
		else
		{
			return head->data;
		}
	}

	bool isEmpty()
	{
		return head == nullptr;
	}

	int size()
	{
		return length;
	}

	//pop
	void pop() {
		if (head == nullptr)
		{
			throw "Queue is empty";
		}
		else
		{
			Node* temp = head;
			head = head->next;
			delete temp;
			length--;
		}
	}


};


#endif // !__QUEUE_HPP__