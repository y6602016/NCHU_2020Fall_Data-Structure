#include "String.h"
#include <iostream>
#include <cstring>
using namespace std;

String::String(char * init) {
    str = new char[strlen(init)];
    strcpy(str, init);
    f = new int[strlen(init)];
    fill(f, f + strlen(init), 0); // Remember to initialize!!!!!
}

int String::Length() {
    return strlen(str);
}

void String::FailureFunction() {
    int lengthP = Length();
    f[0] = -1;
    for (int j = 1; j < lengthP; j ++) {
        int i = f[j - 1];
        while ((*(str + j) != *(str + i + 1)) && (i >= 0)) {
            i = f[i];
        }
        if (*(str + j) == *(str + i + 1)) {
            f[i] = i + 1;
        }
        else {
            f[j] = -1;
        }
    }
}

int String::FastFind(String pat) {
    int posP = 0, posS = 0;
    int lengthP = pat.Length(), lengthS = Length();
    while ((posP < lengthP) && (posS < lengthS)) {
        if (pat.str[posP] ==  str[posS]) {
            posP ++; 
            posS ++;
        }

        else {
            if (posP == 0) {
                posS++;
            }
            else {
                posP = pat.f[posP - 1] + 1;
            }
        }
    }
    if (posP < lengthP) {
        return -1;
    }
    else {
        return posS - lengthP;
    }
}

String String::Concat(String t) {
    int length_t = t.Length();
    int newSize = length_t + Length();
    char * newString = new char[newSize];
    strcpy(newString, str); // copy the *this to the new array
    strcat(newString, t.str); // add t.str to end of the new array
    String combined(newString);
    cout << newString << endl;
    return combined;
}

