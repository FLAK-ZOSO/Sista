#pragma once

#include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
#include "coordinates.hpp" // Coord, Coordinates, <utility>


class Border { // Border class - represents a brick of the border [parent class]
public:
    char symbol; // Symbol of the Border
    ANSI::Settings settings; // settings of the Border style

    Border(char symbol_, ANSI::Settings settings_): symbol(symbol_), settings(settings_) {} // Constructor
    Border(char symbol_, ANSI::Settings& settings_): symbol(symbol_), settings(settings_) {} // Constructor

    virtual void print() { // Print the Border
        settings.apply(); // Apply the settings
        std::cout << symbol; // Print the symbol
    }
    virtual void print(bool _) { // Print the Border when the style is already applied
        std::cout << symbol; // Print the symbol
    }
};