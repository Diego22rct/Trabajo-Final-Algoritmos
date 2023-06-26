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
        if (this->_size == 0) throw "Cannot erase in empty list";
        if (this->_size == 1) {
            delete _start;
            _start = _end = nullptr;
            _size = 0;
            return;
        }
        _end = _end->back;
        _end->next->back = nullptr;
        delete _end->next;
        _end->next = nullptr;
        --_size;
    }

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
        Node* aux = _start;
        while (aux != nullptr) {
            if (findCriteria(aux->value)) {
                action(aux->value);
                return;
            }
            aux = aux->next;
        }
        cout << "Element not found in the list" << endl;
    }

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
        if (pos < 0 || pos >= _size) return;
        if (pos == 0) {
            popFront();
            return;
        }
        if (pos == _size - 1) {
            popBack();
            return;
        }
        Node* aux = _start;
        for (unsigned int i = 0; i < pos - 1; ++i) aux = aux->next;
        Node* toErase = aux->next;

        aux->next = aux->next->next;
        aux->next->back = aux->next->back->back;

        toErase->next = toErase->back = nullptr;

        delete toErase;
        --_size;
    }

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
