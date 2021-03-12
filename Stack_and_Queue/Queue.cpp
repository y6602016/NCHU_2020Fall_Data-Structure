#include "Queue.h"
#include <iostream>
using namespace std;

template <typename T>
Queue<T>::Queue(int QCapacity) : capacity(QCapacity){
    if (capacity < 1) throw "The capacity must be < 0";
    queue = new T[capacity];
    front = 4;
    rear = 2;
}

template <typename T>
Queue<T>::~Queue() {
    delete [] queue;
}

template <typename T>
void Queue<T>::Delete(const int k) {
    int pos = (front + k) % capacity;
    int start = (front + 1) % capacity; 
    if (isEmpty()) throw "Queue is empty, cann't delete";
    if (k == 1) {
        front = start;
        queue[front].~T();
    }
    else {
        if (pos < front) {
        copy(queue, queue + pos, queue + 1);
        queue[0] = queue[capacity - 1];
        copy(queue + start, queue + capacity - 1, queue + start + 1);
        front = start;
        queue[front].~T();
    }
        else if (pos > front) {
        copy(queue + start, queue + pos, queue + start + 1);
        front = start;
        queue[front].~T();
    }
    }
}

template <typename T>
void Queue<T>::Insert(const T & y, const int k) {
    if ((rear + 1) % capacity == front) {
        T * newQueue = new T[capacity * 2];
        int start = (front + 1) % capacity;
        if (start < 2) {
            copy(queue + start, queue + start + capacity - 1, newQueue);
        }
        else {
            copy(queue + start, queue + capacity, newQueue);
            copy(queue, queue + rear + 1, newQueue + capacity - start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete [] queue;
        queue = newQueue;
    }
    int pos = (front + k + 1) % capacity;
    int end = (rear + 1) % capacity;
    if (pos <= rear) {
        copy(queue + pos, queue + end, queue + pos + 1);
        queue[pos] = y;
        rear = end;
    }
    else if (pos > rear) {
        copy(queue, queue + end, queue + 1);
        rear = end;
        queue[0] = queue[capacity - 1];
        if (pos == (capacity - 1)) {
            queue[capacity - 1] = y;
        }
        else {
            copy(queue + pos, queue + capacity - 1, queue + pos + 1);
            queue[pos] = y;
        }
    }
}

template <typename T>
int Queue<T>::Size() {
    if (isEmpty()) {
        return 0;
    }
    else if (front > rear) {
        return capacity - ((front - rear) % capacity);
    }

    else {
        return capacity - ((rear - front) % capacity);
    }
}