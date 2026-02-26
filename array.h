#pragma once
#include <iostream>
using namespace std;

class Array {
protected:
    static const int MAX_SIZE = 100;
    unsigned char* data;
    int size;

public:
    Array();
    Array(int n, unsigned char value = 0);
    Array(const Array& other);
    virtual ~Array();

    int getSize() const { return size; }
    
    // Оператор индексирования с проверкой
    unsigned char& operator[](int index);
    const unsigned char& operator[](int index) const;
    
    // Виртуальная функция поэлементного сложения
    virtual Array operator+(const Array& other) const;
    
    // Операторы ввода/вывода
    friend ostream& operator<<(ostream& out, const Array& arr);
    friend istream& operator>>(istream& in, Array& arr);
    
    // Оператор присваивания
    Array& operator=(const Array& other);
};