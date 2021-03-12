// C++ class for a "Tower" in a Tower of Hanoi assignment of Sata Structure.
// @author Mike Hong <y6602016@gmail.com>

#pragma once
#include <vector>
#include "Stack.h"

class Tower {
    // operator overloading for print out the stack by using <<
    friend ostream & operator<<(ostream & out, const Tower & tower);
    public:
        Tower(); // the constructor of Tower
        void Action(); // Start to move the disks by following the rule
    private:
        vector<Stack> stacks_;
    private:
        void move_disk(Stack & s1, Stack & s2); // move the disk at the end of recursion
        void move(int start, int end, Stack & origin, Stack & target, Stack & spare); // recursively move
};
