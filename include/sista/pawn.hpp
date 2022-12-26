#pragma once

#include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
#include "coordinates.hpp" // Coord, Coordinates, <utility>


namespace sista {
    class Pawn { // Pawn class - represents an object on the field [parent class]
    protected:
        char symbol; // Symbol of the pawn
        Coordinates coordinates; // Coordinates of the pawn
        ANSI::Settings settings; // settings of the pawn style

    public:
        Pawn(char symbol_, Coordinates coordinates_, ANSI::Settings settings_): symbol(symbol_), coordinates(coordinates_), settings(settings_) {}
        Pawn(char symbol_, Coordinates& coordinates_, ANSI::Settings& settings_, bool _by_reference): symbol(symbol_), coordinates(coordinates_), settings(settings_) {}
        virtual ~Pawn() {}

        inline void setCoordinates(Coordinates& coordinates_) {
            coordinates = coordinates_;
        }
        inline void getCoordinates(Coordinates& coordinates_) {
            coordinates_ = coordinates;
        }
        inline Coordinates getCoordinates() {
            return coordinates;
        }

        inline void setSettings(ANSI::Settings& settings_) {
            settings = settings_;
        }
        inline void getSettings(ANSI::Settings& settings_) {
            settings_ = settings;
        }
        inline ANSI::Settings getSettings() {
            return settings;
        }

        inline void setSymbol(char symbol_) {
            symbol = symbol_;
        }
        inline char getSymbol() {
            return symbol;
        }

        virtual void print() { // Print the pawn
            settings.apply(); // Apply the settings
            std::cout << symbol; // Print the symbol
        }
    };
};