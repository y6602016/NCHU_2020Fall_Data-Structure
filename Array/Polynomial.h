#pragma once
#include <iostream>
using namespace std;

class Polynomial;

class Term {
    friend class Polynomial;
    friend ostream & operator<<(ostream & output, Polynomial & poly);
    private:
        int exp; // the exponent of the term 
        float coef; // the coefficient of the term 
};

class Polynomial {
        friend ostream & operator<<(ostream & output, Polynomial & poly);
    public:
        Polynomial(); // constructor //
        Polynomial Add(const Polynomial & poly); // return the sum of *this and poly 
        Polynomial Multiply(const Polynomial & poly); // return the product of *this and poly 
        float eval(float f) const; // Evaluate *this at f and return the result 
        void NewTerm(const float theCoeff, const int theExp); // create a new term to the end of termArray 
        void print() const; // print out the termArray
    private:
        Term * termArray; // array of nonzero terms 
        int capacity;   // size of termArray 
        int terms;  // number of nonzero terms 
};

