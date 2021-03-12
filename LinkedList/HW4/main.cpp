#include "Chain.h"
#include "Chain2.h"
#include "CChain.h"
#include "HChain.h"
#include "math.h"
#include "Deque.h"
#include <iostream>
using namespace std;


int sum_five(Chain2<int> & chain) {
    Chain2<int>::ChainIterator one = chain.begin();
    Chain2<int>::ChainIterator plusFive = one;
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

int sum_five2(CChain<int> & chain) {
    CChain<int>::ChainIterator one = chain.begin();
    CChain<int>::ChainIterator plusFive = one;
    for (int i = 0; i < 5; i++) {
        plusFive++;
    }
    int sum = 0;
    while (plusFive != chain.end()) {
        sum += (*one) * (*plusFive);
        one++;
        plusFive++;
    }
    sum += (*one) * (*plusFive);
    return sum;
    }

double cal(Polynomial & poly, double x) {
    Polynomial::PolyIterator p = poly.begin();
    double total = 0;
    while (p->exp != -1) {
        double exp_cal = x;
        exp_cal = pow(x, p->exp);
        total += exp_cal * p->coef;
        p++;
    }
    return total;
}

int main() {
    // Chain a(10);
    // a.Add(8);
    // a.Add(5);
    // a.Add(4);
    // a.Add(3);
    // a.Add(2);
    // a.print();
    // cout << endl;
    // Chain b(6);
    // b.Add(1);
    // b.print();
    // cout << endl;
    // Chain c = Merge2(a, b);
    // c.print();
    // cout << endl;
    //------------------------
    // Chain2<int> x;
    // x.Add(3);
    // x.Add(5);
    // x.Add(8);
    // x.Add(9);
    // x.Add(9);

    // x.Add(8);
    // x.Add(6);
    // x.Add(10);
    // x.Add(2);
    // x.Add(0);
    // cout << sum_five(x) << endl;
    // printOut(x);
    //------------------------

    // CChain<int> y;
    // y.Add(2);
    // y.Add(8);
    // y.Add(4);
    // y.Add(10);
    // y.Add(5);

    // y.Add(10);
    // y.Add(3);
    // y.Add(9);
    // y.Add(7);
    // cout << sum_five2(y) << endl;

    //-------------------

    // Polynomial d;
    // d.Add(2, 4);
    // d.Add(3, 3);
    // d.Add(2, 2);
    // d.Add(1, 0);
    // cout << cal(d, 2) << endl;

    //-------------------
    Deque s;
    s.insertFront(5);
    s.insertFront(10);
    s.insertBack(8);
    s.insertFront(3);
    s.insertBack(90);
    s.print();
    cout << endl;
    s.deleteFront();
    s.print();
    cout << endl;
    s.deleteBack();
    s.print();
    cout << endl;
    s.insertFront(100);
    s.insertBack(99);
    s.print();
    cout << endl;
    s.deleteBack();
    s.deleteBack();
    s.print();
    cout << endl;
}