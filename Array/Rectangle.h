#pragma once

class Rectangle {
    public:
        Rectangle(int h = 0 , int w = 0);
        int getHeight();
        int getWidth();
        bool operator < (const Rectangle & right);
    private:
        int xLow, yLow, height, width;
};