#ifndef HashNode_hpp
#define HashNode_hpp

#include <stdio.h>
#include <string>
#include "Passenger.hpp"

//Ячейка ключ-значение
class HashNode {
private:
    string key;
    Passenger value;
public:
    //Конструктор по умолчанию
    HashNode();
    //Конструктор с параметрами
    HashNode(string _key, Passenger _value);
    //Проверка на пустоту ключа и значения
    bool isEmpty();
    friend class HashTable;
};

#endif /* HashNode_hpp */
