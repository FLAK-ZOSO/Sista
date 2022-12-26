#pragma once

#include <utility> // std::pair, std::swap

namespace sista {
    typedef std::pair<unsigned short, unsigned short> Coord; // Coordinates made into a pair [y, x]


    struct Coordinates { // 2D coordinates
        unsigned short y; // y coordinate
        unsigned short x; // x coordinate

        Coordinates(): y(0), x(0) {} // Constructor
        Coordinates(unsigned short y_, unsigned short x_): y(y_), x(x_) {} // Constructor
        Coordinates(Coord coord): y(coord.first), x(coord.second) {} // Constructor

        bool operator==(const Coordinates& other) const {
            return (y == other.y && x == other.x);
        }
        bool operator!=(const Coordinates& other) const {
            return (y != other.y || x != other.x);
        }
        Coordinates operator+(const Coordinates& other) const {
            return Coordinates(y + other.y, x + other.x);
        }
    }; // field[y][x] - y is the row, x is the column
};