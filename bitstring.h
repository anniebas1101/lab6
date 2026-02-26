#pragma once
#include "array.h"
#include <string>

class BitString : public Array {
public:
    BitString();
    BitString(int n, unsigned char value = 0);
    BitString(const BitString& other);
    virtual ~BitString();

    // Проверка корректности битовой строки
    bool isValid() const;
    
    // Преобразование в строку
    string toString() const;
    
    // Переопределение виртуальной функции сложения
    virtual Array operator+(const Array& other) const override;
    
    // Специализированные методы для битовых строк
    BitString bitwiseAnd(const BitString& other) const;
    BitString bitwiseOr(const BitString& other) const;
    BitString bitwiseXor(const BitString& other) const;
    
    // Операторы ввода/вывода
    friend ostream& operator<<(ostream& out, const BitString& bs);
    friend istream& operator>>(istream& in, BitString& bs);
};
