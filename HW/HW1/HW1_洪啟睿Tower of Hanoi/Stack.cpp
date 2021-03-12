// C++ class for a "stack" in a Tower of Hanoi assignment of Sata Structure.
// @author Mike Hong <y6602016@gmail.com>

#include "Stack.h"
#include <iostream>

void Stack::push_back(const Disk & disk) {
    // avoid putting a smaller disk on the larger one
    if ((size() > 0) && (disk.getRadius() > peekTop().getRadius())) {
        cout << "A smaller disk cannot be placed on top of a larger disk." << endl;
        return;
    }
    Disks_.push_back(disk);
}

Disk Stack::removeTop() {
    Disk disk = peekTop();
    Disks_.pop_back();
    return disk;
}

Disk & Stack::peekTop() {
    return Disks_[size() - 1];
}

int Stack::size() const{
    return Disks_.size();
}

ostream & operator<<(ostream & out, const Stack & stack) {
    int i;
    for (i = 0; i < stack.size() - 1; i ++) {
        out << stack.Disks_[i].getRadius() << " ";
    }
    if (stack.size() > 0) {
        out << stack.Disks_[i].getRadius();
    }
    return out;
}