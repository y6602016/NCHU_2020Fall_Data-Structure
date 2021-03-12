#include "CppArray.h"
#include <iomanip>

CppArray::CppArray(int arraySize, float initValue) {
    // check the valid size
    size = (arraySize > 0 ? arraySize : 10); 

    // create the array and initialize the value
    ptr = new float[size];
    for (int i = 0; i < size; i ++) {
        ptr[i] = initValue;
    }
}

CppArray::CppArray(const CppArray & cp2) : size(cp2.size) {
    // create the array and copy the value
    ptr = new float[size];
    for (int i = 0; i < size; i ++) {
        ptr[i] = cp2.ptr[i];
    }
}

CppArray::~CppArray() {
    delete [] ptr;
}

const CppArray & CppArray::operator=(const CppArray & cp2) {
    // resize the size if the sizes are different
    if (&cp2 != this) { // avoid self-assignment
        if (cp2.size != size) {
            size = cp2.size;
            delete [] ptr;
            ptr = new float[size];
        }

        // replace the value with cp2
        for (int i = 0; i < size; i ++) {
            ptr[i] = cp2.ptr[i];
        }
    }
    return *this;
}

bool CppArray::operator==(const CppArray & cp2) const {
    // compare the size of these two object first
    if (cp2.size != size) {
        return false;
    }

    // compare the value of each data in the arrays
    for (int i = 0; i < size; i ++) {
        if (ptr[i] != cp2.ptr[i]) {
            return false;
        }
    }

    return true;
}

float & CppArray::operator[](int i) {
    // range check
    if (i < 0 || i >= size) {
        cout << "\nError subscript " << i << " out of range" << endl;
    }
    return ptr[i];
}

float CppArray::operator[](int i) const {
    // range check
    if (i < 0 || i >= size) {
        cout << "\nError subscript " << i << " out of range" << endl;
    }
    return ptr[i];
}

int CppArray::getsize() const {
    return size;
}

istream & operator>>(istream & input, CppArray & cp2) {
    // input the value to the array
    for (int i = 0; i < cp2.size; i ++) {
        input >> cp2.ptr[i];
    }
    return input;
}

ostream & operator<<(ostream & output, const CppArray & cp2) {
    // print out the value of the array
    int i;
    for (i = 0; i < cp2.size; i ++) {
        output << setw(12) << cp2.ptr[i];
        if ((i + 1) % 4 == 0) {
            output << endl;
        }
    }

    output << endl;
    return output;
}