#include "Polynomial.h"
#include <math.h>


// create an object of Polynomial, the initial capacity is 1 
Polynomial::Polynomial() {
    capacity = 1;
    terms = 0;
    termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float theCoeff, const int theExp) {
    // resize the termArray if the capacity is full 
    if (capacity == terms) {
        capacity *= 2;
        Term * temp = new Term[capacity];
        copy(termArray, termArray + terms, temp); // copy the terms from [0] to [terms - 1] 
        delete[] termArray;
        termArray = temp; // temp is a local variable, no need to delete it 
    }

    // assign the parameter to the termArray 
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp; // increase terms value by 1 after the assignment 
}

Polynomial Polynomial::Add(const Polynomial & poly){
    Polynomial c; // create c as the container for the sum of these two polynomial 
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < poly.terms)) {
        // compare the exponent of *this and poly, if the exp are same, add this term into c 
        if (termArray[aPos].exp == poly.termArray[bPos].exp) {
            c.NewTerm(termArray[aPos].coef + poly.termArray[bPos].coef, termArray[aPos].exp);
            aPos ++;
            bPos ++;
        }

        // if this * exp is smaller, add the poly's term into c 
        else if (termArray[aPos].exp < poly.termArray[bPos].exp) {
            c.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
            bPos ++;
        }

        // if this * exp is larger, add this * term into c 
        else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos ++;
        }
    }
    
    // if aPos or bpos is larger than theri terms, the while loop is terminated, then
    // add the remaining terms into c
    for (; aPos < terms; aPos ++) {
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    }

    for (; bPos < poly.terms; bPos ++) {
         c.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
    }

    return c;
}

Polynomial Polynomial::Multiply(const Polynomial & poly){
    int aPos = 0;
    Polynomial c;
    while (aPos < terms) {
        // calculate the prodcut of the first terms of this * and poly, and put the result into c
        if (aPos == 0) {
            for (int bPos = 0; bPos < poly.terms; bPos ++) {
                c.NewTerm(termArray[aPos].coef * poly.termArray[bPos].coef, 
                termArray[aPos].exp + poly.termArray[bPos].exp);
            }
            aPos ++;
        }

        else {
            // caculate the rest of terms of this * and poly, and put the result into temp
            Polynomial temp;
            for (int bPos = 0; bPos < poly.terms; bPos ++) {
                temp.NewTerm(termArray[aPos].coef * poly.termArray[bPos].coef, 
                termArray[aPos].exp + poly.termArray[bPos].exp);
            }
            c = c.Add(temp); // add the c and temp
            aPos ++;
        }
    }
    return c;
}

void Polynomial::print() const{
    for (int i = 0; i < terms; i ++) {
        cout << "exp: " << termArray[i].exp << " coef: " << termArray[i].coef << endl;
    }
}

float Polynomial::eval(float f) const{
    // set an initial sum number
    float sum = 0;
    // add the calculation of every term by the f value
    for (int i = 0; i < terms; i ++) {
        float cal = pow(f, termArray[i].exp) * termArray[i].coef;
        sum += cal;
    }

    return sum;
}

ostream & operator<<(ostream & output, Polynomial & poly) {
    for (int i = 0; i < poly.terms; i ++) {
        output << "exp: " << poly.termArray[i].exp << " coef: " << poly.termArray[i].coef << endl;
    }
    return output;
}