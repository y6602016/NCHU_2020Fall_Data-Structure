#include <iostream>
#include "Chain.h"
using namespace std;

int main() {
    Term temp;
    Polynomia a;
    a.poly.InsertBack(temp.Set(9, 4));
    a.poly.InsertBack(temp.Set(7, 3));
    a.poly.InsertBack(temp.Set(5, 2));

    Polynomia b;
    b.poly.InsertBack(temp.Set(4, 3));
    b.poly.InsertBack(temp.Set(1, 1));

    Polynomia c = a + b;
    c.print();


    
}