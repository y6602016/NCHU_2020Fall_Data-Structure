// Simple C++ class for representing a Disk (with constructors).
// @author Mike Hong <y6602016@gmail.com>

#pragma once

class Disk {
    public:
        // the constructor of Disk
        Disk(double r);
        // get the value of radius of Disk
        double getRadius() const;
    private:
        // Disk with different radius, the disk with smaller radius is 
        // on the one with larger radius;
        double radius; 
};
