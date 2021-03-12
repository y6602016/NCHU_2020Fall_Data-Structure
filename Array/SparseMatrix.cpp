#include "SparseMatrix.h"
#include <algorithm>

SparseMatrix::SparseMatrix(int r, int c, int t) {
    rows = r;
    cols = c;
    terms = t;
    capacity = terms + 1;
    smArray = new MatrixTerm[capacity]; // create an array with the capacity as the size
}

void SparseMatrix::IntAndOut() {

    cout << "1. Please enter the term information in the format:row col value(ex:3 5 10) :" << endl;
    cout << "2. Press Enter to key in the next term" << endl;
    cout << "3. Please key in " << terms << " terms." << endl;
    cout << "4. The valid row index is < " << rows << " , col index is < " << cols << endl;
    cin >> *this;
    cout << endl;
    cout << "The terms of this Matrix are:" << endl;
    cout << *this << endl;
    for (int i = 0; i < terms; i ++) {
        if (smArray[i].row >= rows || smArray[i].col >= cols) {
            cout << "Caveat! The " << i + 1 << "th term's information is incorrect" << endl;
        }
        for (int j = i + 1; j < terms; j ++) {
            if (smArray[i].row == smArray[j].row && smArray[i].col == smArray[j].col) {
                cout << "Caveat! The " << i + 1 << "th term and " << j + 1 << "th term have the same row and col index" << endl;
            }
        }
    }
}

// return the transpose of *this
SparseMatrix SparseMatrix::Transpose() {
    SparseMatrix b(cols, rows, terms); // capacity of b.smArray is the terms of *this
    if (terms > 0) {
        int currentB = 0;
        for (int c = 0; c < cols; c ++) {
            for (int i = 0; i < terms; i ++) {
                if (smArray[i].col == c) { // compare the columns value of each terms in the *this array
                    b.smArray[currentB].row = c;
                    b.smArray[currentB].col = smArray[i].row;
                    b.smArray[currentB++].value = smArray[i].value;
                }
            }
        }
    }
    return b;
}

SparseMatrix SparseMatrix::FastTranspose() {
    SparseMatrix b(cols, rows, terms);
    if (terms > 0) {
        int * rowSize = new int[cols]; // create an array to store the number of terms of each row of b seperately
        int * rowStart = new int[cols]; // create an array to store the index indicating the start position of row in b;
        fill(rowSize, rowSize + cols, 0); // initialize rowSize array
        // scan each term in smArray, 
        // and add the value of the elements in rowSize according to the col value of each term
        for (int i = 0; i < terms; i ++) {
            rowSize[smArray[i].col] ++;
        }

        // rowStart[i] = starting position of row i in b
        rowStart[0] = 0;
        for (int i = 1; i < cols; i ++) {
            rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
        }

        // copy from *this to b
        for (int i = 0; i < terms; i ++) {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col] ++; // next time, when scan the term with same col value, start position will be the next one
        }

        delete [] rowStart;
        delete [] rowSize;
    }
    return b;
}

// if sum != 0, then it along with its row and column position are stored as the last term in *this
void SparseMatrix::StoreSum(const int sum, const int r, const int c) {
    if (sum != 0) {
        if (terms == capacity) {
            ChangeSize1D(2 * capacity); // double size
        }
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
}

// change the size of smArray to the newSize
void SparseMatrix::ChangeSize1D(const int newSize) {
    if (newSize < terms) {
        cout << "New Size must be >= number of terms" << endl;
    }
    MatrixTerm * temp = new MatrixTerm[newSize];
    copy(smArray, smArray + terms, temp);
    delete [] smArray;
    smArray = temp;
    capacity = newSize;
}

SparseMatrix SparseMatrix::Add(const SparseMatrix b) {
    if (rows == b.rows && cols == b.cols) {
        SparseMatrix d(rows, cols, 0);
        int aPos = 0, bPos = 0;
        while ((aPos < terms) && (bPos < b.terms)) {
            if (smArray[aPos].row == b.smArray[bPos].row) {
                if (smArray[aPos].col == b.smArray[bPos].col) {
                    d.StoreSum(smArray[aPos].value + b.smArray[bPos].value, smArray[aPos].row, smArray[aPos].col);
                    aPos ++;
                    bPos ++;
                }
                else if (smArray[aPos].col < b.smArray[bPos].col) {
                    d.StoreSum(smArray[aPos].value, smArray[aPos].row, smArray[aPos].col);
                    aPos ++;
                }
                else {
                    d.StoreSum(b.smArray[bPos].value, b.smArray[bPos].row, b.smArray[bPos].col);
                    bPos ++;
                }
            }

            else if (smArray[aPos].row < b.smArray[bPos].row) {
                d.StoreSum(smArray[aPos].value, smArray[aPos].row, smArray[aPos].col);
                aPos ++;
            }
            else {
                d.StoreSum(b.smArray[bPos].value, b.smArray[bPos].row, b.smArray[bPos].col);
                bPos ++;
            }  
        }

        for (; aPos < terms; aPos ++) {
            d.StoreSum(smArray[aPos].value, smArray[aPos].row, smArray[aPos].col);
        }

        for (; bPos < b.terms; bPos ++) {
            d.StoreSum(b.smArray[bPos].value, b.smArray[bPos].row, b.smArray[bPos].col);
        }

        return d;
    }
    else {
        return *this;
    }

}

// Return the product of the sparse matrices *this and b
SparseMatrix SparseMatrix::Multiply(SparseMatrix b) {
    if (cols != b.rows) {
        cout << "Incompatible matrices";
    }

    // transpose b and build a new array d to store the prodcut value
    SparseMatrix bXpose = b.FastTranspose();
    SparseMatrix d(rows, b.cols, 0);

    int currRowIndex = 0, currRowBegin = 0, currRowA = smArray[0].row;

    // set boundary conditions for the calculation below
    if (terms == capacity) {
        ChangeSize1D(terms + 1);
    }
    bXpose.ChangeSize1D(bXpose.terms + 1);
    smArray[terms].row = rows;
    bXpose.smArray[b.terms].row = b.cols;
    bXpose.smArray[b.terms].col = -1;

    int sum = 0;
    // generate row currentRowA of d
    while (currRowIndex < terms) {
        int currColB = bXpose.smArray[0].row;
        int currColIndex = 0;
        // multiply row currRowA of *this by column currColB of b
        while (currColIndex <= b.terms) {
            if (smArray[currRowIndex].row != currRowA) { // end of row currRowA
                d.StoreSum(sum, currRowA, currColB);
                sum = 0; // reset sum
                currRowIndex = currRowBegin;
                // advance to the next column of b
                while (bXpose.smArray[currColIndex].row == currColB) {
                    currColIndex ++;
                }
                currColB = bXpose.smArray[currColIndex].row;
            }

            else if (bXpose.smArray[currColIndex].row != currColB) { // end of column of column currColB of b
                d.StoreSum(sum, currRowA, currColB);
                sum = 0;
                // set to multiply row corrRowA with next column
                currRowIndex = currRowBegin;
                currColB = bXpose.smArray[currColIndex].row;
            }

            else {
                if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col) {
                    currRowIndex ++; // advance to next term in currRowA
                }

                else if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col) {
                    sum += (smArray[currRowIndex].value * bXpose.smArray[currColIndex].value); // add to sum
                    currRowIndex ++;
                    currColIndex ++;
                }

                else {
                    currColIndex ++; // advance to bext term in currColB
                }
            }
        }

        while (smArray[currRowIndex].row == currRowA) {
            currRowIndex ++; // advance to next row
        }
        currRowBegin = currRowIndex;
        currRowA = smArray[currRowIndex].row;
    }
    return d;
}

void SparseMatrix::print() const {
    for (int i = 0; i < terms; i ++) {
        cout << "value: " << smArray[i].value << " rows: " << smArray[i].row << " cols: " << smArray[i].col << endl;
    }
}

ostream & operator<<(ostream & output, SparseMatrix & matrix) {
    for (int i = 0; i < matrix.terms; i ++) {
        output << "row: " << matrix.smArray[i].row << " col: " << matrix.smArray[i].col << " value: " << matrix.smArray[i].value << endl;
    }
    return output;
}

istream & operator>>(istream & input, SparseMatrix & matrix) {
    for (int i = 0; i < matrix.terms; i ++) {
        input >> matrix.smArray[i].row >> matrix.smArray[i].col >> matrix.smArray[i].value;
    }
    return input;
}



