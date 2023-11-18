#include "SkipListNode.hpp"

Node::Node(int key, int level, Ticket ticket) {
    this->key = key;
    this->value = ticket;
    //Выделение памяти
    forward = new Node*[level + 1];
    //Заполнение массива нулями
    memset(forward, 0, sizeof(Node*)*(level + 1));
};
