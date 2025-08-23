#pragma once

#include "ansi.hpp" // ForegroundColor, BackgroundColor, Attribute, ANSISettings
#include "coordinates.hpp" // Coordinates, <utility>


namespace sista {
    class Pawn { // Pawn class - represents an object on the field [parent class]
    protected:
        char symbol; // Symbol of the pawn
        Coordinates coordinates; // Coordinates of the pawn
        ANSISettings settings; // settings of the pawn style

    public:
        Pawn(char, const Coordinates&, const ANSISettings&);
        virtual ~Pawn() {}

        void setCoordinates(const Coordinates&);
        void getCoordinates(Coordinates&);
        Coordinates getCoordinates();

        void setSettings(const ANSISettings&);
        void getSettings(ANSISettings&);
        ANSISettings getSettings();

        void setSymbol(char);
        char getSymbol();

        virtual void print();
    };
};