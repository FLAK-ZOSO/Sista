#pragma once

#include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
#include "coordinates.hpp" // Coord, Coordinates, <utility>

namespace sista {
    class Border { // Border class - represents a brick of the border [parent class]
    protected:
        char symbol; // Symbol of the Border
        ANSI::Settings settings; // settings of the Border style

    public:
        Border(char symbol_, ANSI::Settings settings_): symbol(symbol_), settings(settings_) {}
        Border(char symbol_, ANSI::Settings& settings_, bool _by_reference): symbol(symbol_), settings(settings_) {}

        virtual void print(bool apply_settings=true) { // Print the Border
            if (apply_settings)
                settings.apply(); // Apply the settings
            std::cout << symbol; // Print the symbol
        }
    };
};