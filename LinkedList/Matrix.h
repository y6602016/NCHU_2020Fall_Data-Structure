#include <iostream>
using namespace std;

struct Triple {
    int row, col, value;
}

class Matrix;

class MatrixNode {
    friend class matrix;
    friend istream & operator>>(istream &, Matrix &);
    private:
    MatrixNode(bool, Triple *);
    MatrixNode * down, * right;
    bool head;
    uinion {
        MatrixNode * next;
        Triple triple;
    }
};

MatrixNode::MatrixNode(bool b, Triple * t) {
    if(b) {
        right = down = this;
    }
    else {
        triple = *t;
    }
}

class Matrix {
    friend istream & operator>>(istream &, Matrix &);
    public:
        ~Matrix();
    private:
        MatrixNode * headnode;
};

istream & operator>>(istream & is, Matrix & matrix) {
    Triple s;
    is >> s.row >> s.col >> s.value;
    int p = max(s.row, s.col);
    // create the headnode of the headnode list //
    // false boolean value means that it is a headnode //
    matrix.headnode = new MatrixNode(false, &s);
    if (p == 0) {
        matrix.headnode->right = matrix.headnode;
        return is;
    }
    //head array stores the pointer of each headnode//
    MatrixNode ** head = new MatrixNode * [p];
    for (int i = 0; i < p; i ++) {
        head[i] = new MatrixNode(true, 0);
    }

    int currentRow = 0;
    MatrixNode * last = head[0]; //the last node of this row //

    // import the three-info to the valid nodes // 
    for (int i = 0; i < s.value; i ++) {
        Triple t;
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow) {
            last->right = head[currentRow]; // close the current row //
            currentRow = t.row;
            last = head[currentRow];
        }
        // add node to the row //
        last->right = new MatrixNode(false, &t); 
        last = last->right;
        // add node to the col //
        head[t.col]->down = last;
        head[t.col]->next
    }


}