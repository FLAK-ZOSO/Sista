#pragma once
#include <iostream>


namespace color {
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
        std::cout << "\033[" << color << "m";
    }
    void setBackgroundColor(BackgroundColor color) {
        std::cout << "\033[" << color << "m";
    }
    void setAttribute(Attribute attribute) {
        std::cout << "\033[" << attribute << "m";
    }

    void reset() {
        setAttribute(Attribute::RESET);
        setForegroundColor(ForegroundColor::WHITE);
        setBackgroundColor(BackgroundColor::BLACK);
    }
};