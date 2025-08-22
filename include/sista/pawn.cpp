#include "pawn.hpp" // Pawn

namespace sista {
    Pawn::Pawn(char symbol_, Coordinates coordinates_, ANSISettings settings_): symbol(symbol_), coordinates(coordinates_), settings(settings_) {}
    Pawn::Pawn(char symbol_, Coordinates& coordinates_, ANSISettings& settings_, bool _by_reference): symbol(symbol_), coordinates(coordinates_), settings(settings_) {}

    void Pawn::setCoordinates(Coordinates& coordinates_) {
        coordinates = coordinates_;
    }
    void Pawn::getCoordinates(Coordinates& coordinates_) {
        coordinates_ = coordinates;
    }
    Coordinates Pawn::getCoordinates() {
        return coordinates;
    }

    void Pawn::setSettings(ANSISettings& settings_) {
        settings = settings_;
    }
    void Pawn::getSettings(ANSISettings& settings_) {
        settings_ = settings;
    }
    ANSISettings Pawn::getSettings() {
        return settings;
    }

    void Pawn::setSymbol(char symbol_) {
        symbol = symbol_;
    }
    char Pawn::getSymbol() {
        return symbol;
    }

    void Pawn::print() { // Print the pawn
        settings.apply(); // Apply the settings
        std::cout << symbol; // Print the symbol
    }
};