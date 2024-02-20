#include "border.hpp" // Border

namespace sista {
    Border::Border(char symbol_, ANSI::Settings settings_): symbol(symbol_), settings(settings_) {}
    Border::Border(char symbol_, ANSI::Settings& settings_, bool _by_reference): symbol(symbol_), settings(settings_) {}

    void Border::print() { // Print the Border
        print(true); // Print the Border with the settings
    }
    void Border::print(bool apply_settings) { // Print the Border
        if (apply_settings)
            settings.apply(); // Apply the settings
        std::cout << symbol; // Print the symbol
    }
};