#pragma once
#include "array.h"

class Decimal : public Array {
private:
    bool sign; // true - положительное, false - отрицательное

public:
    Decimal();
    Decimal(int n, bool positive = true);
    Decimal(const Decimal& other);
    virtual ~Decimal();

    // Методы для работы со знаком
    void setSign(bool positive) { sign = positive; }
    bool getSign() const { return sign; }
    
    // Преобразование числа в строку
    string toString() const;
    
    // Переопределение виртуальной функции сложения
    virtual Array operator+(const Array& other) const override;
    
    // Специализированные методы для Decimal
    Decimal add(const Decimal& other) const;
    void normalize(); // Удаление ведущих нулей
    
    // Операторы ввода/вывода
    friend ostream& operator<<(ostream& out, const Decimal& dec);
    friend istream& operator>>(istream& in, Decimal& dec);
};