#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

template <class T>
class Vector
{
private:
    T* data;
    int capacity;
    int length;



public:
    Vector() {
        capacity = 10;
        length = 0;
        data = new T[capacity];
    }
    void resize() {
        capacity *= 2;
        T* temp = new T[capacity];
        for (int i = 0; i < length; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

    Vector(const Vector<T>& other) {
        capacity = other.capacity;
        length = other.length;
        data = new T[capacity];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }

    Vector<T> operator=(Vector<T>& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            length = other.length;
            data = new T[capacity];
            for (int i = 0; i < length; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (length == capacity) {
            resize();
        }
        data[length++] = value;
    }

    void pop_back() {
        if (length > 0) {
            length--;
        }
    }

    void insert(const T& value, const int& index) {
        if (length == capacity) {
            resize();
        }
        for (int i = length; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        length++;
    }

    void erase(const int& index) {
        for (int i = index; i < length - 1; i++) {
            data[i] = data[i + 1];
        }
        length--;
    }

    void clear() {
        length = 0;
    }

    T& begin() {
        return data[0];
    }

    T& end() {
        if (length > 0) {
            return data[length - 1];
        }
        // Handle empty vector case
        throw std::out_of_range("Vector is empty.");
    }

    T& operator[](const int& index) {
        return data[index];
    }

    int size() const {
        return length;
    }

    bool empty() const {
        return length == 0;
    }
};

#endif // __VECTOR_HPP__
