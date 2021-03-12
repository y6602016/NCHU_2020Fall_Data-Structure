#include "Deque.h"
#include <iostream>
using namespace std;


int main() {
    Deque<int> a;
    a.insertFront(5);
    a.insertFront(10);
    a.insertFront(15);
    cout << "Insert 5, 10, 15 at front" << endl;
    cout << "Deque a: ";
    a.printForward();
    cout << endl;
    a.deleteBack();
    cout << "Delete back"<< endl;
    cout << "Deque a: ";
    a.printForward();
    cout << endl;
    a.insertBack(20);
    cout << "Insert 20 at back"<< endl;
    cout << "Deque a: ";
    a.printForward();
    cout << endl;
    a.insertBack(25);
    cout << "Insert 25 at back"<< endl;
    cout << "Deque a: ";
    a.printForward();
    cout << endl;
    a.deleteFront();
    cout << "Delete front"<< endl;
    cout << "Deque a: ";
    a.printForward();
    cout << endl;
    cout << "Print conversely"<< endl;
    cout << "Deque a: ";
    a.printBackward();
    cout << endl;
    Deque<int> b(a);
    cout << "After using the copy constructor"<< endl;
    cout << "Deque a: ";
    a.printForward();
    cout << "Deque b: ";
    b.printForward();
}