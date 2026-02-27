#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <typeinfo>
#include "decimal.h"
#include "bitstring.h"

using namespace std;

// Функция для демонстрации полиморфизма
void demonstratePolymorphism(Array& arr1, Array& arr2) {
    cout << "\n--- Демонстрация полиморфизма ---" << endl;
    cout << "Тип первого объекта: " << typeid(arr1).name() << endl;
    cout << "Первый массив: " << arr1 << endl;
    cout << "Тип второго объекта: " << typeid(arr2).name() << endl;
    cout << "Второй массив: " << arr2 << endl;
    
    Array result = arr1 + arr2; // Вызов виртуальной функции
    cout << "Результат сложения: " << result << endl;
}

// Функция для демонстрации принципа подстановки
void demonstrateSubstitution(Array* ptr) {
    cout << "Принцип подстановки: объект типа " << typeid(*ptr).name() 
         << " используется через указатель на Array" << endl;
    cout << "Значение: " << *ptr << endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    srand(time(nullptr));
    
    cout << "==========================================" << endl;
    cout << "  ЛАБОРАТОРНАЯ РАБОТА №2, ЗАДАНИЕ №5" << endl;
    cout << "  Классы: Decimal и BitString" << endl;
    cout << "==========================================" << endl << endl;
    
    // ========== ЧАСТЬ 1: РАБОТА С КЛАССОМ DECIMAL ==========
    cout << "┌──────────────────────────────────────┐" << endl;
    cout << "│ 1. ДЕМОНСТРАЦИЯ РАБОТЫ С КЛАССОМ DECIMAL │" << endl;
    cout << "└──────────────────────────────────────┘" << endl << endl;
    
    // 1.1 Создание объектов разными способами
    cout << "1.1. Создание объектов Decimal:" << endl;
    cout << "--------------------------------" << endl;
    
    // Конструктор по умолчанию
    Decimal d1;
    cout << "d1 (конструктор по умолчанию): " << d1 << endl;
    
    // Конструктор инициализации
    Decimal d2(5, true); // 5 разрядов, положительное
    cout << "d2 (конструктор инициализации, 5 разрядов): " << d2 << endl;
    
    // Заполнение d2 значениями
    cout << "Заполните d2 (5 цифр):" << endl;
    cin >> d2;
    cout << "d2 после ввода: " << d2 << endl;
    
    // Конструктор копирования
    Decimal d3(d2);
    cout << "d3 (копия d2): " << d3 << endl;
    
    // 1.2 Создание массива объектов
    cout << "\n1.2. Создание массива объектов Decimal:" << endl;
    cout << "----------------------------------------" << endl;
    
    const int ARRAY_SIZE = 3;
    Decimal dArray[ARRAY_SIZE];
    
    cout << "Введите " << ARRAY_SIZE << " десятичных числа:" << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << "dArray[" << i << "]: ";
        cin >> dArray[i];
    }
    
    cout << "\nМассив десятичных чисел:" << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << "dArray[" << i << "] = " << dArray[i] 
             << " (знак: " << (dArray[i].getSign() ? "+" : "-") << ")" << endl;
    }
    
    // 1.3 Демонстрация методов класса Decimal
    cout << "\n1.3. Демонстрация методов Decimal:" << endl;
    cout << "-----------------------------------" << endl;
    
    // Создание конкретных чисел
    Decimal num1(3, true);
    num1[0] = 5; num1[1] = 4; num1[2] = 3; // число 345
    cout << "num1 = " << num1 << " (должно быть 345)" << endl;
    
    Decimal num2(3, true);
    num2[0] = 7; num2[1] = 6; num2[2] = 2; // число 267
    cout << "num2 = " << num2 << " (должно быть 267)" << endl;
    
    // Проверка знака
    cout << "Знак num1: " << (num1.getSign() ? "+" : "-") << endl;
    
    // Изменение знака
    num1.(false);
    cout << "num1 после изменения знака на отрицательный: " << num1 << endl;
    
    // Сложение чисел
    Decimal sum = num1.add(num2);
    cout << "Сумма num1 + num2 = " << sum << endl;
    
    // Проверка нормализации (удаление ведущих нулей)
    Decimal num3(5, true);
    num3[0] = 0; num3[1] = 0; num3[2] = 1; num3[3] = 2; num3[4] = 3; // 32100
    cout << "num3 до нормализации: " << num3 << " (размер: " << num3.getSize() << ")" << endl;
    num3.normalize();
    cout << "num3 после нормализации: " << num3 << " (размер: " << num3.getSize() << ")" << endl;
    
    // Преобразование в строку
    cout << "num1 как строка: " << num1.toString() << endl;
    
    // ========== ЧАСТЬ 2: РАБОТА С КЛАССОМ BITSTRING ==========
    cout << "\n┌──────────────────────────────────────────┐" << endl;
    cout << "│ 2. ДЕМОНСТРАЦИЯ РАБОТЫ С КЛАССОМ BITSTRING │" << endl;
    cout << "└──────────────────────────────────────────┘" << endl << endl;
    
    // 2.1 Создание объектов разными способами
    cout << "2.1. Создание объектов BitString:" << endl;
    cout << "----------------------------------" << endl;
    
    // Конструктор по умолчанию
    BitString bs1;
    cout << "bs1 (конструктор по умолчанию): " << bs1 << endl;
    
    // Конструктор инициализации
    BitString bs2(8, 0); // 8 бит, все нули
    cout << "bs2 (конструктор инициализации, 8 бит): " << bs2 << endl;
    
    // Ввод битовой строки
    cout << "Введите битовую строку для bs2 (например, 10110010): ";
    cin >> bs2;
    cout << "bs2 после ввода: " << bs2 << endl;
    
    // Конструктор копирования
    BitString bs3(bs2);
    cout << "bs3 (копия bs2): " << bs3 << endl;
    
    // Проверка валидности
    cout << "bs2 валидна? " << (bs2.isValid() ? "Да" : "Нет") << endl;
    
    // 2.2 Создание массива объектов
    cout << "\n2.2. Создание массива объектов BitString:" << endl;
    cout << "------------------------------------------" << endl;
    
    BitString bsArray[ARRAY_SIZE];
    
    cout << "Введите " << ARRAY_SIZE << " битовых строки:" << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << "bsArray[" << i << "]: ";
        cin >> bsArray[i];
    }
    
    cout << "\nМассив битовых строк:" << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << "bsArray[" << i << "] = " << bsArray[i] << endl;
    }
    
    // 2.3 Демонстрация методов класса BitString
    cout << "\n2.3. Демонстрация методов BitString:" << endl;
    cout << "-------------------------------------" << endl;
    
    // Создание конкретных битовых строк
    BitString bs4(4);
    bs4[0] = 1; bs4[1] = 0; bs4[2] = 1; bs4[3] = 1; // 1101
    cout << "bs4 = " << bs4 << " (должно быть 1101)" << endl;
    
    BitString bs5(4);
    bs5[0] = 1; bs5[1] = 1; bs5[2] = 0; bs5[3] = 1; // 1011
    cout << "bs5 = " << bs5 << " (должно быть 1011)" << endl;
    
    // Побитовые операции
    BitString and_res = bs4.bitwiseAnd(bs5);
    BitString or_res = bs4.bitwiseOr(bs5);
    BitString xor_res = bs4.bitwiseXor(bs5);
    
    cout << "bs4 AND bs5 = " << and_res << endl;
    cout << "bs4 OR bs5 = " << or_res << endl;
    cout << "bs4 XOR bs5 = " << xor_res << endl;
    
    // Преобразование в строку
    cout << "bs4 как строка: " << bs4.toString() << endl;
    
    // ========== ЧАСТЬ 3: ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА ==========
    cout << "\n┌─────────────────────────────────────┐" << endl;
    cout << "│ 3. ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА │" << endl;
    cout << "└─────────────────────────────────────┘" << endl << endl;
    
    // 3.1 Вызов виртуальной функции через разные типы
    cout << "3.1. Вызов виртуальной функции operator+:" << endl;
    cout << "----------------------------------------" << endl;
    
    // Создаем указатели на базовый класс
    Array* ptr1 = &d2;
    Array* ptr2 = &bs2;
    
    cout << "Через указатель на Array (ptr1 указывает на Decimal):" << endl;
    cout << "*ptr1 = " << *ptr1 << endl;
    
    cout << "Через указатель на Array (ptr2 указывает на BitString):" << endl;
    cout << "*ptr2 = " << *ptr2 << endl;
    
    // Демонстрация полиморфного поведения
    cout << "\nВызов виртуальной функции через указатели:" << endl;
    Array result1 = *ptr1 + *ptr1; // Сложение двух Decimal
    cout << "ptr1 + ptr1 = " << result1 << endl;
    
    Array result2 = *ptr2 + *ptr2; // Сложение двух BitString
    cout << "ptr2 + ptr2 = " << result2 << endl;
    
    // 3.2 Демонстрация полиморфизма через функцию
    cout << "\n3.2. Демонстрация полиморфизма через функцию:" << endl;
    cout << "----------------------------------------------" << endl;
    
    demonstratePolymorphism(d2, num1); // Два Decimal
    demonstratePolymorphism(bs2, bs4); // Два BitString
    demonstratePolymorphism(d2, bs2);   // Decimal + BitString (разные типы)
    
    // ========== ЧАСТЬ 4: ПРИНЦИП ПОДСТАНОВКИ ==========
    cout << "\n┌─────────────────────────────────────┐" << endl;
    cout << "│ 4. ПРИНЦИП ПОДСТАНОВКИ │" << endl;
    cout << "└─────────────────────────────────────┘" << endl << endl;
    
    // 4.1 Присваивание объекта производного класса базовому
    cout << "4.1. Присваивание производного класса базовому:" << endl;
    cout << "------------------------------------------------" << endl;
    
    Array baseArray = d2; // Принцип подстановки: Decimal -> Array
    cout << "baseArray (Array) после присваивания d2 (Decimal): " << baseArray << endl;
    cout << "Произошла срезка (утеряна информация о знаке)" << endl;
    
    // 4.2 Использование через указатели
    cout << "\n4.2. Использование через указатели:" << endl;
    cout << "------------------------------------" << endl;
    
    Array* pointers[] = { &d2, &bs2, &num1, &bs4 };
    for (int i = 0; i < 4; i++) {
        cout << "Элемент " << i << ": тип " << typeid(*pointers[i]).name() 
             << ", значение: " << *pointers[i] << endl;
    }
    
    // 4.3 Передача в функцию
    cout << "\n4.3. Передача в функцию:" << endl;
    cout << "------------------------" << endl;
    
    demonstrateSubstitution(&d2);  // Передаем Decimal
    demonstrateSubstitution(&bs2); // Передаем BitString
    
    // ========== ЧАСТЬ 5: ДИНАМИЧЕСКОЕ СОЗДАНИЕ ОБЪЕКТОВ ==========
    cout << "\n┌─────────────────────────────────────────┐" << endl;
    cout << "│ 5. ДИНАМИЧЕСКОЕ СОЗДАНИЕ ОБЪЕКТОВ │" << endl;
    cout << "└─────────────────────────────────────────┘" << endl << endl;
    
    // 5.1 Создание через new
    cout << "5.1. Создание объектов через new:" << endl;
    cout << "---------------------------------" << endl;
    
    Array* dynamicPtr1 = new Decimal(4, true);
    Array* dynamicPtr2 = new BitString(6, 0);
    
    cout << "dynamicPtr1 (Decimal): " << *dynamicPtr1 << endl;
    cout << "dynamicPtr2 (BitString): " << *dynamicPtr2 << endl;
    
    // Заполнение динамических объектов
    cout << "Введите значение для dynamicPtr1 (десятичное число): ";
    cin >> *dynamicPtr1;
    cout << "Введите значение для dynamicPtr2 (битовую строку): ";
    cin >> *dynamicPtr2;
    
    cout << "После ввода:" << endl;
    cout << "dynamicPtr1: " << *dynamicPtr1 << endl;
    cout << "dynamicPtr2: " << *dynamicPtr2 << endl;
    
    // 5.2 Создание массива указателей
    cout << "\n5.2. Массив указателей на базовый класс:" << endl;
    cout << "----------------------------------------" << endl;
    
    const int PTR_ARRAY_SIZE = 4;
    Array* ptrArray[PTR_ARRAY_SIZE];
    
    ptrArray[0] = new Decimal(3, true);
    ptrArray[1] = new BitString(4, 0);
    ptrArray[2] = new Decimal(2, false);
    ptrArray[3] = new BitString(5, 1);
    
    // Заполнение значений
    cout << "Введите значения для массива указателей:" << endl;
    for (int i = 0; i < PTR_ARRAY_SIZE; i++) {
        cout << "Элемент " << i << " (тип " << typeid(*ptrArray[i]).name() << "): ";
        cin >> *ptrArray[i];
    }
    
    cout << "\nСодержимое массива указателей:" << endl;
    for (int i = 0; i < PTR_ARRAY_SIZE; i++) {
        cout << "ptrArray[" << i << "] = " << *ptrArray[i] << endl;
    }
    
    // 5.3 Очистка динамической памяти
    cout << "\n5.3. Освобождение динамической памяти:" << endl;
    cout << "--------------------------------------" << endl;
    
    delete dynamicPtr1;
    delete dynamicPtr2;
    
    for (int i = 0; i < PTR_ARRAY_SIZE; i++) {
        delete ptrArray[i];
    }
    
    cout << "Память успешно освобождена" << endl;
    
    cin.get();
    cin.get();
    
    return 0;
}
