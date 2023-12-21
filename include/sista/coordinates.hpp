#pragma once

#include <utility> // std::pair, std::swap

namespace sista {
    typedef std::pair<unsigned short, unsigned short> Coord; // Coordinates made into a pair [y, x]


    struct Coordinates { // 2D coordinates
        unsigned short y; // y coordinate
        unsigned short x; // x coordinate

        Coordinates();
        Coordinates(unsigned short, unsigned short);
        Coordinates(Coord);

        bool operator==(const Coordinates&) const;
        bool operator!=(const Coordinates&) const;
        Coordinates operator+(const Coordinates&) const;
    }; // field[y][x] - y is the row, x is the column
};