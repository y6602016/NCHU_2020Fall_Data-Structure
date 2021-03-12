#pragma once
#include "HChain.h"

class Polynomial;

class Term {
    friend class Polynomial;
    public:
        int coef;
        int exp;
        Term Set(int c, int e) {
            coef  = c;
            exp = e;
        }
};

class Polynomial{
    public:
        Polynomial(){
            poly = new HChain<Term>;
            poly->
        }
    private:
        HChain<Term> * poly;
};
