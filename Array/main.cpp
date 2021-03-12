#include "Polynomial.h"
#include "CppArray.h"
#include "SparseMatrix.h"
#include "String.h"
#include "Rectangle.h"
#include <algorithm>

int compare(int * a, int * b, int n, int m) {
    int i = -1;
    int length = min(n, m);
    for (int j = 0; j < length ; j ++) {
        if (a[j] == b[j]) i = j;
        else break;
    }
    if (i == -1) {
        cout << "There is no same element in both list\n";
        return -2;
    }
    else if (i == n - 1) {
        if (n < m) return -1;
        else if (n == m) return 0;
        else return 1;
    }
    else {
        if (a[i + 1] < b[i + 1]) return -1;
        else return 1;
    }
}

int String_compare(char * a, char * b, int n, int m) {
    int i = -1;
    int length = min(n, m);
    for (int j = 0; j < length ; j ++) {
        if (a[j] == b[j]) i = j;
        else break;
    }
    if (i == -1) {
        cout << "There is no same element in both list\n";
        return -2;
    }
    else if (i == n - 1) {
        if (n < m) return -1;
        else if (n == m) return 0;
        else return 1;
    }
    else {
        if (a[i + 1] < b[i + 1]) return -1;
        else return 1;
    }
}

int main() {
    // SparseMatrix a(3, 3, 3);
    // a.IntAndOut();
    // SparseMatrix b(2, 5, 4);
    // b.IntAndOut();

    // SparseMatrix c = a.FastTranspose();
    // cout << c;


    // String s((char *)"aadddvssssb");
    // String p((char *)"vsss");
    // String com = s.Concat(p);
    // // cout << com << endl;
    
    // Rectangle a(6, 5);
    // Rectangle b(5, 5);
    // cout << (b < a) << endl;

    // int a[] = {1, 3, 5, 8, 30};
    // int b[] = {1, 3, 6, 9, 20};
    // cout << compare(a, b, 5, 5) << endl;

    char a[] = "abcdghk";
    char b[] = "abcdf";
    cout << String_compare(a, b, 7, 5) << endl;

    // Polynomial a;
    // Polynomial b;

    // a.NewTerm(5,2);
    // a.NewTerm(3,1);
    // b.NewTerm(3,2);
    // b.NewTerm(4,0);
    // Polynomial c = a.Multiply(b);
    // cout << c;
    
}