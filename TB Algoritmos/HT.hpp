#ifndef __HT_HPP__
#define __HT_HPP__
#include <string>
#include <functional>
#include <cmath>
#include "DLL.hpp"
using namespace std;

template<class T>
class HT {
private:
    struct Element {
        string key;
        T value;

        Element(string key = "", T value = T{}) : key(key), value(value) { }
    };

    DLL<Element>** _hashTable;
    size_t _size;
    size_t _capacity;

    int _hashFunction(string key) {
        int res = 0;
        for (unsigned int i = 0; i < key.length(); ++i)
            res += pow(static_cast<int>(key[i]), i + 1);
        return res % _capacity;
    }

    unsigned long _hashFunction2(string key) {
        unsigned long hash = 5381;
        for (unsigned int i = 0; i < key.length(); ++i) {
            hash = ((hash << 5) + hash) + key[i];
        }
        return hash % _capacity;
    }

public:
    HT(size_t capacity) : _capacity(capacity), _size(0) {
        _hashTable = new DLL<Element>*[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            _hashTable[i] = nullptr;
        }
    }

    ~HT() {
        for (size_t i = 0; i < _capacity; ++i) {
            delete _hashTable[i];
        }
        delete[] _hashTable;
    }

    void insert(string key, T value) {
        if (_size == _capacity) throw "Hash table is full";
        int index = _hashFunction(key);
        if (_hashTable[index] == nullptr) _hashTable[index] = new DoublyLinkedList<Element>();
        int pos = _hashTable[index]->size() / 2;
        _hashTable[index]->insertAt(Element{ key,value }, pos);
        ++_size;
    }

    void forEach(function<void(T)> func) {
        for (size_t i = 0; i < _capacity; ++i) {
            if (_hashTable[i] != nullptr) {
                _hashTable[i]->forEach(func);
            }
        }
    }

    T& search(string key) {
        int index = _hashFunction(key);
        auto element = _hashTable[index]->getByCriteria([&](Element e) -> bool {
            return e.key == key;
            });
        if (element.key != key) {
            throw runtime_error("Key not found");
        }
        return element.value;
    }

    T& operator[](string key) {
        int index = _hashFunction(key);
        auto list = _hashTable[index];
        T value = _hashTable[index]->getByCriteria([&](Element e) -> bool {
            return e.key == key;
            });
        return value;
    }

    T getCopy(string key) {
        int index = _hashFunction(key);
        auto list = _hashTable[index];
        T value = _hashTable[index]->getByCriteria([&](Element e) -> bool {
            return e.key == key;
            });
        return value;
    }

    void display(void (*show)(T)) {
        for (unsigned int i = 0; i < _capacity; ++i) {
            cout << "\nPos: " << i << ": ";
            if (_hashTable[i] == nullptr) {
                cout << "nullptr";
                continue;
            }
            _hashTable[i]->display([&](Element a) -> void {
                show(a.value);
                });
        }
    }

    void display1(function<void(T&)> show) {
        for (unsigned int i = 0; i < _capacity; ++i) {
            std::cout << "\nPos: " << i << ": ";
            if (_hashTable[i] == nullptr) {
                std::cout << "nullptr";
                continue;
            }
            _hashTable[i]->display([&](Element a) -> void {
                show(a.value);
                });
        }
    }

    void remove(string key) {
        int index = _hashFunction(key);
        if (_hashTable[index] == nullptr) {
            throw runtime_error("Key not found");
        }
        else {
            bool removed = _hashTable[index]->popElementIf([&](Element e) -> bool {
                return e.key == key;
                });
            if (!removed) {
                throw runtime_error("Key not found");
            }
            else {
                --_size;
            }
        }
    }
};

#endif
