#include "border.hpp" // Border
#include <iostream> // std::cout

namespace sista {
    Border::Border(char symbol_, const ANSISettings& settings_): symbol(symbol_), settings(settings_) {}

    void Border::print(bool apply_settings) const { // Print the Border
        if (apply_settings)
            settings.apply(); // Apply the settings
        std::cout << symbol; // Print the symbol
    }
};
