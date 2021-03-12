#pragma once
#include <iostream>
using namespace std;

class Tree2;

class TreeNode2 {
    friend class Tree2;
    private:
        char first;
        bool second;
        TreeNode2 * leftChild;
        TreeNode2 * rightChild;
        TreeNode2(char s) {
            first = s;
            second = 0;
            leftChild = 0;
            rightChild = 0;
        }
};

class Tree2 {
    public:
        Tree2(char s);
        void Postorder();
    private:
        TreeNode2 * root;
        TreeNode2 * build();
        void Postorder(TreeNode2 * currentNode);
};

Tree2::Tree2(char s) {
    root = new TreeNode2(s);
    root->leftChild = build();
    root->rightChild = build();
}

TreeNode2 * Tree2::build() {
    char t;
    cin >> t;
    if (t == '0') {
        return 0;
    }
    TreeNode2 * sub = new TreeNode2(t);
    sub->leftChild = build();
    sub->rightChild = build();
    return sub;
}

void Tree2::Postorder() {
    Postorder(root);
    if (root->second) {
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }
}

void Tree2::Postorder(TreeNode2 * currentNode) {
    if (currentNode) {
        Postorder(currentNode->leftChild);
        Postorder(currentNode->rightChild);
        switch(currentNode->first) {
            case 'N':
                currentNode->second = !currentNode->rightChild->second;
                break;
            case 'A':
                currentNode->second = currentNode->leftChild->second && currentNode->rightChild->second;
                break;
            case 'O' :
                currentNode->second = currentNode->leftChild->second || currentNode->rightChild->second;
                break;
            case 'T':
                currentNode->second = true;
                break;
            case 'F':
                currentNode->second = false;
                break;
        }
    }
}