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
        Pawn(char, Coordinates, ANSI::Settings);
        Pawn(char, Coordinates&, ANSI::Settings&, bool);
        virtual ~Pawn() {}

        void setCoordinates(Coordinates&);
        void getCoordinates(Coordinates&);
        Coordinates getCoordinates();

        void setSettings(ANSI::Settings&);
        void getSettings(ANSI::Settings&);
        ANSI::Settings getSettings();

        void setSymbol(char);
        char getSymbol();

        virtual void print();
    };
};