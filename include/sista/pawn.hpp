#pragma once

#include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
#include "coordinates.hpp" // Coord, Coordinates, <utility>


class Pawn { // Pawn class - represents an object on the field [parent class]
public:
    char symbol; // Symbol of the pawn
    Coordinates coordinates; // Coordinates of the pawn
    ANSI::Settings settings; // settings of the pawn style

    Pawn(char symbol_, Coordinates coordinates_, ANSI::Settings settings_): symbol(symbol_), coordinates(coordinates_), settings(settings_) {} // Constructor
    Pawn(char symbol_, Coordinates& coordinates_, ANSI::Settings& settings_): symbol(symbol_), coordinates(coordinates_), settings(settings_) {} // Constructor

    virtual void print() { // Print the pawn
        settings.apply(); // Apply the settings
        std::cout << symbol; // Print the symbol
    }
};