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

    enum ScreenMode {
        MONOCROME_TEXT_40_25 = 0,
        COLOR_TEXT_40_25 = 1,
        MONOCROME_TEXT_80_25 = 2,
        COLOR_TEXT_80_25 = 3,
        FOUR_COLORS_GRAPHICS_320_200 = 4,
        MONOCROME_GRAPHICS_320_200 = 5,
        MONOCROME_GRAPHICS_640_200 = 6,
        LINE_WRAPPING = 7,
        COLOR_GRAPHICS_320_200 = 13,
        COLOR_16_COLORS_GRAPHICS_640_200 = 14,
        MONOCROME_2_COLORS_GRAPHICS_640_350 = 15,
        COLOR_16_COLORS_GRAPHICS_640_350 = 16,
        MONOCROME_2_COLORS_GRAPHICS_640_480 = 17,
        COLOR_16_COLORS_GRAPHICS_640_480 = 18,
        COLOR_256_COLORS_GRAPHICS_320_200 = 19
    };

    void setScreenMode(ScreenMode mode) {
        std::cout << CSI << '=' << mode << 'h';
    }
    void unsetScreenMode(ScreenMode mode) {
        std::cout << CSI << '=' << mode << 'l';
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