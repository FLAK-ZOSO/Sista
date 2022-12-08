#ifndef BORDER_HPP
    #define BORDER_HPP 1

#ifndef ANSI_SETTINGS_HPP
    #include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
#endif
#ifndef COORDINATES_HPP
    #include "coordinates.hpp" // Coord, Coordinates, <utility>
#endif


class Border { // Border class - represents a brick of the border [parent class]
public:
    ANSI::Settings settings; // settings of the Border style
    char symbol; // Symbol of the Border

    Border(char symbol_, ANSI::Settings settings_): symbol(symbol_), settings(settings_) {} // Constructor
    Border(char symbol_, ANSI::Settings& settings_): symbol(symbol_), settings(settings_) {} // Constructor

    virtual void print() { // Print the Border
        settings.apply(); // Apply the settings
        std::cout << symbol; // Print the symbol
    }
    virtual void print(bool _) { // Print the Border when the style is already applied
        std::cout << symbol; // Print the symbol
    }
};
#endif