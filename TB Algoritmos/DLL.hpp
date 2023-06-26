#ifndef __DLL_HPP__
#define __DLL_HPP__
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

template <class T>
class DLL {
private:
    struct Node{
        T value;
        Node* next;
        Node* back;
        Node(T value) : value(value), next(nullptr), back(nullptr) {}
    };
    Node* _start;
    Node* _end;
    size_t _size;
    function<void(T)> _show;

public:
    DLL() {
        this->_start = this->_end = nullptr;
        this->_size = 0;
    }

    void pushFront(T value) {
        Node* newNode = new Node(value);
        if (_size == 0) {
            this->_start = this->_end = newNode;
            this->_size = 1;
            return;
        }
        newNode->next = this->_start;
        this->_start->back = newNode;
        this->_start = this->_start->back;
        ++this->_size;
    }

    void pushBack(T value) {
        Node* newNode = new Node(value);
        if (_size == 0) {
            this->_start = this->_end = newNode;
            _size = 1;
            return;
        }
        this->_end->next = newNode;
        newNode->back = this->_end;
        this->_end = this->_end->next;
        ++_size;
    }

    void insertAt(T value, int pos) {
        if (pos < 0 || pos > _size) throw "Invalid position >:V";
        if (pos == 0) { pushFront(value); return; }
        if (pos == _size) { pushBack(value); return; }
        Node* aux = this->_start;
        Node* newNode = new Node(value);
        for (int i = 0; i < pos - 1; ++i) aux = aux->next;
        newNode->next = aux->next;
        aux->next->back = newNode;
        aux->next = newNode;
        newNode->back = aux;

        ++this->_size;
    }

    void display(function<void(T)> show) {
        Node* aux = this->_start;
        while (aux) {
            show(aux->value);
            aux = aux->next;
        }
    }

    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    void popBack() {
        if (this->_size == 0) throw "Cannot erase in empty list"; // 1
        if (this->_size == 1) { // 1 + 2 +1 +1 -> 5 
            delete _start; // 1
            _start = _end = nullptr;// 2
            _size = 0; // 1
            return; // 1
        }
        _end = _end->back; // 2
        _end->next->back = nullptr; // 3
        delete _end->next; // 1
        _end->next = nullptr; // 2
        --_size; // 2
    }// 1 + 5 + 2 + 3 + 1 +2 = 14

    void popFront() {
        if (this->_size == 0) return;
        if (this->_size == 1) {
            delete _start;
            _start = _end = nullptr;
            _size = 0;
            return;
        }
        _start = _start->next;
        _start->back->next = nullptr;
        delete _start->back;
        _start->back = nullptr;
        --_size;
    }

    void forEach(function<void(T)> f) {
        Node* aux = _start;
        while (aux != nullptr) {
            f(aux->value);
            aux = aux->next;
        }
    }

    void findAndApply(function<bool(T)> findCriteria, function<void(T)> action) {
        Node* aux = _start; // 1
        while (aux != nullptr) { // n(1 MaxInterno) ->  n(1+ 3 + 2)
            if (findCriteria(aux->value)) { // 1 -> 3
                action(aux->value); // 1
                return; // 1
            }
            aux = aux->next; // 2
        }
        cout << "Element not found in the list" << endl; // 2
    }
    // findAndApply 
    // 1+n(6)+2
    // O(n)
    void popAllElementsIf(function<bool(T)> comparacion) {
        Node* currentNode = _start;
        Node* previousNode = nullptr;

        while (currentNode != nullptr) {
            Node* nextNode = currentNode->next;
            if (comparacion(currentNode->value)) {
                if (previousNode == nullptr) {
                    _start = nextNode;
                }
                else {
                    previousNode->next = nextNode;
                }

                if (nextNode != nullptr) {
                    nextNode->back = previousNode;
                }

                if (currentNode == _end) {
                    _end = previousNode;
                }

                --_size;
                delete currentNode;
            }
            else {
                previousNode = currentNode;
            }

            currentNode = nextNode;
        }
    }

    bool popElementIf(function<bool(T)> comparacion) {
        Node* currentNode = _start;
        Node* previousNode = nullptr;

        while (currentNode != nullptr) {
            if (comparacion(currentNode->value)) {
                Node* nextNode = currentNode->next;

                if (previousNode == nullptr) {
                    _start = nextNode;
                }
                else {
                    previousNode->next = nextNode;
                }

                if (nextNode != nullptr) {
                    nextNode->back = previousNode;
                }

                if (currentNode == _end) {
                    _end = previousNode;
                }

                --_size;
                delete currentNode;

                return true;
            }
            else {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
        }

        return false;
    }

    void eraseAt(int pos) {
        if (pos < 0 || pos >= _size) return; // 1 + 1 + 1 +1
        if (pos == 0) { // 1
            popFront(); // (14)
            return; // 1
        }
        if (pos == _size - 1) { // 1 + 1
            popBack();  // (14)
            return; // 1
        }
        Node* aux = _start; // 1
        for (unsigned int i = 0; i < pos - 1; ++i) aux = aux->next; // n(2+ 2 + 2) -> n(6)
        Node* toErase = aux->next; // 2

        aux->next = aux->next->next; // 4
        aux->next->back = aux->next->back->back; // 6

        toErase->next = toErase->back = nullptr; // 4

        delete toErase; // 1
        --_size; // 2
    }
    // eraseAt
    //4+ 16+ 17+1+n(6)+2+4+6+4+1+2 = 57 + n(6)
    //O(n)

    void modifyAt(int pos, std::function<void(T&)> modify) {
        if (pos < 0 || pos >= _size) return;
        Node* aux = _start;
        for (size_t i = 0; i < pos; ++i) aux = aux->next;
        modify(aux->value);
    }

    bool isEmpty() {
        return this->_size == 0;
    }

    size_t size() {
        return this->_size;
    }

    T getByCriteria(function<bool(T)> criteria) {
        Node* aux = this->_start;
        while (aux) {
            if (criteria(aux->value)) return aux->value;
            aux = aux->next;
        }
        return T();
    }
};
#endif
