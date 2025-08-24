/** \file pawn.cpp
 *  \brief Implementation of the Pawn class.
 * 
 *  This file contains the implementation of the Pawn class, which represents
 *  a game piece with a symbol, coordinates on a field, and ANSI settings for
 *  its appearance in the terminal.
 * 
 *  \author FLAK-ZOSO
 *  \date 2022-2025
 *  \version 3.0.0
 *  \see Pawn
 *  \copyright GNU General Public License v3.0
 */
#include "pawn.hpp"
#include <iostream>

namespace sista {
    Pawn::Pawn(char symbol_, const Coordinates& coordinates_, const ANSISettings& settings_): symbol(symbol_), coordinates(coordinates_), settings(settings_) {}

    void Pawn::setCoordinates(const Coordinates& coordinates_) {
        coordinates = coordinates_;
    }
    void Pawn::getCoordinates(Coordinates& coordinates_) const {
        coordinates_ = coordinates;
    }
    Coordinates Pawn::getCoordinates() const {
        return coordinates;
    }

    void Pawn::setSettings(const ANSISettings& settings_) {
        settings = settings_;
    }
    void Pawn::getSettings(ANSISettings& settings_) const {
        settings_ = settings;
    }
    ANSISettings Pawn::getSettings() const {
        return settings;
    }

    void Pawn::setSymbol(char symbol_) {
        symbol = symbol_;
    }
    char Pawn::getSymbol() const {
        return symbol;
    }

    void Pawn::print() const { // Print the pawn
        settings.apply(); // Apply the settings
        std::cout << symbol; // Print the symbol
    }
};
