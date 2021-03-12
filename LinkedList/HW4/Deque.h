#pragma once
#include <iostream>
using namespace std;


class Deque;

class NodeN {
    friend class Deque;
    public:
        NodeN(int s, NodeN * next, NodeN * pre) {
            data = s;
            right = next;
            left = pre;
        }
    private:
        int data;
        NodeN * right;
        NodeN * left;
};

class Deque {
    public:
        Deque() {
            head = new NodeN(0, 0, 0);
            head->right = head;
            head->left = head;
            size = 0;
        }
        bool isEmpty() {
            return ((head->right == head) && (head->left == head));
        }
        void insertFront(int s) {
            head->right = new NodeN(s, head->right, head);
            head->right->right->left = head->right;
            size ++;
        }
        void insertBack(int s) {
            head->left = new NodeN (s, head, head->left);
            head->left->left->right = head->left;
            size ++;
        }
        void deleteFront() {
            if (isEmpty()) throw "The list is empty!";
            head->right = head->right->right;
            head->right->left = head;
            size--;
        }
        void deleteBack() {
            if (isEmpty()) throw "The list is empty!";
            head->left = head->left->left;
            head->left->right = head;
            size--;
        }
        void print() {
            NodeN * k = head->right;
            for (int i = 0; i < size; i ++) {
                cout << k->data << " ";
                k = k->right;
            }
        }
    private:
        NodeN * head;
        int size;
};