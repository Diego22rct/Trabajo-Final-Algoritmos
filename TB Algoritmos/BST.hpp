#ifndef __BST_HPP__
#define __BST_HPP__
#include <functional>
using namespace std;

template<class T>
class BST {
public:
    BST(function<void(T)> show, function<bool(T, T)> compare, function<bool(T, T)> equals) : _show(show), _compare(compare), _equals(equals) {
        _root = nullptr;
        _size = 0ll;
    }

    void insert(T value) {
        _insert(_root, value);
    }

    void preOrder() {
        _preOrder(_root);
    }

    void inOrder() {
        _inOrder(_root);
    }

    void postOrder() {
        _postOrder(_root);
    }

    void remove(T value) {
        _root = _remove(_root, value);
    }

    T find(T value) {
        return _find(_root, value);
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

    void roadTree(std::function<void(T)> countInRange) {
        _road(_root, countInRange);
    }

    T findSuccessor(T value) {
        Node* aux = _root;
        Node* succesor = nullptr;
        while (aux) {
            if (_equals(aux->value, value))
                break;
            if (_compare(aux->value, value)) {
                succesor = aux;
                aux = aux->leftChild;
            }
            else
                aux = aux->rightChild;
        }
        if (aux == nullptr) throw "Value does not exists in this tree";
        if (aux->rightChild) {
            Node* currentNode = aux->rightChild;
            while (currentNode->leftChild != nullptr) currentNode = currentNode->leftChild;
            return currentNode->value;
        }
        if (succesor == nullptr) {
            return T();
        }
        return succesor->value;
    }

    T findPreviousNode(T value) {
        Node* aux = _root;
        Node* prev = nullptr;
        while (aux) {
            if (_equals(aux->value, value))
                break;
            if (_compare(aux->value, value))
                aux = aux->leftChild;
            else {
                prev = aux;
                aux = aux->rightChild;
            }
        }
        if (aux == nullptr) throw "Value does not exists in this tree";
        if (aux->leftChild) {
            Node* currentNode = aux->leftChild;
            while (currentNode->rightChild != nullptr) currentNode = currentNode->rightChild;
            return currentNode->value;
        }
        if (prev == nullptr) {
            return T();
        }
        return prev->value;
    }
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
private:
    void _insert(Node*& n, T value) {
        if (n == nullptr) {
            n = new Node{ value, nullptr, nullptr };
            return;
        }
        if (_equals(n->value, value)) return;
        if (_compare(n->value, value)) _insert(n->leftChild, value);
        else _insert(n->rightChild, value);
    }

    T _find(Node* node, T value) {
        if (node == nullptr) {
            throw "Value does not exists in this tree";
        }
        else if (_equals(node->value, value)) {
            return node->value;
        }
        else if (_compare(value, node->value)) {
            return _find(node->leftChild, value);
        }
        else {
            return _find(node->rightChild, value);
        }
    }

    void _preOrder(Node* n) {
        if (!n) return;
        _show(n->value); 
        _preOrder(n->leftChild); 
        _preOrder(n->rightChild); 
    }

    void _inOrder(Node* node) {
        if (node == nullptr)
            return;
        _inOrder(node->leftChild);
        _show(node->value);
        _inOrder(node->rightChild);
    }

    void _postOrder(Node* node) {
        if (node == nullptr)
            return;
        _postOrder(node->leftChild);  
        _postOrder(node->rightChild); 
        _show(node->value);           
    }

    void _road(Node* n, std::function<void(T)> countInRange) {
        if (!n) return;
        countInRange(n->value);
        _road(n->leftChild, countInRange);
        _road(n->rightChild, countInRange);
    }

    Node* _remove(Node* root, T value) {
        if (root == nullptr) return root;

        if (_compare(value, root->value))
            root->leftChild = _remove(root->leftChild, value);
        else if (!_compare(root->value, value))
            root->rightChild = _remove(root->rightChild, value);
        else {
            if (root->leftChild == nullptr) {   
                Node* temp = root->rightChild;
                delete root;
                return temp;
            }
            else if (root->rightChild == nullptr) {
                Node* temp = root->leftChild;
                delete root;
                return temp;
            }

            Node* temp = _minValueNode(root->rightChild);
            root->value = temp->value;
            root->rightChild = _remove(root->rightChild, temp->value);
        }
        return root;
    }

    Node* _minValueNode(Node* node) {
        Node* current = node;
        while (current && current->leftChild != nullptr)
            current = current->leftChild;

        return current;
    }
};

#endif