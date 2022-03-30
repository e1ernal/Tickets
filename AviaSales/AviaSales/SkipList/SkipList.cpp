#include "SkipList.hpp"

SkipList::SkipList(int MAXLVL, float P) {
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;

    header = new Node(-1, MAXLVL, Ticket());
};

int SkipList::randomLevel() {
    float r = (float)rand() / RAND_MAX;
    int lvl = 0;
    while (r < P && lvl < MAXLVL) {
        lvl++;
        r = (float)rand()/RAND_MAX;
    }
    return lvl;
};

Node* SkipList::createNode(int key, int level, Ticket ticket) {
    Node *n = new Node(key, level, ticket);
    return n;
};

void SkipList::insertElement(int key, Ticket ticket) {
    Node *current = header;

    //Создание и инициализация нового массива
    Node *update[MAXLVL + 1];
    memset(update, 0, sizeof(Node*)*(MAXLVL + 1));
    
    //Начинаем с самого высокого уровня и двигаемся вперед пока ключ больше
    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    //Достигли нуля и перемещаем указатель вправо,
    //который будет точкой вставки
    current = current->forward[0];

    if (current == NULL || current->key != key) {
        int rlevel = randomLevel();

        if (rlevel > level) {
            for (int i = level + 1; i < rlevel + 1; i++)
                update[i] = header;
            level = rlevel;
        }

        Node* n = createNode(key, rlevel, ticket);

        //Вставка элемента
        for (int i = 0; i <= rlevel; i++) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        cout << "Билет № " << key << " сохранен.\n";
    }
};

void SkipList::displayList() {
    cout << "\n*****Skip List*****" << "\n";
    for (int i = 0; i <= level; i++) {
        Node *node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL) {
            cout << node->key << " ";
            node = node->forward[i];
        }
        cout << "\n";
    }
};

void SkipList::deleteElement(int key, Ticket ticket) {
    Node *x = header;
    Node *update[MAXLVL + 1];
    memset (update, 0, sizeof(Node*) * (MAXLVL + 1));
    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
    if (x->key == key) {
        for (int i = 0; i <= level; i++) {
            if (update[i]->forward[i] != x) break;
            update[i]->forward[i] = x->forward[i];
        }
        cout << "Билет № " << x->value.getTiketNumberInt() << " удален.\n";
        delete x;
        while (level > 0 && header->forward[level] == NULL) level--;
        
    }
}

bool SkipList::contains(int key) {
    Node *x = header;
    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && x->forward[i]->key < key) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    return x != NULL && x->key == key;
}
