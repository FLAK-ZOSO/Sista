#include "cursor.hpp" // Cursor, <iostream>


namespace sista {
    void clearScreen() {
        clearScreen(true);
    }
    void clearScreen(bool spaces) {
        if (spaces) {
            std::cout << CLS; // Clear screen
            std::cout << SSB; // Clear scrollback buffer
        }
        std::cout << TL; // Move cursor to top-left corner
    }

    Cursor::Cursor(): x(0), y(0) {
        std::cout << HIDE_CURSOR;
        clearScreen();
    }
    Cursor::~Cursor() {
        ANSI::reset();
        std::cout << SHOW_CURSOR;
        clearScreen();
    }

    void Cursor::set(unsigned short int y_, unsigned short int x_) {
        std::cout << CSI << y_ << ";" << x_ << CHA;
    }
    void Cursor::set(sista::Coordinates coordinates_) {
        this->set(coordinates_.y + 3, coordinates_.x + 2);
    }

    void Cursor::eraseScreen(EraseScreen eraseScreen_) {
        std::cout << CSI << eraseScreen_ << "J";
    }
    void Cursor::eraseLine(EraseLine eraseLine_, bool moveCursor=true) {
        std::cout << CSI << eraseLine_ << "K";
        if (moveCursor) {
            this->set(this->y, 0);
            std::cout << '\r';
        }
    }

    void Cursor::move(MoveCursor moveCursor_, unsigned short int n=1) {
        std::cout << CSI << n << (char)moveCursor_;
    }
    void Cursor::move(MoveCursorDEC moveCursorDEC_) {
        std::cout << ESC << ' ' << moveCursorDEC_;
    }
    void Cursor::move(MoveCursorSCO moveCursorSCO_) {
        std::cout << ESC << ' ' << moveCursorSCO_;
    }
};