#include "NStack.h"
#include <iostream>
using namespace std;

NStack::NStack(int stackCapacity) : size(stackCapacity) {
    narray = new int(size);
    top = -1;
}

NStack::~NStack() {
    delete [] narray;
}

void NStack::Push(int d) {
    if (top == size - 1) {
        Resize();
    }
    narray[++top] = d;
}

int NStack::Pop() {
    int temp = narray[top];
    top --;
    return temp;
}

bool NStack::isEmpty() {
    return top == -1;
}

void NStack::Resize() {
    int * temp = new int[size * 2];
    copy(narray, narray + top + 1, temp);
    delete [] narray;
    narray = temp;
    size *= 2;
}

void NStack::Output(NStack & s) {
    for (int i = 0; i < (s.top + 1); i ++) {
        cout << narray[i] << " ";
    }
}

bool NStack::Remove(NStack & s, int num) {
    for (int i = 0; i <= s.top; i ++) {
        if (s.narray[i] == num) {
            if ( i == s.top) { // special case if the element is at the end of the stack
                s.top --;
            }
            else {
                int temp_size = s.top - i;
                NStack temp(temp_size); // use a temp stack to copy the element
                copy(s.narray + i + 1, s.narray + top + 1, temp.narray);
                copy(temp.narray, temp.narray + temp_size, s.narray + i); // copy the element back to the stack
                s.top --;
            }
            return true;
        }
    }
    return false;
}

void NStack::Sort(NStack & s) { // use bubble sort to sort the stack
    for (int i = 0; i < top; i ++) {
        for (int j = 0; j < top - i; j ++) {
            if (s.narray[j] > s.narray[j + 1]) {
                int temp = s.narray[j];
                s.narray[j] = s.narray[j + 1];
                s.narray[j + 1] = temp;
            }
        }
    }
}