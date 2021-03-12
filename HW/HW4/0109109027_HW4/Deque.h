#pragma once
#include <iostream>
using namespace std;

template <class T>
class Deque;

template <class T>
class Node {
    friend class Deque<T>;
    public:
        Node(T s, Node * next, Node * pre) { // default constructor
            data = s;
            right = next;
            left = pre;
        }
    private:
        T data;
        Node * right;
        Node * left;
};

template <class T>
class Deque {
    public:
        Deque(); // default constructor
        Deque(Deque & d); // deep copy constructor
        ~Deque(); // destructor
        inline bool isEmpty() {
            return ((head->right == head) && (head->left == head));
        }
        void insertFront(T s);
        void insertBack(T s);
        void deleteFront();
        void deleteBack();
        void printForward(); // print from the first node to the last node
        void printBackward(); // print from the last node to the first node
        class DequeIterator { // bidirection iterator for Deque traversing
            public:
                DequeIterator(Node<T> * startNode = 0) {
                    current = startNode;
                }

                T & operator *() const {
                    return current->data;
                }

                T * operator->() const {
                    return &current->data;
                }

                DequeIterator & operator ++() {
                    current = current->right;
                    return *this;
                }

                DequeIterator operator ++(int) {
                    DequeIterator old = *this;
                    current = current->right;
                    return old;
                }

                DequeIterator & operator --() { // -- operator if for left traversing
                    current = current->left;
                    return *this;
                }

                DequeIterator operator --(int) {
                    DequeIterator old = *this;
                    current = current->left;
                    return old;
                }

                bool operator != (const DequeIterator right) const {
                    return current != right.current;
                }

                bool operator == (const DequeIterator right) const {
                    return current == right.current;
                }
            private:
                Node<T> * current;
        };
        inline DequeIterator begin() { // return the position of the first node
            return DequeIterator(head->right);
        }
        inline DequeIterator tail() { // return the position of the last node
            return DequeIterator(head->left);
        }
        inline DequeIterator end() { // return the position of the head node, this is usually used as the condition point for while loop
            return DequeIterator(head);
        }
    private:
        Node<T> * head;
};




template <class T>
Deque<T>::Deque() {
    head = new Node<T>(0, 0, 0);
    head->right = head;
    head->left = head;
}

template <class T>
Deque<T>::Deque(Deque & d) { 
    head = new Node<T>(0, 0, 0); // deep copy constructor, create a head node 
    head->right = head;
    head->left = head;
    Deque<T>::DequeIterator start = d.begin(); // create a iterator to traverse and copy
    while (start != d.end()) {
        insertBack(*start); // copy the nodes of d to this deque
        start++;
    }
}

template <class T>
Deque<T>::~Deque() { 
    delete head; 
}

template <class T>
void Deque<T>::insertFront(T s) {
    head->right = new Node<T>(s, head->right, head);
    head->right->right->left = head->right;
}

template <class T>
void Deque<T>::insertBack(T s) {
    head->left = new Node<T>(s, head, head->left);
    head->left->left->right = head->left;
}

template <class T>
void Deque<T>::deleteFront() {
    if (isEmpty()) throw "The list is empty!";
    Node<T> * removed = head->right;
    head->right = head->right->right;
    head->right->left = head;
    delete removed;
}

template <class T>
void Deque<T>::deleteBack() {
    if (isEmpty()) throw "The list is empty!";
    Node<T> * removed = head->left;
    head->left = head->left->left;
    head->left->right = head;
    delete removed;
}

template <class T>
void Deque<T>::printForward() {
    Deque<T>::DequeIterator start = begin(); // start point is the first node, then print and traverse forward to the last node
    while (start != end()) {
        cout << *start << " ";
        start++;
    } 
    cout << endl;
}

template <class T>
void Deque<T>::printBackward() {
    Deque<T>::DequeIterator start = tail(); // start point is the last node, then print and traverse backward to the last node
    while (start != end()) {
        cout << *start << " ";
        start--;
    } 
    cout << endl;
}