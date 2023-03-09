#pragma once

#include <iostream>


#define ESC "\x1b"
#define CSI "\x1b["
#define CLS "\x1b[2J" // Clear Screen
#define SSB "\x1b[3J" // Scroll Screen Buffer
#define HIDE_CURSOR "\x1b[?25l" // Hide cursor
#define SHOW_CURSOR "\x1b[?25h" // Show cursor
#define TL "\x1b[H" // Top Left (0,0)


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
        FAINT = 2,
        ITALIC = 3,
        UNDERSCORE = 4,
        BLINK = 5,
        REVERSE = 7,
        HIDDEN = 8,
        STRIKETHROUGH = 9
    };

    void setForegroundColor(ForegroundColor color) {
        std::cout << CSI << color << "m";
    }
    void setBackgroundColor(BackgroundColor color) {
        std::cout << CSI << color << "m";
    }
    void setAttribute(Attribute attribute) {
        std::cout << CSI << attribute << "m";
    }
    void resetAttribute(Attribute attribute) {
        if (attribute == Attribute::BRIGHT) {
            std::cout << CSI << attribute + 21 << "m";
            return;
        }
        std::cout << CSI << attribute + 20 << "m";
    }

    void reset() {
        setAttribute(Attribute::RESET);
        setForegroundColor(ForegroundColor::F_WHITE);
        setBackgroundColor(BackgroundColor::B_BLACK);
    }

    void setForegroundColor(unsigned short int red, unsigned short int green, unsigned short int blue) {
        std::cout << CSI << "38;2;" << red << ";" << green << ";" << blue << "m";
    }
    void setBackgroundColor(unsigned short int red, unsigned short int green, unsigned short int blue) {
        std::cout << CSI << "48;2;" << red << ";" << green << ";" << blue << "m";
    }
    void setForegroundColor(unsigned short int color) {
        std::cout << CSI << "38;5;" << color << "m";
    }
    void setBackgroundColor(unsigned short int color) {
        std::cout << CSI << "48;5;" << color << "m";
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
            setAttribute(Attribute::RESET);
            setAttribute(attribute);
            setForegroundColor(foregroundColor);
            setBackgroundColor(backgroundColor);
        }
    };
};