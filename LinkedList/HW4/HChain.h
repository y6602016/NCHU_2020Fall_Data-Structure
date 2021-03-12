#pragma once
#include <iostream>
using namespace std;

template <class T>
class HChain;

class Polynomial;

template <class T>
ostream & operator <<(ostream & output, HChain<T> & chain);

template <class T>
class ChainNode3 {
    friend class HChain<T>;
    friend class Polynomial;
    friend ostream & operator <<(ostream & output, HChain<T> & chain);
    public:
        ChainNode3<T>() {
            link = 0;
        }
        ChainNode3<T>(T s) {
            data = s;
            link = 0;
        }
    private:
        T data;
        ChainNode3<T> * link;
};

template <class T>
class HChain {
    friend class Polynomial;
    inline friend ostream & operator <<(ostream & output, HChain<T> & chain) {
        class HChain<T>::ChainIterator x = chain.begin();
        while (x != chain.end()) {
            output << *x << " ";
            x++;
        }
        return output;
    }
    public:
        HChain() {
            head = new ChainNode3<T>;
            last = head;
            last->link = head;
        }
        class ChainIterator {
            public:
                ChainIterator(ChainNode3<T> * startNode = 0) {
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
                ChainNode3<T> * current;
        };
        ChainIterator begin() {
            return ChainIterator(head->link);
        }
        ChainIterator end() {
            return ChainIterator(last);
        }
        inline void Add(const T s) {
            ChainNode3<T> * second = new ChainNode3<T>(s);
            last->link = second;
            last = second;
            last->link = head;
        }
        inline void print() {
            ChainNode3<T> * k = head->link;
            for (; k!= last; k = k->link) {
            cout << k->data << " ";
            }
            cout << k->data << " ";
        }

    private:
        ChainNode3<T> * head;
        ChainNode3<T> * last;
};

class Polynomial;

class Term {
    friend class Polynomial;
    public:
        int coef;
        int exp;
        Term Set(int c, int e) {
            coef  = c;
            exp = e;
            return *this;
        }
};

class Polynomial{
    public:
        Polynomial(){
            poly = new HChain<Term>;
            poly->head->data.exp = -1;
        }

        inline void Add(int c, int e) {
            ChainNode3<Term> * second = new ChainNode3<Term>;
            second->data.Set(c, e);
            poly->last->link = second;
            poly->last = second;
            poly->last->link = poly->head;
        }

        inline void print() {
            ChainNode3<Term> * k = poly->head->link;
            for (; k!= poly->last; k = k->link) {
            cout << k->data.coef << " " << k->data.exp << " " << endl;
            }
            cout << k->data.coef << " " << k->data.exp << " " << endl;
        }
        class PolyIterator {
            public:
                PolyIterator(ChainNode3<Term> * startNode = 0) {
                    current = startNode;
                }

                Term & operator *() const {
                    return current->data;
                }

                Term * operator->() const {
                    return &current->data;
                }

                PolyIterator & operator ++() {
                    current = current->link;
                    return *this;
                }

                PolyIterator operator ++(int) {
                    PolyIterator old = *this;
                    current = current->link;
                    return old;
                }

                bool operator != (const PolyIterator right) const {
                    return current != right.current;
                }

                bool operator == (const PolyIterator right) const {
                    return current == right.current;
                }
            private:
                ChainNode3<Term> * current;
        };
        PolyIterator begin() {
            return PolyIterator(poly->head->link);
        }
        PolyIterator end() {
            return PolyIterator(poly->last);
        }
    private:
        HChain<Term> * poly;
};



