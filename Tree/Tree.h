#pragma once
#include <iostream>
using namespace std;

template <class T>
class Tree;

template <class T>
class TreeNode {
    friend class Tree<T>;
    private:
        TreeNode(T s) {
            data = s;
            leftChild = 0;
            rightChild = 0;
        }
        T data;
        TreeNode<T> * leftChild;
        TreeNode<T> * rightChild;
};

template <class T>
class Tree {
    public:
    Tree(T s);
    TreeNode<T> * build();
    void Inorder();
    void Inorder(TreeNode<T> * currentNode);
    void Postorder();
    void Postorder(TreeNode<T> * currentNode);
    // void print();
    // void print(TreeNode<T> * root);
    private:
    TreeNode<T> * root;
};

template <class T>
Tree<T>::Tree(T s) {
    root = new TreeNode<T>(s);
    root->leftChild = build();
    root->rightChild = build();
}

template <class T>
TreeNode<T> * Tree<T>::build() {
    T value;
    cin >> value;
    if (value == -1) {
        return 0;
    }
    TreeNode<T> * sub;
    sub = new TreeNode<T>(value);
    sub->leftChild = build();
    sub->rightChild = build();
    return sub;
}

template <class T>
void Tree<T>::Inorder() {
    Inorder(root);
}

template <class T>
void Tree<T>::Inorder(TreeNode<T> * currentNode) {
    if (currentNode) {
        Inorder(currentNode->leftChild);
        cout << currentNode->data << " ";
        Inorder(currentNode->rightChild);
    }
}


template <class T>
void Tree<T>::Postorder() {
    Postorder(root);
}

template <class T>
void Tree<T>::Postorder(TreeNode<T> * currentNode) {
    if (currentNode) {
        Postorder(currentNode->leftChild);
        Postorder(currentNode->rightChild);
        cout << currentNode->data << " ";
    }
}

// template <class T>
// void Tree<T>::print() {
//     print(root);
// }

// template <class T>
// void Tree<T>::print(TreeNode<T> * sub) {
//     if (sub == 0) return;

//     cout << sub->data << " ";
//     print(sub->leftChild);
//     print(sub->rightChild);
// }