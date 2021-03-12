#pragma once
#include <iostream>
using namespace std;

class SparseMatrix;

class MatrixTerm {
    friend class SparseMatrix;
    friend ostream & operator<<(ostream & output, SparseMatrix & matrix);
    friend istream & operator>>(istream & input, SparseMatrix & matrix);
    private:
        int row, col, value; // the triple element containing information of row, column, value of the terms in the matrix array
};

class SparseMatrix {
    friend ostream & operator<<(ostream & output, SparseMatrix & matrix);
    friend istream & operator>>(istream & input, SparseMatrix & matrix);
    public:
        SparseMatrix(int r, int c, int t); // default constructor with r(rows), c(columns), t(capacity) parameters
        void IntAndOut(); // add new term into smArray
        SparseMatrix Transpose(); // return the SparseMatrix obtained by interchainging the row and column value of every triple in *this
        SparseMatrix FastTranspose(); // transpose in O(terms + cols) times by using a little more space
        SparseMatrix Add(const SparseMatrix b); // add the b matrix and *this
        SparseMatrix Multiply(SparseMatrix b); // multiply the b matrix with *this
        void StoreSum(const int sum, const int r, const int c); // store the multiply results
        void ChangeSize1D(const int newSize); // resize the array
        void print() const;
    private:
        int rows, cols, capacity, terms; // the rows, columns, and size of the matrix
        MatrixTerm * smArray; // the array to store the terms of the sparse matrix
};



