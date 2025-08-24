/** \file border.cpp
 *  \brief Implementation of the Border class for terminal borders.
 * 
 *  This file contains the implementation of the Border class, which represents
 *  a brick of the border of a field. A border is defined by a character
 *  symbol and ANSI settings for color and text attributes.
 * 
 *  \author FLAK-ZOSO
 *  \date 2022-2025
 *  \version 3.0.0
 *  \see Border
 *  \copyright GNU General Public License v3.0
 */
#include "border.hpp"
#include <iostream>

namespace sista {
    Border::Border(char symbol_, const ANSISettings& settings_): symbol(symbol_), settings(settings_) {}

    void Border::print(bool apply_settings) const { // Print the Border
        if (apply_settings)
            settings.apply(); // Apply the settings
        std::cout << symbol; // Print the symbol
    }
};
