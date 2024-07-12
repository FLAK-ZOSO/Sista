#include "coordinates.hpp"

namespace sista {
    Coordinates::Coordinates(): y(0), x(0) {} // Constructor
    Coordinates::Coordinates(unsigned short y_, unsigned short x_): y(y_), x(x_) {} // Constructor
    Coordinates::Coordinates(Coord coord): y(coord.first), x(coord.second) {} // Constructor

    bool Coordinates::operator==(const Coordinates& other) const {
        return (y == other.y && x == other.x);
    }
    bool Coordinates::operator!=(const Coordinates& other) const {
        return (y != other.y || x != other.x);
    }
    Coordinates Coordinates::operator+(const Coordinates& other) const {
        return Coordinates(y + other.y, x + other.x);
    }
    Coordinates Coordinates::operator-(const Coordinates& other) const {
        return Coordinates(y - other.y, x - other.x);
    }
    Coordinates Coordinates::operator+=(const Coordinates& other) {
        y += other.y;
        x += other.x;
        return *this;
    }
    Coordinates Coordinates::operator-=(const Coordinates& other) {
        y -= other.y;
        x -= other.x;
        return *this;
    }
};