#include "IntegerArray.h"
#include <string>
#include <iostream>
#include <exception>
using namespace std;

//Конструкторы и деструкторы
IntegerArray::IntegerArray(size_t size)
{
    if (size == 0 || size > 1000) {  //ограничиваю размер 0 и 1000 элементами 4000 байт (примерно 3.91 КБ)
        throw Bad_length(); // Генерация исключения
    }
    _massRef = new int [size];
    _size = size;
}

IntegerArray::~IntegerArray()
{
    delete [] _massRef;
    cout << "IntegerArray - Удален" << endl;
}

IntegerArray::IntegerArray(const IntegerArray& other){
    _massRef = new int [other._size];
    _size = other._size;
    for (size_t i = 0; i < other._size; i++)
    {
        _massRef[i] = other._massRef[i];
    }
}

//Операторы
int& IntegerArray::operator[](size_t index) {
    if (index >= _size) { //>= тк индекс начинается с 0, а размер с 1
        throw Bad_range(); // Генерация исключения
    }
    return _massRef[index];
}

IntegerArray& IntegerArray::operator=(const IntegerArray& other){
    // Проверка на самоприсваивание (other == *this) arr = arr
    if (this != &other) {
        //Удаляем старые данные
        delete[] _massRef;

        //Копируем размер
        _size = other._size;

        //Выделяем новую память
        _massRef = new int[_size];

        //Копируем элементы
        for (size_t i = 0; i < _size; i++) {
            _massRef[i] = other._massRef[i];
        }
    }

    _massRef = new int [other._size];
    _size = other._size;
    for (size_t i = 0; i < other._size; i++)
    {
        _massRef[i] = other._massRef[i];
    }
    return *this;
}

//Методы
    //получить доступ к любому элементу контейнера по индексу
    int IntegerArray::getNumberByIndex(size_t index) const{          // может бросить bad_range
        if (index >= _size) { //>= тк индекс начинается с 0, а размер с 1
            throw Bad_range(); // Генерация исключения
        }
        return _massRef[index];
    }
    //получить размер
    size_t IntegerArray::getSize() const{
        return _size;
    }                
    //изменить размер контейнера на число
    void IntegerArray::changeSizeContainer(size_t size){            // может бросить bad_length
        if (size == 0 || size > 1000) { //ограничиваю размер 1000 элементами 4000 байт (примерно 3.91 КБ)
            throw Bad_length(); // Генерация исключения
        }
        int* temporaryPtr = new int [size]; //создаю временный массив нового размера
        if (_size < size)
        {
            //копирую все элементы старого массива строго до длинны СТАРОГО массива тк она меньше
            for (size_t i = 0; i < _size; i++)
            {
                temporaryPtr[i] = _massRef[i];
            }
            //остаток забиваю 0
            for (size_t i = _size; i < size; i++)
            {
                temporaryPtr[i] = 0;
            }
        }
        else
        {
            //копирую все элементы старого массива строго до длинны НОВОГО массива тк она меньше
            for (size_t i = 0; i < size; i++)
            {
                temporaryPtr[i] = _massRef[i];
            }
        }
        //Удаляю старый массив
        delete [] _massRef;
        //прсваиваю ссылке новый массив
        _massRef = temporaryPtr;
        //обнулять старую ссылку не надо, она выйдет из зоны видисости, стек затрет сам
        //новый размер
        _size = size;
    }                
    //изменить элемент по индексу
    void IntegerArray::replaceElement(int el, size_t index){  // может бросить bad_range
        if (index >= _size) { //>= тк индекс начинается с 0, а размер с 1
            throw Bad_range(); // Генерация исключения
        }
        _massRef[index] = el;
    }

    //вставить элемент по индексу - сдвинет все вправо увеличивая размер
    void IntegerArray::elementIntoContainer(int el, size_t index){  // может бросить bad_range
        if (index >= _size) { //>= тк индекс начинается с 0, а размер с 1
            throw Bad_range(); // Генерация исключения
        }
        //Увеличиваю размер +1
        this->changeSizeContainer(_size + 1);

        //копирую все элементы старого массива c конца на ячейку вправа до index а в индекс вставляю новый элемент
        for (size_t i = _size - 1; i != index; i--)
        {
            _massRef[i] = _massRef[i-1];
            if (i == 1) //выходим так как копируем 0 элемент в 1, а в 0 нужно добавить новый только при 0 элементе 
                break;
        }
        //Записываю новый элемент
        _massRef[index] = el;
    }    
    
    //удалить элемент из контейнера по индексу
    void  IntegerArray::deleteElementOnTheContainer(size_t index){  // может бросить bad_range
        if (index >= _size) { //>= тк индекс начинается с 0, а размер с 1
            throw Bad_range(); // Генерация исключения
        }
        //если последний элемент, то можно просто сократить размер на 1
        if (index == _size -1)
        {
            this->changeSizeContainer(_size -1);
            return; //Завершаем в этом случае
        }
        
        //сдвигаем все элементы влево начиная с index +1 тк уже проверил выше на последний элемент безопасно +1
        for (size_t i = index + 1; i < _size; i++)
        {
            _massRef[i-1] = _massRef[i];
        }
        //Удаляю последний элемент
        this->changeSizeContainer(_size -1);
    }        

    //Дополнительно вставка в начало и конец и поиск в контейнере элемента по значению
    //вставить элемент в конец контейнера
    void IntegerArray::insertElementEnd(int el){
        //Увеличиваю размер на 1
        changeSizeContainer(_size + 1);
        //добавляю в конец _size - 1 так как уже новый размер _size на 1 больше после changeSizeContainer(_size + 1);
        _massRef[_size - 1] = el;
    }
    
    //вставить элемент в начало контейнера
    void IntegerArray::insertElementStart(int el){
        this->elementIntoContainer(el, 0);//вопользуюсь уже готовой функцикй
    }
    
    //поиск элемента в контейнере записывает в size_t& index - место элемента и возвращает true при успехе false при провале
    bool IntegerArray::searchingElement(size_t& index, int el){
        for (size_t i = 0; i < _size - 1; i++)
        {
            if (el == _massRef[i])
            {
                index = i;
                return true;
            }   
        }
        return false;
    }
