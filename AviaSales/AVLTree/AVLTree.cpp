#include "AVLTree.hpp"

using namespace std;

int AVLTree::height(AVLNode *p) {
    if (p) return p->height;
    else return 0;
}

int AVLTree::BF(AVLNode *p) {
    return height(p->right)-height(p->left);
}

void AVLTree::OverHeight(AVLNode *p) {
    char hleft=height(p->left);
    char hright=height(p->right);
    p->height=(hleft>hright ? hleft : hright)+1;
}

AVLNode* AVLTree::RightRotation(AVLNode *x) {
    AVLNode *y=x->left;
    x->left=y->right;
    y->right=x;
    OverHeight(x);
    OverHeight(y);
    return y;
}

AVLNode* AVLTree::LeftRotation(AVLNode *y) {
    AVLNode *x=y->right;
    y->right=x->left;
    x->left=y;
    OverHeight(y);
    OverHeight(x);
    return x;
}

AVLNode* AVLTree::Balance(AVLNode *x) {
    OverHeight(x);
    if (BF(x)==2)
    {
    if (BF(x->right)<0) x->right=RightRotation(x->right);
    return LeftRotation(x);
    }
    if (BF(x)==-2)
    {
    if (BF(x->left)>0) x->left=LeftRotation(x->left);
    return RightRotation(x);
    }
    return x;
}

AVLNode* AVLTree::Insert(AVLNode *x, string k, Flight f) {
    if (!x) return new AVLNode(k, f);
    if (k < x->key) x->left = Insert(x->left, k, f);
    else x->right = Insert(x->right, k, f);
    return Balance(x);
}

AVLNode* AVLTree::Delete(AVLNode *x, string k) {
    if (!x) return 0;
    if (k < x->key) x->left = Delete(x->left, k);
    else if (k > x->key) x->right = Delete(x->right, k);
    else {
        AVLNode *y = x->left;
        AVLNode *z = x->right;
        delete x;
        if (!z) return y;
        AVLNode* min = SearchMin(z);
        min->right = DeleteMin(z);
        min->left = y;
        return Balance(min);
    }
    return Balance(x);
}

AVLNode* AVLTree::SearchMin(AVLNode *x) {
    if (x->left) return SearchMin(x->left);
    else return x;
}

AVLNode* AVLTree::DeleteMin(AVLNode *x) {
    if (x->left==0) return x->right;
    x->left=DeleteMin(x->left);
    return Balance(x);
}

void AVLTree::output(AVLNode *x) {
    if (x != NULL) {
        x->outputNode(x);
        x->outputNode(x->left);
        x->outputNode(x->right);
    } else cout << "Данных об авиарейсах нет.\n";
}

AVLNode* AVLTree::findByNumber(AVLNode *x, string k) {
    if (x == NULL) {
        return NULL;
    } else {
        if (k < x->key) return findByNumber(x->left, k);
        else if (k > x->key) return findByNumber(x->right, k);
        else if (k == x->key) return x;
        else return NULL;
    }
}

vector<int> AVLTree::prefix_func(const string &s) {
    vector<int> p(s.length());

    int k = 0;
    p[0] = 0;
    for (int i = 1; i < s.length(); ++i) {
        while (k > 0 && s[k] != s[i]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            ++k;
        }
        p[i] = k;
    }
    return p;
}

int AVLTree::boyerMooreSearch(string s, string t) {
    if (s.length() < t.length()) {
        return -1;
    }

    if (!t.length()) {
        return s.length();
    }

    typedef __gnu_cxx::hash_map<char, int> TStopTable;
    typedef __gnu_cxx::hash_map<int, int> TSufficsTable;
    TStopTable stop_table;
    TSufficsTable suffics_table;

    for (int i = 0; i < t.length(); ++i) {
        stop_table[t[i]] = i;
    }

    string rt(t.rbegin(), t.rend());
    vector<int> p = prefix_func(t), pr = prefix_func(rt);
    for (int i = 0; i < t.length() + 1; ++i) {
        suffics_table[i] = t.length() - p.back();
    }

    for (int i = 1; i < t.length(); ++i) {
        int j = pr[i];
        suffics_table[j] = min(suffics_table[j], i - pr[i] + 1);
    }

    for (int shift = 0; shift <= s.length() - t.length();) {
        int pos = t.length() - 1;

        while (t[pos] == s[pos + shift]) {
            if (pos == 0) return shift;
            --pos;
        }
        
        if (pos == t.length() - 1) {
            TStopTable::const_iterator stop_symbol = stop_table.find(s[pos + shift]);
            int stop_symbol_additional = pos - (stop_symbol != stop_table.end() ? stop_symbol->second : -1);
            shift += stop_symbol_additional;
        } else {
            shift += suffics_table[t.length() - pos - 1];
        }
    }

    return -1;
}


void AVLTree::findByArrivalAirport(AVLNode *x, string k, vector<AVLNode*>& v) {
    if (x == NULL) return;
    else {
        if (boyerMooreSearch(x->value.getArrivalAirport(), k) != -1) v.push_back(x);
        findByArrivalAirport(x->left, k, v);
        findByArrivalAirport(x->right, k, v);
    }
}
