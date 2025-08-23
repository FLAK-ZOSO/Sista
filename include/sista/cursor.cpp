#include "cursor.hpp" // Cursor
#include <iostream> // std::cout


namespace sista {
    const unsigned short int Cursor::offset_y = 3; // Offset for the y coordinate (empyrical)
    const unsigned short int Cursor::offset_x = 2; // Offset for the x coordinate (empyrical)

    void clearScreen(bool spaces) {
        if (spaces) {
            std::cout << CLS; // Clear screen
            std::cout << SSB; // Clear scrollback buffer
        }
        std::cout << TL; // Move cursor to top-left corner
    }

    Cursor::Cursor() {
        std::cout << HIDE_CURSOR;
        clearScreen();
    }
    Cursor::~Cursor() {
        resetAnsi();
        std::cout << SHOW_CURSOR;
        clearScreen();
    }

    void Cursor::goTo(unsigned short int y_, unsigned short int x_) const {
        std::cout << CSI << y_ << ";" << x_ << CHA;
    }
    void Cursor::goTo(sista::Coordinates coordinates_) const {
        this->goTo(coordinates_.y + offset_y, coordinates_.x + offset_x);
    }

    void Cursor::eraseScreen(EraseScreen eraseScreen_) const {
        std::cout << CSI << static_cast<int>(eraseScreen_) << "J";
    }
    void Cursor::eraseLine(EraseLine eraseLine_, bool moveCursor) const {
        std::cout << CSI << static_cast<int>(eraseLine_) << "K";
        if (moveCursor) {
            std::cout << '\r'; // Move cursor to start of line
        }
    }

    void Cursor::move(MoveCursor moveCursor_, unsigned short int n=1) const {
        std::cout << CSI << n << static_cast<char>(moveCursor_);
    }
    void Cursor::move(MoveCursorDEC moveCursorDEC_) const {
        std::cout << ESC << ' ' << static_cast<int>(moveCursorDEC_);
    }
    void Cursor::move(MoveCursorSCO moveCursorSCO_) const {
        std::cout << ESC << ' ' << static_cast<char>(moveCursorSCO_);
    }
};
