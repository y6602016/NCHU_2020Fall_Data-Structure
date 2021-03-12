// C++ class for a "Tower" in a Tower of Hanoi assignment of Sata Structure.
// @author Mike Hong <y6602016@gmail.com>

#include "Tower.h"
#include "Disk.h"
#include "Stack.h"
#include <iostream>
using namespace std;

Tower::Tower() {
    // The initial default state has three stacks and four disks.

    // Create the three empty Stacks
    for (int i = 0; i < 3; i ++) {
        Stack stackOfDisks;
        stacks_.push_back(stackOfDisks);
    }

    // Create the four disk, placing each on the [0]th stack:
    // - A disk1 of length=4, on the bottom
    // - A disk2 of length=3, on top of the last disk
    // - A disk3 of length=2, on top of the last disk
    // - A disk4 of length=1 at the very top
    Disk disk1(4);
    stacks_[0].push_back(disk1);

    Disk disk2(3);
    stacks_[0].push_back(disk2);

    Disk disk3(2);
    stacks_[0].push_back(disk3);

    Disk disk4(1);
    stacks_[0].push_back(disk4);
}

// Move a Cube from Stack `s1` to Stack `s2`
void Tower::move_disk(Stack & s1, Stack & s2) {
    Disk disk = s1.removeTop();
    s2.push_back(disk);
}

// Move the disks in the range [start...end] from `source` to `target`, using spare as a spare spot:
void Tower::move(int start, int end, Stack & origin, Stack & target, Stack & spare) {
    // Check if we are at the end of the recursion, it we are, use move_disk:
    if (start == end) {
        move_disk(origin, target);
        // cout << *this << endl;
    }
    else {
        // otherwise, use the recursion
        move(start + 1, end, origin, spare, target);
        move(start, start, origin, target, spare);
        move(start + 1, end, spare, target, origin);
    }
}

void Tower::Action() {
    move(0, stacks_[0].size() - 1, //< Move the entire set of cubes, [0 .. size-1]
    stacks_[0], //< Source stack is [0]
    stacks_[2], //< Target stack is [2]
    stacks_[1] //< Spare stack is [1]
    );
}

ostream & operator<<(ostream & out, const Tower & tower) {
    for (int i = 0; i < tower.stacks_.size(); i ++) {
        out << "Stack[" << i << ", " << &tower.stacks_[i] << "]: " << tower.stacks_[i] << endl;
    }
    return out;
}