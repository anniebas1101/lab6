#include "bitstring.h"
#include <sstream>
#include <algorithm>

BitString::BitString() : Array() {}

BitString::BitString(int n, unsigned char value) : Array(n, value) {
    if (!isValid()) {
        cout << "Ошибка: битовая строка может содержать только 0 или 1!" << endl;
        exit(1);
    }
}

BitString::BitString(const BitString& other) : Array(other) {}

BitString::~BitString() {
}

bool BitString::isValid() const {
    for (int i = 0; i < size; i++) {
        if (data[i] != 0 && data[i] != 1) {
            return false;
        }
    }
    return true;
}

string BitString::toString() const {
    stringstream ss;
    for (int i = size - 1; i >= 0; i--) {
        ss << (int)data[i];
    }
    return ss.str();
}

Array BitString::operator+(const Array& other) const {
    // Проверяем, что other действительно BitString
    const BitString* bsOther = dynamic_cast<const BitString*>(&other);
    if (bsOther) {
        // Для битовых строк сложение - это побитовое ИЛИ
        return bitwiseOr(*bsOther);
    }
    
    // Если не BitString, используем базовую реализацию
    return Array::operator+(other);
}

BitString BitString::bitwiseAnd(const BitString& other) const {
    int maxSize = max(size, other.size);
    BitString result(maxSize, 0);
    
    for (int i = 0; i < maxSize; i++) {
        unsigned char bit1 = (i < size) ? data[i] : 0;
        unsigned char bit2 = (i < other.size) ? other.data[i] : 0;
        result.data[i] = bit1 & bit2;
    }
    
    return result;
}

BitString BitString::bitwiseOr(const BitString& other) const {
    int maxSize = max(size, other.size);
    BitString result(maxSize, 0);
    
    for (int i = 0; i < maxSize; i++) {
        unsigned char bit1 = (i < size) ? data[i] : 0;
        unsigned char bit2 = (i < other.size) ? other.data[i] : 0;
        result.data[i] = bit1 | bit2;
    }
    
    return result;
}

BitString BitString::bitwiseXor(const BitString& other) const {
    int maxSize = max(size, other.size);
    BitString result(maxSize, 0);
    
    for (int i = 0; i < maxSize; i++) {
        unsigned char bit1 = (i < size) ? data[i] : 0;
        unsigned char bit2 = (i < other.size) ? other.data[i] : 0;
        result.data[i] = bit1 ^ bit2;
    }
    
    return result;
}

ostream& operator<<(ostream& out, const BitString& bs) {
    out << bs.toString();
    return out;
}

istream& operator>>(istream& in, BitString& bs) {
    string input;
    in >> input;
    
    // Проверяем, что все символы - 0 или 1
    for (char c : input) {
        if (c != '0' && c != '1') {
            cout << "Ошибка: битовая строка может содержать только 0 и 1!" << endl;
            exit(1);
        }
    }
    
    // Создаем массив битов (младший бит - в нулевом индексе)
    bs.size = input.length();
    delete[] bs.data;
    bs.data = new unsigned char[bs.size];
    
    for (int i = 0; i < bs.size; i++) {
        bs.data[i] = input[bs.size - 1 - i] - '0';
    }
    
    return in;
}