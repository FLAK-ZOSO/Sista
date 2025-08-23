#include "coordinates.hpp"
#include <functional> // std::hash

namespace sista {
    Coordinates::Coordinates(): y(0), x(0) {} // Constructor
    Coordinates::Coordinates(unsigned short y_, unsigned short x_): y(y_), x(x_) {} // Constructor

    Coordinates Coordinates::fromPair(const std::pair<unsigned short, unsigned short>& p) {
        return Coordinates(p.first, p.second);
    }
    std::pair<unsigned short, unsigned short> Coordinates::toPair() const {
        return std::make_pair(y, x);
    }

    bool Coordinates::operator==(const Coordinates& other) const {
        return (y == other.y && x == other.x);
    }
    bool Coordinates::operator!=(const Coordinates& other) const {
        return (y != other.y || x != other.x);
    }
    bool Coordinates::operator<(const Coordinates& other) const {
        if (y != other.y)
            return y < other.y;
        return x < other.x;
    }
    Coordinates Coordinates::operator+(const Coordinates& other) const {
        return Coordinates(y + other.y, x + other.x);
    }
    Coordinates Coordinates::operator-(const Coordinates& other) const {
        return Coordinates(y - other.y, x - other.x);
    }
    Coordinates Coordinates::operator*(const unsigned short multiplier) const {
        return Coordinates(y*multiplier, x*multiplier);
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

namespace std {
    template<>
    struct hash<sista::Coordinates> {
        std::size_t operator()(const sista::Coordinates& c) const noexcept {
            return (std::size_t(c.y) << 16) ^ std::size_t(c.x);
        }
    };
};
