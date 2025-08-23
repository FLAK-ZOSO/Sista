#include "pawn.hpp" // Pawn

namespace sista {
    Pawn::Pawn(char symbol_, const Coordinates& coordinates_, const ANSISettings& settings_): symbol(symbol_), coordinates(coordinates_), settings(settings_) {}

    void Pawn::setCoordinates(const Coordinates& coordinates_) {
        coordinates = coordinates_;
    }
    void Pawn::getCoordinates(Coordinates& coordinates_) {
        coordinates_ = coordinates;
    }
    Coordinates Pawn::getCoordinates() {
        return coordinates;
    }

    void Pawn::setSettings(const ANSISettings& settings_) {
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