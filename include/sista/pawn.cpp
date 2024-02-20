#include "pawn.hpp" // Pawn

namespace sista {
    Pawn::Pawn(char symbol_, Coordinates coordinates_, ANSI::Settings settings_): symbol(symbol_), coordinates(coordinates_), settings(settings_) {}
    Pawn::Pawn(char symbol_, Coordinates& coordinates_, ANSI::Settings& settings_, bool _by_reference): symbol(symbol_), coordinates(coordinates_), settings(settings_) {}

    void Pawn::setCoordinates(Coordinates& coordinates_) {
        coordinates = coordinates_;
    }
    void Pawn::getCoordinates(Coordinates& coordinates_) {
        coordinates_ = coordinates;
    }
    Coordinates Pawn::getCoordinates() {
        return coordinates;
    }

    void Pawn::setSettings(ANSI::Settings& settings_) {
        settings = settings_;
    }
    void Pawn::getSettings(ANSI::Settings& settings_) {
        settings_ = settings;
    }
    ANSI::Settings Pawn::getSettings() {
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