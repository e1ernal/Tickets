#ifndef SkipList_hpp
#define SkipList_hpp

#include <stdio.h>
#include <iomanip>
#include "SkipListNode.hpp"

using namespace std;

class SkipList {
    //Максимальное кол-во уровней
    int MAXLVL;
    //Вероятность доб. на след. уровень
    float P;
    //Текущий уровень
    int level;
public:
    //Указатель на начало
    Node *header;
    //Конструктор с параметрами
    SkipList(int, float);
    //Возврат случайного уровня
    int randomLevel();
    //Создание нового значения
    Node* createNode(int, int, Ticket);
    //Добавление элемента
    void insertElement(int, Ticket);
    //Удаление элемента
    void deleteElement(int, Ticket);
    //Проверка на наличие элемента
    bool contains(int);
    //Вывод списка
    void displayList();
};

#endif /* SkipList_hpp */
