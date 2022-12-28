#pragma once

#include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
#include "border.hpp" // Border
#include "coordinates.hpp" // Coord, Coordinates, <utility>
#include "pawn.hpp" // Pawn
#include "field.hpp" // Field, Path, SwappableField
#if (_WIN32 || _WIN64)
    #include "clearScreen.hpp" // clearScreen [Windows-specific]
#endif