#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ext/hash_map>
#include <iomanip>
#include "Flight.hpp"
#include "AVLNode.hpp"

using namespace std;

class AVLTree {
public:
    
    int height(AVLNode *p);
    int BF(AVLNode *p);
    void OverHeight(AVLNode *p);
    
    //Малые левый и правый повороты
    AVLNode *LeftRotation(AVLNode *y);
    AVLNode *RightRotation(AVLNode *x);

    //Балансировка дерева
    AVLNode *Balance(AVLNode *x);
    
    //Вставка и удаление
    AVLNode *Insert(AVLNode *x, string k, Flight f);
    AVLNode *Delete(AVLNode *x, string k);

    //Поиск и удаление минимального эл-та
    AVLNode *SearchMin(AVLNode *x);
    AVLNode *DeleteMin(AVLNode *x);
    
    //Вывод значений
    void output(AVLNode *x);
    //Поиск по номеру
    AVLNode *findByNumber(AVLNode *x, string k);
    //Поиск по названию аэропорта
    void findByArrivalAirport(AVLNode *x, string k, vector<AVLNode*>& v);
    vector<int> prefix_func(const string &s);
    int boyerMooreSearch(string s, string t);
    
};

#endif /* AVLTree_hpp */
