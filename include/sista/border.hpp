#pragma once

#include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
#include "coordinates.hpp" // Coord, Coordinates, <utility>

namespace sista {
    class Border { // Border class - represents a brick of the border [parent class]
    protected:
        char symbol; // Symbol of the Border
        ANSI::Settings settings; // settings of the Border style

    public:
        Border(char, ANSI::Settings);
        Border(char, ANSI::Settings&, bool);

        virtual void print();
        virtual void print(bool);
    };
};