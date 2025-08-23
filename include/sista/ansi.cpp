#include "ansi.hpp" // ForegroundColor, BackgroundColor, Attribute, ANSISettings
#include <iostream>


namespace sista {
    RGBColor::RGBColor() : red(0), green(0), blue(0) {}
    RGBColor::RGBColor(unsigned short int red, unsigned short int green, unsigned short int blue) : red(red), green(green), blue(blue) {}

    void setForegroundColor(ForegroundColor color) {
        std::cout << CSI << static_cast<int>(color) << "m";
    }
    void setBackgroundColor(BackgroundColor color) {
        std::cout << CSI << static_cast<int>(color) << "m";
    }
    void setAttribute(Attribute attribute) {
        std::cout << CSI << static_cast<int>(attribute) << "m";
    }
    void resetAttribute(Attribute attribute) {
        if (attribute == Attribute::BRIGHT) {
            std::cout << CSI << static_cast<int>(attribute) + 21 << "m";
            return;
        }
        std::cout << CSI << static_cast<int>(attribute) + 20 << "m";
    }

    void resetAnsi() {
        setAttribute(Attribute::RESET);
        setForegroundColor(ForegroundColor::WHITE);
        setBackgroundColor(BackgroundColor::BLACK);
    }

    inline void setForegroundColor(RGBColor rgbcolor) {
        setForegroundColor(rgbcolor.red, rgbcolor.green, rgbcolor.blue);
    }
    inline void setBackgroundColor(RGBColor rgbcolor) {
        setBackgroundColor(rgbcolor.red, rgbcolor.green, rgbcolor.blue);
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

    void setScreenMode(ScreenMode mode) {
        std::cout << CSI << '=' << static_cast<int>(mode) << 'h';
    }
    void unsetScreenMode(ScreenMode mode) {
        std::cout << CSI << '=' << static_cast<int>(mode) << 'l';
    }

    ANSISettings::ANSISettings() {
        foregroundColor = ForegroundColor::WHITE;
        backgroundColor = BackgroundColor::BLACK;
        attribute = Attribute::RESET;
    }
    ANSISettings::ANSISettings(const RGBColor& foregroundColor_, const RGBColor& backgroundColor_, const Attribute& attribute_)
        : foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}
    ANSISettings::ANSISettings(const ForegroundColor& foregroundColor_, const BackgroundColor& backgroundColor_, const Attribute& attribute_)
        : foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}
    ANSISettings::ANSISettings(const ForegroundColor& foregroundColor_, const RGBColor& backgroundColor_, const Attribute& attribute_)
        : foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}
    ANSISettings::ANSISettings(const RGBColor& foregroundColor_, const BackgroundColor& backgroundColor_, const Attribute& attribute_)
        : foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}

    void ANSISettings::apply() const {
        setAttribute(Attribute::RESET);
        setAttribute(attribute);
        if (std::holds_alternative<ForegroundColor>(foregroundColor)) {
            setForegroundColor(std::get<ForegroundColor>(foregroundColor));
        } else {
            setForegroundColor(std::get<RGBColor>(foregroundColor));
        }
        if (std::holds_alternative<BackgroundColor>(backgroundColor)) {
            setBackgroundColor(std::get<BackgroundColor>(backgroundColor));
        } else {
            setBackgroundColor(std::get<RGBColor>(backgroundColor));
        }
    }
};
