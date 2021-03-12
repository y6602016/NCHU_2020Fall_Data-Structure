#pragma once

template <typename T>
class Queue {
    public:
        Queue(int QCapacity = 10); // condtructor
        ~Queue(); // destructor
        inline bool isEmpty() {
            return front == rear;
        } 
        void Insert(const T & y, const int k); // insert a y element after the kth element
        void Delete(const int k); // delete the kth element
        inline T& Get(const int k) {
            if (isEmpty()) {
                throw "The queue is empty!";
            }
            return queue[k];
        } // return the kth element
        int Size(); // return the size of the list
        T * queue;
        int front, rear, capacity;
    private:
};

