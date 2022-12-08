#pragma once

#include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
#include "coordinates.hpp" // Coord, Coordinates, <utility>


class Pawn { // Pawn class - represents an object on the field [parent class]
public:
    Coordinates coordinates; // Coordinates of the pawn
    ANSI::Settings settings; // settings of the pawn style
    char symbol; // Symbol of the pawn

    Pawn(Coordinates coordinates_, char symbol_, ANSI::Settings settings_): coordinates(coordinates_), symbol(symbol_), settings(settings_) {} // Constructor
    Pawn(Coordinates& coordinates_, char symbol_, ANSI::Settings& settings_): coordinates(coordinates_), symbol(symbol_), settings(settings_) {} // Constructor

    virtual void print() { // Print the pawn
        settings.apply(); // Apply the settings
        std::cout << symbol; // Print the symbol
    }
};