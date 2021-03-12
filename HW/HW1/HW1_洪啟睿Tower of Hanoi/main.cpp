// Simple main to create and solve the Tower of Hanoi puzzle.
// @author Mike Hong <y6602016@gmail.com>

#include "Tower.h"
#include <iostream>
using namespace std;

int main() {
    Tower t;
    cout << "Initial Tower: " << endl;
    cout << t << endl;

    t.Action();

    cout << "Final Tower: " << endl;
    cout << t << endl;

    return 0;
}