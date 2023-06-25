#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include "Vector.hpp"
#include "Queue.hpp"

template <class T>
class Graph {
private:
    struct Node {
        T data;
        Vector<Node*> adj;
        Node(T data) : data(data) {}
        T& getData() {
            return data;
        }
        bool operator==(Node other) {
			return data == other.data;
		}
    };
    Vector<Node*> nodes;
    Vector<Vector<int>> adj;
    int size;
    int capacity;
    int find(T data) {
        for (int i = 0; i < size; i++) {
            if (nodes[i]->data == data) {
                return i;
            }
        }
        return -1;
    }

public:
    Graph(int capacity = 10) : size(0), capacity(capacity) {
    }

    ~Graph() {
        for (int i = 0; i < size; i++) {
            delete nodes[i];
        }
    }

    void addNode(T data) {
        if (size == capacity) {
            return;
        }
        nodes.push_back(new Node(data));
        size++;
    }

    void addEdge(T from, T to) {
        int f = find(from);
        int t = find(to);
        if (f == -1 || t == -1) {
            return;
        }
        adj[f].resize();
        adj[f].push_back(t);
    }

    void BFS(T start) {
        int s = find(start);
        if (s == -1) {
            return;
        }
        Queue<int> q;
        bool* visited = new bool[size];
        for (int i = 0; i < size; i++) {
            visited[i] = false;
        }
        q.enQueue(s);
        visited[s] = true;
        while (!q.isEmpty()) {
            int current = q.front();
            q.deQueue();
            cout << nodes[current]->data << " ";
            for (int i = 0; i < adj[current].size(); i++) {
                int next = adj[current][i];
                if (!visited[next]) {
                    q.enQueue(next);
                    visited[next] = true;
                }
            }
        }
        delete[] visited;
    }

    T getVertex(int index) {
        return nodes[index]->data;
    }

    bool const isEmpty() {
        return size == 0;
    }
};

#endif // !__GRAPH_HPP__
