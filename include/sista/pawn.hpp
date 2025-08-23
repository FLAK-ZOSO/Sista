#pragma once

#include "ansi.hpp" // ForegroundColor, BackgroundColor, Attribute, ANSISettings
#include "coordinates.hpp" // Coord, Coordinates, <utility>


namespace sista {
    class Pawn { // Pawn class - represents an object on the field [parent class]
    protected:
        char symbol; // Symbol of the pawn
        Coordinates coordinates; // Coordinates of the pawn
        ANSISettings settings; // settings of the pawn style

    public:
        Pawn(char, Coordinates, ANSISettings);
        Pawn(char, Coordinates&, ANSISettings&, bool);
        virtual ~Pawn() {}

        void setCoordinates(Coordinates&);
        void getCoordinates(Coordinates&);
        Coordinates getCoordinates();

        void setSettings(ANSISettings&);
        void getSettings(ANSISettings&);
        ANSISettings getSettings();

        void setSymbol(char);
        char getSymbol();

        virtual void print();
    };
};