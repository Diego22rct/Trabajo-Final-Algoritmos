#ifndef _HT_HPP_
#define _HT_HPP
#include "DLL.hpp"
#include <string>
#include <functional>
#include <cmath>

template<class T>
class HT {
public:
    HT(size_t capacity) : _capacity(capacity) {
        _size = 0;
        _hashTable = new DLL<Element>*[capacity];
        for (int i = 0; i < capacity; ++i) _hashTable[i] = nullptr;
    }

    T search(string key) {
        int index = _hashFunction(key);
        auto list = _hashTable[index];
        auto a = _hashTable[index]->getByCriteria([&](Element e) -> bool {
            return e.key == key;
            });
        return a.value;
    }

    void insert(string key, T value) {
        if (_size == _capacity) return;
        int index = _hashFunction(key);
        if (_hashTable[index] == nullptr) _hashTable[index] = new DLL<Element>();
        int pos = _hashTable[index]->size() / 2;
        _hashTable[index]->insertAt(Element{ key,value }, pos);
        ++_size;
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
private:
    struct Element {
        string key;
        T value;
    };
    DLL<Element>** _hashTable;
    size_t _size;
    size_t _capacity;
private:
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
};
#endif