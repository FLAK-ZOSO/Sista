#pragma once

#include <string>
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
#define CR_ '\x0d' // Carriage Return
#define DEL '\x7f' // Delete

#define SS "\33[2J\33[H" // Scroll Screen
#define CLS "\33[2J" // Clear Screen
#define HIDE_CURSOR "\33[?25l" // Hide cursor
#define SHOW_CURSOR "\33[?25h" // Show cursor


namespace ANSI {
    enum ForegroundColor {
        F_BLACK = 30,
        F_RED = 31,
        F_GREEN = 32,
        F_YELLOW = 33,
        F_BLUE = 34,
        F_MAGENTA = 35,
        F_CYAN = 36,
        F_WHITE = 37
    };
    enum BackgroundColor {
        B_BLACK = 40,
        B_RED = 41,
        B_GREEN = 42,
        B_YELLOW = 43,
        B_BLUE = 44,
        B_MAGENTA = 45,
        B_CYAN = 46,
        B_WHITE = 47
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
        std::string command = CSI + std::to_string(color) + "m";
        std::cout << command;
    }
    void setBackgroundColor(BackgroundColor color) {
        std::string command = CSI + std::to_string(color) + "m";
        std::cout << command;
    }
    void setAttribute(Attribute attribute) {
        std::string command = CSI + std::to_string(attribute) + "m";
        std::cout << command;
    }

    void reset() {
        setAttribute(Attribute::RESET);
        setForegroundColor(ForegroundColor::F_WHITE);
        setBackgroundColor(BackgroundColor::B_BLACK);
    }

    struct Settings {
        ForegroundColor foregroundColor;
        BackgroundColor backgroundColor;
        Attribute attribute;

        Settings() {
            foregroundColor = ForegroundColor::F_WHITE;
            backgroundColor = BackgroundColor::B_BLACK;
            attribute = Attribute::RESET;
        }
        Settings(ForegroundColor foregroundColor_, BackgroundColor backgroundColor_, Attribute attribute_): foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}
        Settings(ForegroundColor& foregroundColor_, BackgroundColor& backgroundColor_, Attribute& attribute_, bool _by_reference): foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}

        void apply() {
            setForegroundColor(foregroundColor);
            setBackgroundColor(backgroundColor);
            setAttribute(attribute);
        }
    };
};