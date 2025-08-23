#pragma once

#include <iostream>
#include <variant>


#define ESC "\x1b"
#define CSI "\x1b["
#define CLS "\x1b[2J" // Clear Screen
#define SSB "\x1b[3J" // Scroll Screen Buffer
#define HIDE_CURSOR "\x1b[?25l" // Hide cursor
#define SHOW_CURSOR "\x1b[?25h" // Show cursor
#define TL "\x1b[H" // Top Left (0,0)


namespace sista {
    enum class ForegroundColor: int {
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37
    };
    enum class BackgroundColor: int {
        BLACK = 40,
        RED = 41,
        GREEN = 42,
        YELLOW = 43,
        BLUE = 44,
        MAGENTA = 45,
        CYAN = 46,
        WHITE = 47
    };
    enum class Attribute: int {
        RESET = 0,
        BRIGHT = 1,
        FAINT = 2,
        ITALIC = 3,
        UNDERSCORE = 4,
        BLINK = 5,
        RAPID_BLINK = 6,
        REVERSE = 7,
        HIDDEN = 8,
        STRIKETHROUGH = 9
    };
    struct RGBColor {
        unsigned short int red;
        unsigned short int green;
        unsigned short int blue;

        RGBColor();
        RGBColor(unsigned short int, unsigned short int, unsigned short int);
    };

    void setForegroundColor(ForegroundColor);
    void setBackgroundColor(BackgroundColor);
    void setAttribute(Attribute);
    void resetAttribute(Attribute);

    void resetAnsi();

    inline void setForegroundColor(RGBColor);
    inline void setBackgroundColor(RGBColor);
    void setForegroundColor(unsigned short int, unsigned short int, unsigned short int);
    void setBackgroundColor(unsigned short int, unsigned short int, unsigned short int);
    void setForegroundColor(unsigned short int);
    void setBackgroundColor(unsigned short int);

    enum class ScreenMode: int {
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

    void setScreenMode(ScreenMode);
    void unsetScreenMode(ScreenMode);

    struct ANSISettings {
        std::variant<ForegroundColor, RGBColor> foregroundColor;
        std::variant<BackgroundColor, RGBColor> backgroundColor;
        Attribute attribute;

        ANSISettings();
        ANSISettings(const RGBColor&, const RGBColor&, const Attribute&);
        ANSISettings(const ForegroundColor&, const BackgroundColor&, const Attribute&);
        ANSISettings(const RGBColor&, const BackgroundColor&, const Attribute&);
        ANSISettings(const ForegroundColor&, const RGBColor&, const Attribute&);

        void apply() const;
    };
};
