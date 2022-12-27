#pragma once

#include "ANSI-Settings.hpp" // ESC, CSI
#include "coordinates.hpp" // Coord, Coordinates, <utility>

const std::string ESC_(ESC);
const std::string CSI_(CSI);

#define CHA_ 'H' // "Cursor Horizontal Absolute"
#define VPA_ 'd' // "Vertical Position Absolute"


struct Cursor {
    int x;
    int y;

    Cursor(): x(0), y(0) {
        std::cout << CSI_ << "?25l"; // Hide cursor
        this->set(0, 0);
    }
    ~Cursor() {
        std::cout << CSI_ << "?25h"; // Show cursor
    }

    void set(int y_, int x_) {
        std::cout << CSI_ << y_ << ";" << x_ << CHA_;
    }
    void set(sista::Coordinates coordinates_) {
        this->set(coordinates_.y + 3, coordinates_.x + 2);
    }
};