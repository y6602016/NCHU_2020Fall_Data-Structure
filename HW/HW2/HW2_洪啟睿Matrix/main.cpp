#include "Matrix.h"

int main() {
    Matrix a(3, 3, 5);
    a.IntAndOut();
    Matrix c = a.Adjoint();
    cout << c << endl;
    // Matrix b(3, 3, 4);
    // b.IntAndOut();
    // Matrix c = a.Multiply(b);
    // cout << "The multiply of these two matrices is: " << endl;
    // cout << c << endl;
}