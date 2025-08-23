#pragma once

#include "ansi.hpp" // ForegroundColor, BackgroundColor, Attribute, ANSISettings
#include "coordinates.hpp" // Coord, Coordinates, <utility>

namespace sista {
    class Border { // Border class - represents a brick of the border [parent class]
    protected:
        char symbol; // Symbol of the Border
        ANSISettings settings; // settings of the Border style

    public:
        Border(char, const ANSISettings&);

        virtual void print(bool apply_settings=true);
    };
};