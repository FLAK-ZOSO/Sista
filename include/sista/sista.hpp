#ifndef SISTA_HPP
    #define SISTA_HPP 1

    #ifndef ANSI_SETTINGS_HPP
        #include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
    #endif
    #ifndef BORDER_HPP
        #include "border.hpp" // Border
    #endif
    #ifndef COORDINATES_HPP
        #include "coordinates.hpp" // Coord, Coordinates, <utility>
    #endif
    #ifndef FIELD_HPP
        #include "field.hpp" // Field
    #endif
    #ifndef PAWN_HPP
        #include "pawn.hpp" // Pawn
    #endif

    #ifndef CLEARSCREEN_HPP
        #if (_WIN32 || _WIN64)
            #include "clearScreen.hpp" // clearScreen [Windows-specific]
        #endif
    #endif
#endif