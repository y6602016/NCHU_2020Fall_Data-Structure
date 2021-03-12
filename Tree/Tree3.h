#pragma once
#include <iostream>
using namespace std;

template <class T>
class Tree3;

template <class T>
class TreeNode3 {
    friend class Tree3<T>;
    public:
        TreeNode3(T s) {
            data = s;
            leftChild = 0;
            rightChild = 0;
        }
    private:
        T data;
        TreeNode3<T> * leftChild;
        TreeNode3<T> * rightChild;
        bool leftThread;
        bool rightThread;
        TreeNode3() {
            leftChild = 0;
            rightChild = 0;
        }
};

template <class T>
class Tree3 {
    public:
        Tree3(T s);
        void inOrder(); 
        void InsertRight(TreeNode3<T> * s , TreeNode3<T> * t);
        TreeNode3<T> * getNode();
    private:
        TreeNode3<T> * head;
        TreeNode3<T> * root;
        TreeNode3<T> * preThread;
        TreeNode3<T> * build();
        void inOrder(TreeNode3<T> * currentNode);
        void createThread(TreeNode3<T> * currentNode);
        void mostRightThread(TreeNode3<T> * currentNode);
};

template <class T>
Tree3<T>::Tree3(T s) {
    head = new TreeNode3<T>();
    head->leftThread = false;
    head->rightThread = false;
    head->rightChild = 0;
    preThread = head;
    root = new TreeNode3<T>(s);
    head->leftThread = root;
    root->leftChild = build();
    root->rightChild = build();
    createThread(root);
    mostRightThread(root);
}

template <class T>
TreeNode3<T> * Tree3<T>::build() {
    T value;
    cin >> value;
    if (value == -1) {
        return 0;
    }
    TreeNode3<T> * sub = new TreeNode3<T>(value);
    sub->leftChild = build();
    sub->rightChild = build();
    return sub;
}

template <class T>
void Tree3<T>::inOrder() {
    inOrder(root);
}

template <class T>
void Tree3<T>::inOrder(TreeNode3<T> * currentNode) {
    while (currentNode->leftChild != head) {
        currentNode = currentNode->leftChild;
    }
    while (currentNode != head) {
        TreeNode3<T> * temp = currentNode->rightChild;
        if (!currentNode->rightThread) {
            while (!temp->leftThread) {
                temp = temp->leftChild;
            }
        }  
        cout << currentNode->data << " ";
        currentNode = temp;
    }

}

template <class T>
void Tree3<T>::createThread(TreeNode3<T> * currentNode) {
    if (currentNode) {
        createThread(currentNode->leftChild);
        //====
        if (currentNode->leftChild == 0) {
            currentNode->leftThread = true;
            if (preThread == head) {
            currentNode->leftChild = head;
            }
            currentNode->leftChild = preThread;
        }
        if ((preThread->rightChild == 0) && (preThread != head)) {
            preThread->rightThread = true;
            preThread->rightChild = currentNode;
        }
        preThread = currentNode;
        //====
        createThread(currentNode->rightChild);
    }
}

template<class T>
void Tree3<T>::mostRightThread(TreeNode3<T> * currentNode){
    while (currentNode->rightChild != 0) {
        currentNode = currentNode->rightChild;
    }
    currentNode->rightThread = true;
    currentNode->rightChild = head;
}

template <class T>
void Tree3<T>::InsertRight(TreeNode3<T> * s , TreeNode3<T> * r) {
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;
    r->leftChild = s;
    r->leftThread = true;
    s->rightChild = r;
    s->rightThread = false;
    if (!r->rightThread) {
        TreeNode3<T> * temp = r->rightChild;
        while (!temp->leftThread) {
            temp = temp->leftChild;
        }
        temp->leftChild = r;
    }
}

template <class T>
TreeNode3<T> * Tree3<T>::getNode() {
    return root->leftChild->rightChild;
}