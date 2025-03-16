#pragma once
#include <string>
#include <exception>
using namespace std;

//исключение выход за приделы массива
class Bad_range : public exception
{
public:
    Bad_range() = default;
    ~Bad_range() = default;
    const char* what() const noexcept override{
        return "Index out of range"; //Выход за пределы массива - пишу на английском чтобы избежать проблем с кодировками 
        //хотя кодировка Windows-1251 может использовать русские симолы в 1 байт -> 0-127 - соответствует ASCII -> 128-255 - содержит кириллицу
    }
};

//исключение не верное значение размера массива
class Bad_length : public exception
{
public:
    Bad_length() = default;
    ~Bad_length() = default;
    const char* what() const noexcept override{
        return "Invalid container length"; //Не верное значение размера массива- пишу на английском чтобы избежать проблем с кодировками 
        //хотя кодировка Windows-1251 может использовать русские симолы в 1 байт -> 0-127 - соответствует ASCII -> 128-255 - содержит кириллицу
    }
};

class IntegerArray
{
private:
    size_t _size;       //длинна массива
    int* _massRef;      //Указатель на массив
public:
    //Конструкторы и деструкторы
    //IntegerArray() = default; делаю обязательным указание длинны при создании
    explicit IntegerArray(size_t size); //explicit - избежать случайных неявных преобразований числа
    /*
    Зачам? Без explicit могут возникуть проблемы с неяным преобразованием передаваемого значения в объект IntegerArray
    при помощи explicit я прошу компилятор использовать только явное преобразование для безопасности использования IntegerArray
    */
    ~IntegerArray();
    IntegerArray(const IntegerArray& other);

    //Операторы
    IntegerArray& operator=(const IntegerArray& other);
    int& operator[](size_t index);                          // может бросить bad_range
    /*
    Использование:abortIntegerArray arr(5);
    arr[2] = 42;  // Запись
    int x = arr[3]; // Чтение
    */

    //Методы
    //получить доступ к любому элементу контейнера по индексу
    int getNumberByIndex(size_t index) const;                // может бросить bad_range
    //получить размер
    size_t getSize() const;
    //изменить размер контейнера на число
    void changeSizeContainer(size_t size);                  // может бросить bad_length
    //вставить элемент по индексу - сдвинет все вправо увеличивая размер
    void elementIntoContainer(int el, size_t index);        // может бросить bad_range
    //удалить элемент из контейнера по индексу
    void  deleteElementOnTheContainer(size_t index);        // может бросить bad_range
    //изменить элемент по индексу
    void replaceElement(int el, size_t index);              // может бросить bad_range

    //Дополнительно вставка в начало и конец и поиск в контейнере элемента по значению
    //вставить элемент в конец контейнера
    void insertElementEnd(int el);
    //вставить элемент в начало контейнера
    void insertElementStart(int el);
    //поиск элемента в контейнере записывает в size_t& index место элемента и возвращает true при успехе false при провале int el искомый
    bool searchingElement(size_t& index, int el);

};


