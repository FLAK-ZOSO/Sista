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

    enum EraseScreen {
        FROM_CURSOR_TO_END = 0,
        FROM_CURSOR_TO_BEGINNING = 1,
        ENTIRE_SCREEN = 2,
        ERASE_SAVED_LINES = 3,
    };
    enum EraseLine {
        LINE_FROM_CURSOR_TO_END = 0,
        LINE_FROM_CURSOR_TO_BEGINNING = 1,
        ENTIRE_LINE = 2,
    };
    enum MoveCursor {
        UP = (int)'A',
        DOWN = (int)'B',
        RIGHT = (int)'C',
        LEFT = (int)'D',
        BEGINNING_OF_NEXT_LINE = (int)'E',
        BEGINNING_OF_PREVIOUS_LINE = (int)'F',
        HORIZONTAL_ABSOLUTE = (int)'G'
    };
    enum MoveCursorDEC {
        SAVE_CURSOR_POSITION = 7,
        RESTORE_CURSOR_POSITION = 8
    };
    enum MoveCursorSCO {
        SCO_SAVE_CURSOR_POSITION = (int)'s',
        SCO_RESTORE_CURSOR_POSITION = (int)'u'
    };

    struct Cursor {
        unsigned short int x;
        unsigned short int y;

        Cursor(): x(0), y(0) {
            std::cout << HIDE_CURSOR;
            clearScreen();
        }
        ~Cursor() {
            ANSI::reset();
            std::cout << SHOW_CURSOR;
            clearScreen();
        }

        void set(unsigned short int y_, unsigned short int x_) {
            std::cout << CSI << y_ << ";" << x_ << CHA;
        }
        void set(sista::Coordinates coordinates_) {
            this->set(coordinates_.y + 3, coordinates_.x + 2);
        }

        void eraseScreen(EraseScreen eraseScreen_) {
            std::cout << CSI << eraseScreen_ << "J";
        }
        void eraseLine(EraseLine eraseLine_, bool moveCursor=true) {
            std::cout << CSI << eraseLine_ << "K";
            if (moveCursor) {
                this->set(this->y, 0);
                std::cout << '\r';
            }
        }

        void move(MoveCursor moveCursor_, unsigned short int n=1) {
            std::cout << CSI << n << (char)moveCursor_;
        }
        void move(MoveCursorDEC moveCursorDEC_) {
            std::cout << ESC << ' ' << moveCursorDEC_;
        }
        void move(MoveCursorSCO moveCursorSCO_) {
            std::cout << ESC << ' ' << moveCursorSCO_;
        }
    };
};