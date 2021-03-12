// Simple C++ class for representing a Disk (with constructors).
// @author Mike Hong <y6602016@gmail.com>


#include "Disk.h"
#include <iostream>

Disk::Disk(double r) {
    radius = r;
}

double Disk::getRadius() const{
    return radius;
}
