#include "decimal.h"
#include <string>
#include <sstream>
#include <algorithm>

Decimal::Decimal() : Array(), sign(true) {}

Decimal::Decimal(int n, bool positive) : Array(n, 0), sign(positive) {
    if (n > MAX_SIZE) {
        cout << "Ошибка: превышен максимальный размер!" << endl;
        exit(1);
    }
}

Decimal::Decimal(const Decimal& other) : Array(other), sign(other.sign) {}

Decimal::~Decimal() {
}

void Decimal::normalize() {
    // Удаляем ведущие нули
    int newSize = size;
    for (int i = size - 1; i > 0; i--) {
        if (data[i] == 0) {
            newSize--;
        } else {
            break;
        }
    }
    
    if (newSize != size) {
        unsigned char* newData = new unsigned char[newSize];
        for (int i = 0; i < newSize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }
    
    // Если число равно 0, знак делаем положительным
    if (size == 1 && data[0] == 0) {
        sign = true;
    }
}

string Decimal::toString() const {
    stringstream ss;
    if (!sign && !(size == 1 && data[0] == 0)) {
        ss << "-";
    }
    for (int i = size - 1; i >= 0; i--) {
        ss << (int)data[i];
    }
    return ss.str();
}

Array Decimal::operator+(const Array& other) const {
    // Проверяем, что other действительно Decimal
    const Decimal* decOther = dynamic_cast<const Decimal*>(&other);
    if (decOther) {
        return add(*decOther);
    }
    
    // Если не Decimal, используем базовую реализацию
    return Array::operator+(other);
}

Decimal Decimal::add(const Decimal& other) const {
    int maxSize = max(size, other.size) + 1; // +1 для возможного переноса
    Decimal result(maxSize, true);
    
    int carry = 0;
    for (int i = 0; i < maxSize - 1; i++) {
        int digit1 = (i < size) ? data[i] : 0;
        int digit2 = (i < other.size) ? other.data[i] : 0;
        
        int sum = digit1 + digit2 + carry;
        result.data[i] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry > 0) {
        result.data[maxSize - 1] = carry;
    } else {
        // Уменьшаем размер, если последняя цифра 0
        unsigned char* newData = new unsigned char[maxSize - 1];
        for (int i = 0; i < maxSize - 1; i++) {
            newData[i] = result.data[i];
        }
        delete[] result.data;
        result.data = newData;
        result.size = maxSize - 1;
    }
    
    result.normalize();
    return result;
}

ostream& operator<<(ostream& out, const Decimal& dec) {
    out << dec.toString();
    return out;
}

istream& operator>>(istream& in, Decimal& dec) {
    string input;
    in >> input;
    
    // Определяем знак
    if (input[0] == '-') {
        dec.sign = false;
        input = input.substr(1);
    } else {
        dec.sign = true;
    }
    
    // Проверяем, что все символы - цифры
    for (char c : input) {
        if (c < '0' || c > '9') {
            cout << "Ошибка: недопустимый символ в числе!" << endl;
            exit(1);
        }
    }
    
    // Создаем массив цифр (младшая цифра - в нулевом индексе)
    dec.size = input.length();
    delete[] dec.data;
    dec.data = new unsigned char[dec.size];
    
    for (int i = 0; i < dec.size; i++) {
        dec.data[i] = input[dec.size - 1 - i] - '0';
    }
    
    dec.normalize();
    return in;
}