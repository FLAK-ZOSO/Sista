/** \file ansi.cpp
 *  \brief Implementation of ANSI functions and classes.
 * 
 *  This file contains the implementation of functions and classes for handling ANSI escape codes,
 *  including setting foreground and background colors, text attributes, and screen modes.
 * 
 *  The implementation includes support for both standard colors and RGB colors, as well as
 *  managing ANSI settings through the `ANSISettings` class.
 * 
 *  The code is designed to work with C++17 and later standards.
 * 
 * \author FLAK-ZOSO
 * \date 2022-2025
 * \version 3.0.0
 * \note Many niche features are not implemented, see references for more details.
 * \note Not all terminals support all ANSI features.
 * \see https://en.wikipedia.org/wiki/ANSI_escape_code
 * \see https://gist.github.com/ConnerWill/d4b6c776b509add763e17f9f113fd25b
 * \copyright GNU General Public License v3.0
 */
#include "ansi.hpp"
#include <iostream>
#include <sstream>


namespace sista {
    RGBColor::RGBColor() : red(0), green(0), blue(0) {}
    RGBColor::RGBColor(unsigned char red, unsigned char green, unsigned char blue) : red(red), green(green), blue(blue) {}

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

    void setForegroundColor(const RGBColor& rgbcolor) {
        setForegroundColor(rgbcolor.red, rgbcolor.green, rgbcolor.blue);
    }
    void setBackgroundColor(const RGBColor& rgbcolor) {
        setBackgroundColor(rgbcolor.red, rgbcolor.green, rgbcolor.blue);
    }
    void setForegroundColor(unsigned char red, unsigned char green, unsigned char blue) {
        std::cout << CSI << "38;2;" << static_cast<short int>(red) << ";";
        std::cout << static_cast<short int>(green) << ";";
        std::cout << static_cast<short int>(blue) << "m";
    }
    void setBackgroundColor(unsigned char red, unsigned char green, unsigned char blue) {
        std::cout << CSI << "48;2;" << static_cast<short int>(red) << ";";
        std::cout << static_cast<short int>(green) << ";";
        std::cout << static_cast<short int>(blue) << "m";
    }
    void setForegroundColor(unsigned char color) {
        std::cout << CSI << "38;5;" << color << "m";
    }
    void setBackgroundColor(unsigned char color) {
        std::cout << CSI << "48;5;" << color << "m";
    }

    std::string fgColorStr(ForegroundColor color) {
        return CSI + std::to_string(static_cast<int>(color)) + "m";
    }
    std::string bgColorStr(BackgroundColor color) {
        return CSI + std::to_string(static_cast<int>(color)) + "m";
    }
    std::string attrStr(Attribute attribute) {
        return CSI + std::to_string(static_cast<int>(attribute)) + "m";
    }
    std::string fgColorStr(const RGBColor& color) {
        std::ostringstream oss;
        oss << CSI << "38;2;" << static_cast<short int>(color.red) << ";"
            << static_cast<short int>(color.green) << ";"
            << static_cast<short int>(color.blue) << "m";
        return oss.str();
    }
    std::string bgColorStr(const RGBColor& color) {
        std::ostringstream oss;
        oss << CSI << "48;2;" << static_cast<short int>(color.red) << ";"
            << static_cast<short int>(color.green) << ";"
            << static_cast<short int>(color.blue) << "m";
        return oss.str();
    }
    std::string fgColorStr(unsigned char red, unsigned char green, unsigned char blue) {
        std::ostringstream oss;
        oss << CSI << "38;2;" << static_cast<short int>(red) << ";"
            << static_cast<short int>(green) << ";"
            << static_cast<short int>(blue) << "m";
        return oss.str();
    }
    std::string bgColorStr(unsigned char red, unsigned char green, unsigned char blue) {
        std::ostringstream oss;
        oss << CSI << "48;2;" << static_cast<short int>(red) << ";"
            << static_cast<short int>(green) << ";"
            << static_cast<short int>(blue) << "m";
        return oss.str();
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
        if (std::holds_alternative<Attribute>(attribute)) {
            setAttribute(std::get<Attribute>(attribute));
        } else {
            const auto& attrs = std::get<std::bitset<10>>(attribute);
            for (size_t i = 0; i < attrs.size(); ++i) {
                if (attrs.test(i)) {
                    setAttribute(static_cast<Attribute>(i));
                }
            }
        }
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
