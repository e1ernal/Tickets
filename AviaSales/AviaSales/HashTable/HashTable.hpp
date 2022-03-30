#ifndef HashTable_hpp
#define HashTable_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include "HashNode.hpp"

using namespace std;

//Хэш таблица с квадратичным опробованием
class HashTable {
private:
    HashNode **data;

protected:
    int maxSize;
    HashNode *arr = nullptr;
    HashNode *resize();

public:
    int size;
    //Задать размер хэш таблицы
    HashTable(int M);
    //Деструктор
    ~HashTable();
    //Конструктор по умолчанию
    HashTable() : data(nullptr), maxSize(0), size(0){}

    //Вычисление хэш функции
    unsigned int Hash(string key, int M);
    //Добавление элемента
    void Insert(string key, Passenger value);
    //Поиск элемента по номеру паспорта
    Passenger LookupByPassNum(string key);
    //Поиск элемента по ФИО
    Passenger LookupByName(string name);
    //Удаление элемента
    void Delete(string key);
    //Просмотр всех элементов
    void Output();
    //Очистка таблицы
    void Clear();
    //Добавление номера рейса к данным пассажира
    bool addFlightToPassenger(string flightNumber, string passNumber);
    //Удаление номера рейса из данных пассажира
    bool deleteFlightFromPassenger(string flightNumber, string passNumber);
    //Запрос всех пассажиров
    vector<Passenger> getPassengers();
};
#endif /* HashTable_hpp */
