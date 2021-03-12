#include "Queue.h"
#include "Queue.cpp"
#include <iostream>
using namespace std;

int main() {
    Queue<char> a(8);
    a.queue[0] = 'D';
    a.queue[1] = 'E';
    a.queue[2] = 'F';
    a.queue[5] = 'A';
    a.queue[6] = 'B';
    a.queue[7] = 'C';

    a.Insert('Z', 1);
    a.Insert('V', 6);
    a.Insert('Q', 0);
    for (int i = 0; i < 9; i ++) {
        cout << a.queue[i] << " ";
    }
    cout << endl;
    cout << a.front << " " << a.rear << endl;
    cout << a.Size() << endl;
}