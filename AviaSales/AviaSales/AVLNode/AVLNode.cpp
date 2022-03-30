#include "AVLNode.hpp"

AVLNode::AVLNode(string k, Flight f) {
    key = k;
    value = f;
    height = 1;
    left = right = NULL;
}

AVLNode::AVLNode() {
    string key = NULL;
    Flight value = Flight();
    height = NULL;
    right = NULL;
    left = NULL;
}

void AVLNode::outputNode(AVLNode *point) {
    if (point != NULL) {
        cout << endl;
        cout << "[KEY]: " << point->key << endl;
        cout << "[VALUE]: " << endl;
        point->value.flightOutput();
        outputNode(point->left);
        outputNode(point->right);
    }
}
