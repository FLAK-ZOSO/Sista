#include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings


namespace ANSI {
    RGBColor::RGBColor() : red(0), green(0), blue(0) {}
    RGBColor::RGBColor(unsigned short int red, unsigned short int green, unsigned short int blue) : red(red), green(green), blue(blue) {}

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
        std::cout << CSI << '=' << mode << 'h';
    }
    void unsetScreenMode(ScreenMode mode) {
        std::cout << CSI << '=' << mode << 'l';
    }

    Settings::Settings() {
        foregroundColor = ForegroundColor::F_WHITE;
        backgroundColor = BackgroundColor::B_BLACK;
        attribute = Attribute::RESET;
    }
    Settings::Settings(RGBColor foregroundColor_, RGBColor backgroundColor_, Attribute attribute_) : foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}
    Settings::Settings(RGBColor& foregroundColor_, RGBColor& backgroundColor_, Attribute& attribute_, bool _by_reference) : foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}
    Settings::Settings(ForegroundColor foregroundColor_, BackgroundColor backgroundColor_, Attribute attribute_) : foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}
    Settings::Settings(ForegroundColor& foregroundColor_, BackgroundColor& backgroundColor_, Attribute& attribute_, bool _by_reference) : foregroundColor(foregroundColor_), backgroundColor(backgroundColor_), attribute(attribute_) {}

    void Settings::apply() {
        setAttribute(Attribute::RESET);
        setAttribute(attribute);
        try {
            setForegroundColor(std::get<ForegroundColor>(foregroundColor));
        } catch (const std::bad_variant_access& ex) {
            setForegroundColor(std::get<RGBColor>(foregroundColor));
        }
        try {
            setBackgroundColor(std::get<BackgroundColor>(backgroundColor));
        } catch (const std::bad_variant_access& ex) {
            setBackgroundColor(std::get<RGBColor>(backgroundColor));
        }
    }
};