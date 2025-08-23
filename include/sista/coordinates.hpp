#pragma once

#include <utility> // std::pair, std::swap
#include <functional> // std::hash

namespace sista {
    struct Coordinates { // 2D coordinates
        unsigned short y; // y coordinate
        unsigned short x; // x coordinate

        Coordinates();
        Coordinates(unsigned short, unsigned short);
        static Coordinates fromPair(const std::pair<unsigned short, unsigned short>&);
        std::pair<unsigned short, unsigned short> toPair() const;

        bool operator==(const Coordinates&) const;
        bool operator!=(const Coordinates&) const;
        bool operator<(const Coordinates&) const;
        Coordinates operator+(const Coordinates&) const;
        Coordinates operator-(const Coordinates&) const;
        Coordinates operator*(const unsigned short) const;
        Coordinates operator+=(const Coordinates&);
        Coordinates operator-=(const Coordinates&);
    }; // field[y][x] - y is the row, x is the column
};

namespace std {
    template<>
    struct hash<sista::Coordinates> {
        std::size_t operator()(const sista::Coordinates&) const noexcept;
    };
};
