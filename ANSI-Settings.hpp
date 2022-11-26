#pragma once
#include <iostream>

#define ESC "\x1b"
#define CSI "\x1b["
#define OSC "\x1b]"
#define BACKSLASH "\\"
#define STRING_TERMINATOR "\x1b\\"

#define BEL '\x07' // Bell
#define BS '\x08' // Backspace
#define TAB '\x09' // Tab
#define LF '\x0a' // Line Feed
#define VT '\x0b' // Vertical Tab
#define FF '\x0c' // Form Feed
#define CR '\x0d' // Carriage Return
#define DEL '\x7f' // Delete

#define SS "\33[2J\33[H" // Scroll Screen


namespace ANSI {
    enum ForegroundColor {
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37
    };
    enum BackgroundColor {
        BLACK = 40,
        RED = 41,
        GREEN = 42,
        YELLOW = 43,
        BLUE = 44,
        MAGENTA = 45,
        CYAN = 46,
        WHITE = 47
    };
    enum Attribute {
        RESET = 0,
        BRIGHT = 1,
        DIM = 2,
        UNDERSCORE = 4,
        BLINK = 5,
        REVERSE = 7,
        HIDDEN = 8
    };

    void setForegroundColor(ForegroundColor color) {
        std::cout << ESC << color << "m";
    }
    void setBackgroundColor(BackgroundColor color) {
        std::cout << ESC << color << "m";
    }
    void setAttribute(Attribute attribute) {
        std::cout << ESC << attribute << "m";
    }

    void reset() {
        setAttribute(Attribute::RESET);
        setForegroundColor(ForegroundColor::WHITE);
        setBackgroundColor(BackgroundColor::BLACK);
    }
};