#include "Matrix.h"
#include <algorithm>
#include <exception>


Matrix::Matrix(int r, int c, int t) {
    rows = r;
    cols = c;
    terms = t;
    capacity = t + 1;
    smArray = new MatrixTerm[capacity]; // create an array with the capacity as the size
}

void Matrix::IntAndOut() {
    cout << "1. Please enter the term information in the format:row col value(ex:3 5 10) :" << endl;
    cout << "2. Press Enter to key in the next term" << endl;
    cout << "3. Please key in " << terms << " terms." << endl;
    cout << "4. The valid row index is < " << rows << " , col index is < " << cols << endl;
    cin >> *this; // input the terms
    cout << endl;
    cout << "The terms of this Matrix you give are:" << endl;
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

ostream & operator<<(ostream & output, Matrix & matrix) {
    for (int i = 0; i < matrix.terms; i ++) {
        output << "row: " << matrix.smArray[i].row << " col: " << matrix.smArray[i].col << " value: " << matrix.smArray[i].value << endl;
    }
    return output;
}

istream & operator>>(istream & input, Matrix & matrix) {
    for (int i = 0; i < matrix.terms; i ++) {
        input >> matrix.smArray[i].row >> matrix.smArray[i].col >> matrix.smArray[i].value;
    }
    return input;
}

void Matrix::ChangeSize1D(const int newSize) {
    if (newSize < terms) {
        cout << "New Size must be >= number of terms" << endl;
        return;
    }
    MatrixTerm * temp = new MatrixTerm[newSize]; // create a new array with the new size
    copy(smArray, smArray + terms, temp);
    delete [] smArray;
    smArray = temp;
    capacity = newSize;
}

void Matrix::StoreSum(const int r, const int c, const int sum) {
    if (sum != 0) {
        if (terms == capacity) {
            ChangeSize1D(capacity * 2);
        }
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
}

Matrix Matrix::Transpose() {
    Matrix b(rows, cols, terms);
    if (terms > 0) {
        int * rowSize = new int[cols]; // create an array to store the number of terms of each row of b seperately
        int * rowStart = new int[cols]; // create an array to store the index indicating the start position of row in b;
        fill(rowSize, rowSize + cols, 0);
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
        delete [] rowSize;
        delete [] rowStart;
    }
    return b;   
}

Matrix Matrix::Add(const Matrix b) {
    if (rows == b.rows && cols == b.cols) { // check the sizes of these two matrices
        Matrix c(rows, cols, 0);
        int aPos = 0, bPos = 0;
        while ((aPos < terms) && (bPos < b.terms)) {
            if (smArray[aPos].row == b.smArray[bPos].row) { // add two value if their row and col index are same
                if (smArray[aPos].col == b.smArray[bPos].col) {
                    c.StoreSum(smArray[aPos].row, smArray[aPos].col, smArray[aPos].value + b.smArray[bPos].value);
                    aPos ++;
                    bPos ++;
                }
                else if (smArray[aPos].col > b.smArray[bPos].col) {
                    c.StoreSum(b.smArray[bPos].row, b.smArray[bPos].col, b.smArray[bPos].value);
                    bPos ++;
                }
                else {
                    c.StoreSum(smArray[aPos].row, smArray[aPos].col, smArray[aPos].value);
                    aPos ++;
                }
            }

            else if (smArray[aPos].row > b.smArray[bPos].row) {
                c.StoreSum(b.smArray[bPos].row, b.smArray[bPos].col, b.smArray[bPos].value);
                bPos ++;
            }
            else {
                c.StoreSum(smArray[aPos].row, smArray[aPos].col, smArray[aPos].value);
                aPos ++;
            }
        }

    for (; aPos < terms; aPos ++) {
        c.StoreSum(smArray[aPos].row, smArray[aPos].col, smArray[aPos].value);
    }  

    for (; bPos < b.terms; bPos ++) {
        c.StoreSum(b.smArray[bPos].row, b.smArray[bPos].col, b.smArray[bPos].value);
    }

    return c;
    }
    else {
        throw ("The size of these two matrises are not same!");
    } 
}

Matrix Matrix::Multiply(Matrix b) {
    if (cols != b.rows) {
        throw "Incompatible matrices";
    }

    // transpose the b matrix and build a new array d to store the prodcut value
    Matrix bXpose = b.Transpose();
    Matrix c(rows, b.cols, 0);

    int currRowIndex = 0, currRowBegign = 0, currRowA = smArray[0].row;

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
        int currColB = bXpose.smArray[0].row, currColIndex = 0;
        // multiply row currRowA of *this by column currColB of b
        while (currColIndex <= b.terms) {
            if (smArray[currRowIndex].row != currRowA) { // end of row currRowA
                c.StoreSum(currRowA, currColB, sum);
                sum = 0; // reset sum
                currRowIndex = currRowBegign;
                // advance to the next column of b
                while (bXpose.smArray[currColIndex].row == currColB) {
                    currColIndex ++;
                }
                currColB = bXpose.smArray[currColIndex].row;
            }

            else if (bXpose.smArray[currColIndex].row != currColB) { // end of collumn currColB
                c.StoreSum(currRowA, currColB, sum);
                sum = 0;
                currRowIndex = currRowBegign;
                currColB = bXpose.smArray[currColIndex].row;
            }

            else {
                if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col) {
                    sum += smArray[currRowIndex].value * bXpose.smArray[currColIndex].value;
                    currRowIndex ++;
                    currColIndex ++;
                }

                else if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col) {
                    currRowIndex ++;
                }
                
                else {
                    currColIndex ++;
                }
            }
        }

        while (smArray[currRowIndex].row == currRowA) {
            currRowIndex ++;
        }
        currRowBegign = currRowIndex;
        currRowA = smArray[currRowIndex].row;
    }
    return c;
}


int Matrix::getDet() {
    // the end point of the recursion is when the rows and cols are 2
    if (rows == 2) {
        return ((smArray[0].value * smArray[3].value) - (smArray[1].value * smArray[2].value));
    }

    else {
        int sum = 0;
        for (int i = 0; i < cols; i ++) {
            // use the elements in the first row as target elements
            int down = rows - 1, result;
            int s = 0, temp_r = 0, temp_c = 0;
            Matrix temp(down, down, down * down); // create a sub-matrix with size of rows -1 to store the element that is not at the same line of the target element
            for (int j =0; j < terms; j ++) {
                if (smArray[j].row != smArray[i].row && smArray[j].col != smArray[i].col) {
                    temp.smArray[s].row = temp_r;
                    temp.smArray[s].col = temp_c;
                    temp.smArray[s].value = smArray[j].value;
                    s++;
                    temp_c ++;
                    if ((temp_c % down) == 0) { // row ++ when the col is at the end of the row
                        temp_r ++;
                        temp_c = 0;
                    }
                    
                }
            }
            result = smArray[i].value * temp.getDet(); // use the recursion to multiply the target element and the determinate of the sub-matrix
            if ((smArray[i].row + smArray[i].col) % 2 == 1) {
                result *= -1;
            }
            sum += result;
    }
    return sum;
}
}

int Matrix::Determinate() {
    // check whether the matrix is a asquare matrix
    if (rows != cols) {
        throw "The matrix is not a square matrix";
    }
    
    // expand the sparse matrix array to a full matrix array with 0 for calculation
    Matrix det(rows, cols, rows * cols);
    int temp_r = 0, temp_c = 0, j = 0;
    for (int i = 0; i < (rows * cols); i ++) {
        det.smArray[i].row = temp_r;
        det.smArray[i].col = temp_c;
        if ((smArray[j].row == det.smArray[i].row) && (smArray[j].col == det.smArray[i].col)) {
            det.smArray[i].value = smArray[j].value;
            j++;
        }
        else det.smArray[i].value = 0;
        temp_c ++;
        if ((temp_c % rows) == 0) {
            temp_r ++;
            temp_c = 0;
            }
    }
    // use the sub-function getDet() to calculate the determinate
    return det.getDet();
}

int Matrix::getMinor() {
    if (rows == 2) {
        return ((smArray[0].value * smArray[3].value) - (smArray[1].value * smArray[2].value));
    }

    else {
        int sum = 0;
        for (int i = 0; i < cols; i ++) {
            int down = rows - 1, result;
            int s = 0, temp_r = 0, temp_c = 0;
            Matrix temp(down, down, down * down);
            for (int j =0; j < terms; j ++) {
                if (smArray[j].row != smArray[i].row && smArray[j].col != smArray[i].col) {
                    temp.smArray[s].row = temp_r;
                    temp.smArray[s].col = temp_c;
                    temp.smArray[s].value = smArray[j].value;
                    s++;
                    temp_c ++;
                    if ((temp_c % down) == 0) {
                        temp_r ++;
                        temp_c = 0;
                    }
                    
                }
            }
            result = smArray[i].value * temp.getMinor();
            // if the sum of the element's row and col is odd, it's a negtive number
            if ((smArray[i].row + smArray[i].col) % 2 == 1) {
                result *= -1;
            }
            sum += result;
    }
    return sum;
}
}

Matrix Matrix::Cofactor() {
    // check whether the matrix is a square matrix
    if (rows != cols) {
        throw "The matrix is not a square matrix";
    }

    // special case for 2 x 2 matrix
    if (rows == 2) {
        Matrix co(rows, cols, rows * cols);
        co.smArray[0].value = smArray[3].value;
        co.smArray[0].row = 0;
        co.smArray[0].col = 0;
        co.smArray[1].value = (smArray[2].value * -1);
        co.smArray[1].row = 0;
        co.smArray[1].col = 1;
        co.smArray[2].value = (smArray[1].value * -1);
        co.smArray[2].row = 1;
        co.smArray[2].col = 0;
        co.smArray[3].value = smArray[0].value;
        co.smArray[3].row = 1;
        co.smArray[3].col = 1;
        
        return co;
    }
    
    // use recursion to obtain the cofactor matrix
    else {
        // expand the sparse matrix array to a full matrix array with 0 for calculation
        Matrix co(rows, cols, rows * cols);
        int temp_r = 0, temp_c = 0, j = 0;
        for (int i = 0; i < (rows * cols); i ++) {
            co.smArray[i].row = temp_r;
            co.smArray[i].col = temp_c;
            if ((smArray[j].row == co.smArray[i].row) && (smArray[j].col == co.smArray[i].col)) {
                co.smArray[i].value = smArray[j].value;
                j++;
            }
            else co.smArray[i].value = 0;
            temp_c ++;
            if ((temp_c % rows) == 0) {
                temp_r ++;
                temp_c = 0;
                }
        }

        // create a matrix d to store the cofactor
        Matrix d(rows, cols, rows * cols);
        copy(co.smArray, co.smArray + co.terms, d.smArray);
        for (int i = 0; i < co.terms; i ++) {
            int down = rows - 1, result;
            int s = 0, temp_r = 0, temp_c = 0;
            Matrix temp(down, down, down * down); // 
            for (int j =0; j < co.terms; j ++) {
                if (co.smArray[j].row != co.smArray[i].row && co.smArray[j].col != co.smArray[i].col) {
                    temp.smArray[s].row = temp_r;
                    temp.smArray[s].col = temp_c;
                    temp.smArray[s].value = co.smArray[j].value;
                    s++;
                    temp_c ++;
                    if ((temp_c % down) == 0) {
                        temp_r ++;
                        temp_c = 0;
                    }
                    
                }
            }
            int v = temp.getMinor(); // for each element in the matrix, use sub-matrix and recursion to get their cofactors
            if ((d.smArray[i].row + d.smArray[i].col) % 2 == 1) {
                d.smArray[i].value = (v * -1);
            }
            else d.smArray[i].value = v;
        }

    // compress the array to a without-zero-value array    
    Matrix result(d.rows, d.cols, 0);
    for (int i = 0; i < d.terms; i ++) {
        result.StoreSum(d.smArray[i].row, d.smArray[i].col, d.smArray[i].value);
    }
    return result;
    }
}

Matrix Matrix::Adjoint() {
    // use the cofactor funtion and the transpose function to obtain the adjoint matrix
    Matrix b = Cofactor();
    Matrix d = b.Transpose();
    // compress the array to a without-zero-value array 
    Matrix result(d.rows, d.cols, 0);
    for (int i = 0; i < d.terms; i ++) {
        result.StoreSum(d.smArray[i].row, d.smArray[i].col, d.smArray[i].value);
    }
    return result;
}

Matrix Matrix::Inverse() {
    // use the determinate funtion and the adjoint function to obtain the inverse matrix
    int det = Determinate();
    Matrix inv = Adjoint();
    Matrix result(inv.rows, inv.cols, inv.terms);
    copy(inv.smArray, inv.smArray + inv.terms, result.smArray);
    cout << "The inverse Matrix is: " << endl;
    for (int i = 0; i < inv.terms; i ++) { // the output operator overloaiding works on value instead of valueF, so we output the matrix here
        result.smArray[i].valueF = (float)inv.smArray[i].value / det;
        cout << "row: " << result.smArray[i].row << " col: " << result.smArray[i].col <<
         " value: " << result.smArray[i].valueF << endl;
    }
    return result; // note: the corect data values of the matrix returned are sotred in valueF
}