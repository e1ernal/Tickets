#ifndef SkipListNode_hpp
#define SkipListNode_hpp

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Ticket.hpp"

class Node {
public:
    int key;
    Ticket value;
    //Указатель на след. элемент
    Node **forward;
    //Вершина
    Node(int key, int level, Ticket ticket);
};

#endif /* SkipListNode_hpp */
