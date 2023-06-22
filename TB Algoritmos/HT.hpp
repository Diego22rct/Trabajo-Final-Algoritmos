#ifndef __HT_HPP__
#define __HT_HPP__
#include <string>
#include <cmath>
#include "DLL.hpp"
using namespace std;

template<class T>
class HT {
private:
    struct Element {
        string key;
        T value;
    };

    DLL<Element>** _hashTable;
    size_t _size;
    size_t _capacity;

    int _hashFunction(string& key) {
        int res = 0;
        for (unsigned int i = 0; i < key.length(); ++i)
            res += static_cast<int>(key[i]) * (i + 1);
        return res % _capacity;
    }

    unsigned long _hashFunction2(string& key) {
        unsigned long hash = 5381;
        for (unsigned int i = 0; i < key.length(); ++i) {
            hash = ((hash << 5) + hash) + key[i];
        }
        return hash % _capacity;
    }

public:
    HT(size_t capacity) : _capacity(capacity), _size(0) {
        _hashTable = new DoublyLinkedList<Element>*[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            _hashTable[i] = nullptr;
        }
    }

    void insert(string& key, T value) {
        if (_size == _capacity) throw "Hash table is full";
        int index = _hashFunction(key);
        if (_hashTable[index] == nullptr) {
            _hashTable[index] = new DoublyLinkedList<Element>();
        }
        _hashTable[index]->insertAt(Element{ key, value }, _hashTable[index]->size() / 2);
        ++_size;
    }

    T& search(string& key) {
        int index = _hashFunction(key);
        auto element = _hashTable[index]->getByCriteria([&](Element e) -> bool {
            return e.key == key;
            });
        if (element.key != key) {
            throw "Key not found";
        }
        return element.value;
    }

    T& operator[](string& key) {
        return search(key);
    }

    T getCopy(string& key) {
        return search(key);
    }

    void display(void (*show)(T)) {
        for (size_t i = 0; i < _capacity; ++i) {
            std::cout << "\nPos: " << i << ": ";
            if (_hashTable[i] == nullptr) {
                std::cout << "nullptr";
                continue;
            }
            _hashTable[i]->display([&](Element a) {
                show(a.value);
                });
        }
    }
};

#endif
