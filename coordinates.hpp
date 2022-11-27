#pragma once
#include <utility>


typedef std::pair<unsigned short, unsigned short> Coord; // Coordinates made into a pair


struct Coordinates { // 2D coordinates
    unsigned short y; // y coordinate
    unsigned short x; // x coordinate

    Coordinates(): y(0), x(0) {} // Constructor
    Coordinates(unsigned short y, unsigned short x): y(y), x(x) {} // Constructor
    Coordinates(Coord coord): y(coord.first), x(coord.second) {} // Constructor

    bool operator==(const Coordinates& other) const { // == operator overload
        return (y == other.y && x == other.x);
    }
}; // field[y][x] - y is the row, x is the column