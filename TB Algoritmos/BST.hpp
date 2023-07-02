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
        Node* aux = _root; // 1
        Node* succesor = nullptr; // 1
        while (aux) { // n(+1 Max INTERNO) -> n(5)
            if (_equals(aux->value, value)) // 1
                break; // 1
            if (_compare(aux->value, value)) { // 1
                succesor = aux; // 1
                aux = aux->leftChild; // 2
            }
            else
                aux = aux->rightChild; // 1 + 1
        }
        if (aux == nullptr) throw "Value does not exists in this tree"; // 2
        if (aux->rightChild != nullptr) { // 1 -> 1 +2 +n(3) +1
            Node* currentNode = aux->rightChild; // 2
            while (currentNode->leftChild != nullptr) // n(1+ Max INTERNO) -> n(3)
                currentNode = currentNode->leftChild; // 2
            return currentNode->value; // 1
        }
        if (succesor == nullptr) { // 1
            return T(); // 1
        }
        return succesor->value; // 1
    }
    //findSuccessor 
    //1 + +1 +n5 +2 + 1 +2 +n(1 + 2) +1 + 2 +1
    //9+8n -> O(n)

    T findPreviousNode(T value) {
        Node* aux = _root; // 1
        Node* prev = nullptr; // 1
        while (aux) { // n(+1 Max Interno) -> n(1 + 2 +3)
            if (_equals(aux->value, value)) // 1
                break; // 1
            if (_compare(aux->value, value)) // 1 -> 3
                aux = aux->leftChild; // 2
            else { // sum ->3
                prev = aux; // 1
                aux = aux->rightChild; // 2
            }
        }
        if (aux == nullptr) throw "Value does not exists in this tree"; // 1
        if (aux->leftChild) { // 1
            Node* currentNode = aux->leftChild; // 2
            while (currentNode->rightChild != nullptr)  // n(1 + Max INTERNO) -> n(3)
                currentNode = currentNode->rightChild; // 2
            return currentNode->value; // 1
        }
        if (prev == nullptr) { // 1
            return T(); // 1
        }
        return prev->value; // 1
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
        if (node == nullptr) throw "Value does not exists in this tree";
		if (_equals(node->value, value)) return node->value;
		if (_compare(node->value, value)) return _find(node->leftChild, value);
		return _find(node->rightChild, value);
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