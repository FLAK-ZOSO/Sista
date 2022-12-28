#pragma once

#include "ANSI-Settings.hpp" // ESC, CSI
#include "coordinates.hpp" // Coord, Coordinates, <utility>


#define CHA 'H' // "Cursor Horizontal Absolute"
#define VPA 'd' // "Vertical Position Absolute"


namespace sista {
    void clearScreen(bool spaces=true) {
        if (spaces) {
            std::cout << CLS; // Clear screen
            std::cout << SSB; // Clear scrollback buffer
        }
        std::cout << TL; // Move cursor to top-left corner
    }

    struct Cursor {
        int x;
        int y;

        Cursor(): x(0), y(0) {
            std::cout << HIDE_CURSOR;
            clearScreen();
        }
        ~Cursor() {
            ANSI::reset();
            std::cout << SHOW_CURSOR;
            clearScreen();
        }

        void set(int y_, int x_) {
            std::cout << CSI << y_ << ";" << x_ << CHA;
        }
        void set(sista::Coordinates coordinates_) {
            this->set(coordinates_.y + 3, coordinates_.x + 2);
        }
    };
};