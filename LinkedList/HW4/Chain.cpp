#include "Chain.h"
#include <iostream>
using namespace std;


Chain::Chain() {
    first = 0;
    size = 0;
}

Chain::Chain(int s) {
    first = new Node(s);
    size = 1;
}

void Chain::Add(int s) {
    Node * second = new Node(s);
    if (first->next == 0) {
        second->next = first;
        first = second;
    }
    else{
        second->next = first;
        first = second;
    }
    size ++;
}

void Chain::print() {
    for (Node * k = first; k!= 0; k = k->next) {
        cout << k->value << " ";
    }
}

Chain Merge(Chain & x, Chain & y) {
    Chain z;
    z.first = x.first;
    Node * last = z.first;
    while ((y.first) && (x.first)) {
        x.first = x.first->next;
        last->next = y.first;
        last = last->next;
        y.first = y.first->next;
        if (x.first) {
            last->next = x.first;
            last = last->next;
        }
    }

    while (x.first) {
        x.first = x.first->next;
        last->next = x.first;
        last = last->next;
    }

    while (y.first) {
        last->next = y.first;
        last = last->next;
        y.first = y.first->next;
    }
    z.size = x.size + y.size;
    return z;
}

Chain Merge2(Chain & x, Chain & y) {
    Chain z;
    Node * last;
    if (x.first->value <= y.first->value) {
        z.first = x.first;
        last = x.first;
        }
    else {
        z.first = y.first;
        last = y.first;
    }
    while ((y.first) && (x.first)) {

        if (last == x.first) {
            x.first = x.first->next;
        }
        if (last == y.first) {
            y.first = y.first->next;
        }

        if ((y.first) && (x.first)) {
            if (x.first->value <= y.first->value) {
            last->next = x.first;
            last = last->next;
            }
            else {
            last->next = y.first;
            last = last->next;
            }
        }
    }

    while (x.first) {
        last->next = x.first;
        last = last->next;
        x.first = x.first->next;
    }

    while (y.first) {
        last->next = y.first;
        last = last->next;
        y.first = y.first->next;
    }
    z.size = x.size + y.size;
    return z;
}