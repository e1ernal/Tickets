#ifndef AVLNode_hpp
#define AVLNode_hpp

#include <stdio.h>
#include <string>
#include <iomanip>
#include "Flight.hpp"

using namespace std;

struct AVLNode {
    string key;
    Flight value;
    //Высота поддерева
    int height;
    //Указатель на правое поддерево
    AVLNode *right;
    //Указатель на левое поддерево
    AVLNode *left;
    
    AVLNode(string k, Flight f);
    AVLNode();
    //Вывод значения вершины
    void outputNode(AVLNode *point);
};

#endif /* AVLNode_hpp */
