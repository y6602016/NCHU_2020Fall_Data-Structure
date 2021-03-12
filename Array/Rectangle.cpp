#include "Rectangle.h"
#include <iostream>
using namespace std;

Rectangle::Rectangle(int h, int w) : height(h), width(w) {   
}

int Rectangle::getHeight() {
    return height;
}

int Rectangle::getWidth() {
    return width;
}

bool Rectangle::operator < (const Rectangle & right) {
    if (&right == this) {
        return false;
    }
    if ((height * width) < (right.height * right.width)) {
        return true;
    }
    else return false;
}