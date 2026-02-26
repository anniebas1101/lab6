#include "array.h"
#include <cstring>
#include <cstdlib>

Array::Array() : size(0), data(nullptr) {}

Array::Array(int n, unsigned char value) : size(n) {
    if (n < 0 || n > MAX_SIZE) {
        cout << "Ошибка: недопустимый размер массива!" << endl;
        exit(1);
    }
    
    data = new unsigned char[n];
    cout << "выделяем память array" << endl;

    for (int i = 0; i < n; i++) {
        data[i] = value;
    }
}

Array::Array(const Array& other) : size(other.size) {
    data = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

Array::~Array() {
    if (data) {
        cout << "delete data array" << endl;
        delete[] data;
        data = nullptr;
    }
}

unsigned char& Array::operator[](int index) {
    if (index < 0 || index >= size) {
        cout << "Ошибка: индекс вне диапазона!" << endl;
        exit(1);
    }
    return data[index];
}

const unsigned char& Array::operator[](int index) const {
    if (index < 0 || index >= size) {
        cout << "Ошибка: индекс вне диапазона!" << endl;
        exit(1);
    }
    return data[index];
}

Array Array::operator+(const Array& other) const {
    int maxSize = (size > other.size) ? size : other.size;
    Array result(maxSize, 0);
    
    for (int i = 0; i < maxSize; i++) {
        unsigned char val1 = (i < size) ? data[i] : 0;
        unsigned char val2 = (i < other.size) ? other.data[i] : 0;
        result[i] = val1 + val2;
    }
    
    return result;
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new unsigned char[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

ostream& operator<<(ostream& out, const Array& arr) {
    out << "[";
    for (int i = 0; i < arr.size; i++) {
        if (i > 0) out << ", ";
        out << (int)arr.data[i];
    }
    out << "]";
    return out;
}

istream& operator>>(istream& in, Array& arr) {
    cout << "Введите " << arr.size << " элементов: ";
    for (int i = 0; i < arr.size; i++) {
        int val;
        in >> val;
        if (val < 0 || val > 255) {
            cout << "Ошибка: значение должно быть от 0 до 255!" << endl;
            exit(1);
        }
        arr.data[i] = (unsigned char)val;
    }
    return in;
}