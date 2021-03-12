#pragma once


class NStack {
    public:
        NStack(int = 10);
        ~NStack();
        void Push(int d);
        int Pop();
        bool isEmpty();
        void Output(NStack & s); // output the all elements in the s
        bool Remove(NStack & s, int num); // remove the element with the value num, after the deletion, other elements are in the same order
        void Sort(NStack & s); // sort the stack from the smallest elemnt to the largest
    private:
        void Resize(); // resize the array doubly
        int top, size;
        int * narray; 
};