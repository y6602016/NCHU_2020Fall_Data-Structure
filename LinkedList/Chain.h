#pragma once
#include <iostream>
using namespace std;


template <class T> class Chain;
template <class T> class CircularList;

template <class T>
class ChainNode {
    friend class Chain<T>;
    friend class CircularList<T>;
    friend class Polynomia;
    public:
        ChainNode(T element, ChainNode<T> * next) {
            data = element;
            link = next;
        }

    private:
        T data;
        ChainNode<T> * link;
};

template <class T>
class Chain {
    public:
        friend class Polynomia;
        class ChainIterator {
            public:
                ChainIterator(ChainNode<T> * startNode = 0) {
                    current = startNode;
                }

                T & operator*() const {
                    return current->data;
                }

                T * operator->() const {
                    return &current->data;
                }

                ChainIterator & operator++() {
                    current = current->link;
                    return *this;
                }

                ChainIterator & operator++(int) {
                    ChainIterator old = *this;
                    current = current->link;
                    return old;
                }

                bool operator!=(const ChainIterator right) const {
                    return current != right.current;
                }

                bool operator==(const ChainIterator right) const {
                    return current == right.current;
                }
            private:
                ChainNode<T> * current;
        };
        Chain() {
            first = 0;
            last = 0;
        }
        // void create2();
        // void Inser50(ChainNode<T> * x);
        // void Delete(ChainNode<T> * x, ChainNode<T> * y);
        void InsertBack(const T & e);
        // void Concatenate(Chain<T> & b);
        void print();
        // void Reverse();
        ChainIterator begin() const{
            return ChainIterator(first);
        }
        ChainIterator end() const{
            return ChainIterator(last);
        }
    private:
        int size = 0;
        ChainNode<T> * first;
        ChainNode<T> * last;
};

// template <class T>
// void Chain<T>::create2() {
//     ChainNode<T> * second = new ChainNode<T>(20, 0);
//     first = new ChainNode<T>(10, second);
// }

// template <class T>
// void Chain<T>::Inser50(ChainNode<T> * x) {
//     if (first) {
//         x->link = new ChainNode<T>(50, x->link);
//     }
//     else {
//         first = new ChainNode<T>(50);
//     }
// }

// template <class T>
// void Chain<T>::Delete(ChainNode<T> * x, ChainNode<T> * y) {
//     if (x == first) {
//         first = first->link;
//     }

//     else {
//         y->link =  x->link;
//     }
//     delete x;
// }

template <class T>
void Chain<T>::InsertBack(const T & e) {
    // if (first) {
    //     last->link = new ChainNode<T>(e);
    //     last = last->link;
    // }
    // else {
    //     first = last = new ChainNode<T>(e);
    // }
    last->link = new ChainNode<T>(e, first);
    last = last->link;
    size += 1;
}

// template <class T>
// void Chain<T>::Concatenate(Chain<T> & b) {
//     if (first) {
//         last->link = b.first;
//         last = b.last;
//     }
//     else {
//         first = b.first;
//         last = b.last;
//     }
//     b.last = 0;
//     b.first = 0;
// }

// template <class T>
// void Chain<T>::Reverse() {
//     ChainNode<T> * current = first, * previous = 0;
//     while (current) {
//         ChainNode<T> * r = previous;
//         previous = current;
//         current = current->link;
//         previous->link = r;
//     }
//     last = first;
//     first = previous;
// }



template <class T>
void Chain<T>::print() {
    // for (ChainNode<T> * ptr = first; ptr != 0; ptr = ptr->link) {
    //     cout << ptr->data << endl;
    // }
    for (ChainIterator i = first; i != 0; i ++) {
        cout << *i << endl;
    }
}

//Below is CircularList class//


// template <class T>
// class CircularList {
//     public:
//         CircularList<T>() {
//             last = 0;
//         }
//         ~CircularList<T>();
//         void InsertFront(const T & e);
//         ChainNode<T> * GetNode();
//         void RetNode(ChainNode<T> *& x);
//     private:
//         ChainNode<T> * last;
//         static ChainNode<T> * av;
// };



// template <class T>
// ChainNode<T> * CircularList<T>::av = 0;

// template <class T>
// void CircularList<T>::InsertFront (const T & e) {
//     ChainNode<T> * newNode = new ChainNode<T>(e);
//     if (last) {
//         newNode->link = last->link;
//         last->link = newNode;
//     }

//     else {
//         last = newNode;
//         newNode->link = newNode;
//     }
// }

// template <class T>
// ChainNode<T> * CircularList<T>::GetNode() {
//     ChainNode<T> * x;
//     if (av) {
//         x = av;
//         av = av->link;
//     }
//     else {
//         x = new ChainNode<T>;
//     }
//     return x;
// }

// template <class T>
// void CircularList<T>::RetNode(ChainNode<T> *& x) {
//     x->link = av;
//     av = x;
//     x = 0;
// }

// template <class T>
// CircularList<T>::~CircularList() {
//     if (last) {
//         ChainNode<T> * first = last->link;
//         last->link = av;
//         av = first;
//         last = 0;
//     }
// }

struct Term {
    int coef; //係數//
    int exp;  //指數//
    Term Set(int c, int e) {
        coef = c;
        exp = e;
        return *this;
    }
};

class Polynomia {
    public:
        Polynomia operator+(const Polynomia & b) const;
        void print();
        Chain<Term> poly;
        Polynomia();
    private:
        // Chain<Term> poly;
};

// Polynomia Polynomia::operator+(const Polynomia & b) const {
//     Term temp;
//     Chain<Term>::ChainIterator ai = poly.begin(), bi = b.poly.begin();
//     Polynomia c;
//     while ((ai != 0) && (bi != 0)) {
//         if (ai->exp == bi->exp) {
//             int sum = ai->coef + bi->coef;
//             if (sum) {
//                 c.poly.InsertBack(temp.Set(sum, ai->exp));
//                 ai ++;
//                 bi ++;
//             }
//         }

//         else if (ai->exp < bi->exp) {
//             c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
//             bi ++;
//         }

//         else {
//             c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
//             ai ++;
//         }
//     }
//     while (ai != 0) {
//         c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
//         ai ++;
//     }

//     while (bi != 0) {
//         c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
//         bi ++;
//     }

//     return c;

// }

void Polynomia::print() {
    Chain<Term>::ChainIterator i = poly.begin();
    i ++;
    for (i; i != poly.begin(); i ++) {
        cout << i->coef << " " << i->exp << endl;
    }
    // ChainNode<Term> * toprint = poly.first->link;
    // for (int i = 0; i < poly.size; i ++) {
    //     cout << toprint->data.coef << " " << toprint->data.exp << endl;
    //     toprint = toprint->link;
    // }
}

Polynomia::Polynomia() {
    Term temp;
    temp.Set(0, -1);
    poly.first = new ChainNode<Term>(temp, poly.first);
    poly.last = poly.first;
    poly.first->link = poly.last;
}

Polynomia Polynomia::operator+(const Polynomia & b) const {
    Term temp;
    Chain<Term>::ChainIterator ai = poly.begin(), bi = b.poly.begin();
    ai++;
    bi++;
    Polynomia c;
    while (1) {
        if (ai->exp == bi->exp) {
            if (ai->exp == -1) {
                return c;
            }
            int sum = ai->coef + bi->coef;
            if (sum) {
                c.poly.InsertBack(temp.Set(sum, ai->exp));
                ai ++;
                bi ++;
            }
        }

        else if (ai->exp < bi->exp) {
            c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
            bi ++;
        }

        else {
            c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
            ai ++;
        }
    }
}
