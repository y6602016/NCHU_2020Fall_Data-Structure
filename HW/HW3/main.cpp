#include "NStack.h"
#include <iostream>
using namespace std;


int main() {
    NStack a(10);
    int flag = 1;
    while (flag) {
        cout << "Input a positive integer (-1 to end): ";
        int input;
        cin >> input;
        if (input == -1) {
            flag = 0;
        }
        else {
            a.Push(input);
        }
    }
    flag = 1;
    while (flag) {
        cout << endl;
        cout << "Option: 1) Output. 2) Remove. 3) Sort. 4) Quit: ";
        int select;
        cin >> select;
        switch(select) {
            case 1:
                a.Output(a);
                break;
            case 2:
                cout << "Please enter the number to remove: ";
                int removed;
                cin >> removed;
                if (a.Remove(a, removed)) {
                    cout << "The number " << removed << " has been removed" << endl;
                    cout << "Now the stack is: " << endl;
                    a.Output(a);
                    break;
                }
                else {
                    cout << "The number is not in the stack!" << endl;
                    break;
                }
            case 3:
                a.Sort(a);
                cout << "The sorted stack is: " << endl;
                a.Output(a);
                break;

            case 4:
                flag = 0;
                break;

            default:
                cout << "Please enter again" << endl;
        }
    }
}