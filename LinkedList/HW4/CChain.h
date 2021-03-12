#pragma once
#include <iostream>
using namespace std;

template <class T>
class CChain;

template <class T>
ostream & operator <<(ostream & output, CChain<T> & chain);

template <class T>
class ChainNode2 {
    friend class CChain<T>;
    friend ostream & operator <<(ostream & output, CChain<T> & chain);
    public:
        ChainNode2<T>(T s) {
            data = s;
            link = 0;
        }
    private:
        T data;
        ChainNode2<T> * link;
};

template <class T>
class CChain {
    inline friend ostream & operator <<(ostream & output, CChain<T> & chain) {
        class CChain<T>::ChainIterator x = chain.begin();
        while (x != chain.end()) {
            output << *x << " ";
            x++;
        }
        return output;
    }
    public:
        CChain() {
            last = 0;
        }
        class ChainIterator {
            public:
                ChainIterator(ChainNode2<T> * startNode = 0) {
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
                ChainNode2<T> * current;
        };
        ChainIterator begin() {
            return ChainIterator(last->link);
        }
        ChainIterator end() {
            return ChainIterator(last);
        }
        inline void Add(const T s) {
            ChainNode2<T> * second = new ChainNode2<T>(s);
            if (last) {
            second->link = last->link;
            last->link = second;
            }
            else {
            last = second;
            second->link = second;
            }
        }
        inline void print() {
            ChainNode2<T> * k = last->link;
            for (; k!= last; k = k->link) {
            cout << k->data << " ";
            }
            cout << k->data << " ";
        }

    private:
        ChainNode2<T> * last;
};



