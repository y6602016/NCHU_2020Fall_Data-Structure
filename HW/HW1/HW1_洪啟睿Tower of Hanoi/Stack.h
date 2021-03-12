// C++ class for a "stack" in a Tower of Hanoi assignment of Sata Structure.
// @author Mike Hong <y6602016@gmail.com>

#pragma once
#include <vector>
#include <iostream>
#include "Disk.h"
using namespace std;


class Stack {
    // operator overloading for print out the disks on the Stack by using <<
    friend ostream & operator<<(ostream & out, const Stack & stack);
    public:
        void push_back(const Disk & disk); // add a disk on the top of the Stack
        Disk removeTop(); // remove the disk on the top of the Stack
        Disk & peekTop(); // get the disk to be removed
        int size() const; // get the size of the Stack

    private:
        vector<Disk> Disks_; // use vector as container to arrange disks
};