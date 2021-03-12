// C++ class for a "stack" in a Tower of Hanoi assignment of Sata Structure.
// @author Mike Hong <y6602016@gmail.com>

#pragma once
#include <iostream>
using namespace std;

class Matrix;

class MatrixTerm {
    friend class Matrix;
    friend ostream & operator<<(ostream & output, Matrix & matrix);
    friend istream & operator>>(istream & input, Matrix & matrix);
    private:
        int row, col, value; // the triple element containing information of row, column, value of the terms in the matrix array
        float valueF; // only for inverse function
};

class Matrix {
    friend ostream & operator<<(ostream & output, Matrix & matrix); // oupt put a matrix except inverse matrix
    friend istream & operator>>(istream & input, Matrix & matrix); // input a matrix
    public:
        Matrix(int r, int c, int t); // default constructor with r(rows), c(columns), t(capacity) parameters
        Matrix Transpose(); // transpose in O(terms + cols) times by using a little more space
        Matrix Add(const Matrix b); // add the b matrix and *this
        Matrix Multiply(Matrix b); // multiply the b matrix with *this
        int Determinate(); // return the determinate of *this matrix
        Matrix Adjoint(); // return the adjoint of *this matrix
        Matrix Inverse(); // return and desplay the inverse matrix of *this matrix
        Matrix Cofactor(); // return the cofactor matrix of *this matrix
        void IntAndOut(); // input and ouput the matrix
    private:
        int rows, cols, terms, capacity; // the rows, columns, and size of the matrix
        MatrixTerm * smArray; // the array to store the terms of the sparse matrix
    private:
        void ChangeSize1D(const int newSize); // resize the array
        void StoreSum(const int r, const int c, const int sum); // store the multiply results
        int getDet(); // get the minor of the matrix
        int getMinor(); // get the cofactor of the matrix
};