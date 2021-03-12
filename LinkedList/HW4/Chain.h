#pragma once

class Chain;

class Node {
    friend class Chain;
    friend Chain Merge(Chain & x, Chain & y);
    friend Chain Merge2(Chain & x, Chain & y);
    public:
        Node(int s) {
            value = s;
            next = 0;
        }
    private:
        int value;
        Node * next;
};

class Chain {
    friend Chain Merge(Chain & x, Chain & y);
    friend Chain Merge2(Chain & x, Chain & y);
    public:
        Chain();
        Chain(int s);
        void Add(int s);
        void print();
    private:
        Node * first;
        int size;
};

