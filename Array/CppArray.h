#pragma once
#include <iostream>
using namespace std;

class CppArray {
    // input operator overloading for inputting value for the array
    friend istream & operator>>(istream & input, CppArray & cp2);

    // output operator overloading for outputting value for the array
    friend ostream & operator<<(ostream & output, const CppArray & cp2);

    public:
        // default constructor with array size and default sata value
        CppArray(int arraySize = 10, float initValue = 0); 

        // copy constructor for initializing the object with another class object
        CppArray(const CppArray & cp2); 

        //destructor
        ~CppArray();

        // assignment operator overloading for replacing the orginal array with cp2
        // return const object to avoid (a1 = a2) = a3
        const CppArray & operator=(const CppArray & cp2); 

        // equality operator overloading for evaluating whether the original array and cp2 are same
        bool operator==(const CppArray & cp2) const; 

        // inequality operator overloading
        bool operator!=(const CppArray & cp2) const { 
            return !(*this == cp2); 
        }

        // subscript operator for non-const objects returns modifiable lvalue
        float & operator[](int i);

        // subscript operator for const objects returns non-modifiable rvalue
        float operator[](int i) const;


        // return the size of array
        int getsize() const;

    private:
        float * ptr;
        int size;
};