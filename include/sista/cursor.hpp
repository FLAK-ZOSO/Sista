#pragma once

#include "ANSI-Settings.hpp" // ESC, CSI
#include "coordinates.hpp" // Coord, Coordinates, <utility>


#define CHA 'H' // "Cursor Horizontal Absolute"
#define VPA 'd' // "Vertical Position Absolute"


namespace sista {
    void clearScreen();
    void clearScreen(bool);

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

        Cursor();
        ~Cursor();

        void set(unsigned short int, unsigned short int);
        void set(sista::Coordinates);

        void eraseScreen(EraseScreen);
        void eraseLine(EraseLine, bool);

        void move(MoveCursor, unsigned short int);
        void move(MoveCursorDEC);
        void move(MoveCursorSCO);
    };
};