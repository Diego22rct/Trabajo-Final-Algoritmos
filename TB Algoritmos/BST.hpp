#ifndef __BST_HPP__
#define __BST_HPP_
#include <functional>
using namespace std;

template<class T>
class BST {
private:
    struct Node {
        T value;
        Node* leftChild;
        Node* rightChild;
    };

    Node* _root;
    size_t _size;
    function<void(T)> _show;
    function<bool(T, T)> _compare;
    function<bool(T, T)> _equals;

    void _insert(Node*& n, T value) {
        if (n == nullptr) {
            n = new Node{ value, nullptr, nullptr };
            return;
        }
        if (_equals(n->value, value)) return;
        if (_compare(n->value, value)) _insert(n->leftChild, value);
        else _insert(n->rightChild, value);
    }

    void _preOrder(Node* n) {
        if (!n) return;
        _show(n->value);
        _preOrder(n->leftChild);
        _preOrder(n->rightChild);
    }

    void _road(Node* n, function<void(T)> countInRange) {
        if (!n) return;
        countInRange(n->value);
        _road(n->leftChild, countInRange);
        _road(n->rightChild, countInRange);
    }

public:
    BST(function<void(T)> show, function<bool(T, T)> compare, function<bool(T, T)> equals) : _show(show), _compare(compare), _equals(equals) {
        _root = nullptr;
        _size = 0;
    }

    void insert(T value) {
        _insert(_root, value);
    }

    void preOrder() {
        _preOrder(_root);
    }

    T max() {
        Node* aux = _root;
        while (aux->rightChild != nullptr) aux = aux->rightChild;
        return aux->value;
    }

    T min() {
        Node* aux = _root;
        while (aux->leftChild != nullptr) aux = aux->leftChild;
        return aux->value;
    }

    void roadTree(function<void(T)> countInRange) {
        _road(_root, countInRange);
    }
};

#endif
