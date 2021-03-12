#pragma once
#include <iostream>
using namespace std;

template <class T>
class Chain2;

template <class T>
ostream & operator <<(ostream & output, Chain2<T> & chain);

template <class T>
class ChainNode {
    friend class Chain2<T>;
    friend ostream & operator <<(ostream & output, Chain2<T> & chain);
    public:
        ChainNode<T>(T s) {
            data = s;
            link = 0;
        }
    private:
        T data;
        ChainNode<T> * link;
};

template <class T>
class Chain2 {
    inline friend ostream & operator <<(ostream & output, Chain2<T> & chain) {
        class Chain2<T>::ChainIterator x = chain.begin();
        while (x != chain.end()) {
            output << *x << " ";
            x++;
        }
        return output;
    }
    public:
        Chain2() {
            first = 0;
        }
        class ChainIterator {
            public:
                ChainIterator(ChainNode<T> * startNode = 0) {
                    current = startNode;
                }

                T & operator *() const {
                    return current->data;
                }

                T * operator->() const {
                    return &current->data;
                }

                ChainIterator & operator ++() {
                    current = current->link;
                    return *this;
                }

                ChainIterator operator ++(int) {
                    ChainIterator old = *this;
                    current = current->link;
                    return old;
                }

                bool operator != (const ChainIterator right) const {
                    return current != right.current;
                }

                bool operator == (const ChainIterator right) const {
                    return current == right.current;
                }
            private:
                ChainNode<T> * current;
        };
        ChainIterator begin() {
            return ChainIterator(first);
        }
        ChainIterator end() {
            return ChainIterator(0);
        }
        inline void Add(const T s) {
            ChainNode<T> * second = new ChainNode<T>(s);
            if (first) {
            second->link = first;
            first = second;
            }
            else {
            first = second;
            }
        }
        inline void print() {
            for (ChainNode<T> * k = first; k!= 0; k = k->link) {
            cout << k->data << " ";
            }
        }

        inline int sum_five(Chain2<int> & chain) {
            ChainIterator one = chain.begin();
            ChainIterator plusFive = one;
            for (int i = 0; i < 5; i++) {
                plusFive++;
            }
            int sum = 0;
            while (plusFive != chain.end()) {
                sum += (*one) * (*plusFive);
                one++;
                plusFive++;
            }

            return sum;
        }
    private:
        ChainNode<T> * first;
};



