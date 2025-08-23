#pragma once

#include "ansi.hpp" // ESC, CSI
#include "coordinates.hpp" // Coordinates, <utility>


#define CHA 'H' // "Cursor Horizontal Absolute"
#define VPA 'd' // "Vertical Position Absolute"


namespace sista {
    void clearScreen(bool spaces=true);

    enum class EraseScreen: int {
        FROM_CURSOR_TO_END = 0,
        FROM_CURSOR_TO_BEGINNING = 1,
        ENTIRE_SCREEN = 2,
        ERASE_SAVED_LINES = 3,
    };
    enum class EraseLine: int {
        LINE_FROM_CURSOR_TO_END = 0,
        LINE_FROM_CURSOR_TO_BEGINNING = 1,
        ENTIRE_LINE = 2,
    };
    enum class MoveCursor: char {
        UP = 'A',
        DOWN = 'B',
        RIGHT = 'C',
        LEFT = 'D',
        BEGINNING_OF_NEXT_LINE = 'E',
        BEGINNING_OF_PREVIOUS_LINE = 'F',
        HORIZONTAL_ABSOLUTE = 'G'
    };
    enum class MoveCursorDEC: int {
        SAVE_CURSOR_POSITION = 7,
        RESTORE_CURSOR_POSITION = 8
    };
    enum class MoveCursorSCO: char {
        SCO_SAVE_CURSOR_POSITION = 's',
        SCO_RESTORE_CURSOR_POSITION = 'u'
    };

    struct Cursor {
    private:
        const static unsigned short int offset_y;
        const static unsigned short int offset_x;

    public:
        Cursor();
        ~Cursor();

        void goTo(unsigned short int, unsigned short int) const;
        void goTo(sista::Coordinates) const;

        void eraseScreen(EraseScreen) const;
        void eraseLine(EraseLine, bool=true) const;

        void move(MoveCursor, unsigned short int) const;
        void move(MoveCursorDEC) const;
        void move(MoveCursorSCO) const;
    };
};
