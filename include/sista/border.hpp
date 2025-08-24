/** \file border.hpp
 *  \brief Border class header file.
 *  \author FLAK-ZOSO
 *  \date 2022-2025
 *  \version 3.0.0
 * 
 *  This file contains the declaration of the Border class, which represents a brick of the border.
 * 
 *  \see Border
 *  \copyright GNU General Public License v3.0
 */
#pragma once

#include "ansi.hpp"
#include "coordinates.hpp"

/** \namespace sista
 *  \brief Sista library namespace.
 * 
 *  This namespace encapsulates all components of the Sista library.
 * 
 *  \see ANSISettings
 *  \see Coordinates
*/
namespace sista {
    /** \class Border
     *  \brief Represents a brick of the border with a symbol and ANSI settings.
     *
     *  The Border class encapsulates a character symbol and its associated ANSI settings,
     *  allowing for the representation and printing of border "bricks" in a terminal.
     *
     *  \see ANSISettings
    */
    class Border {
    protected:
        char symbol; /** The character symbol representing the border brick. */
        ANSISettings settings; /** The ANSI settings for the border brick. */

    public:
        /** \brief Constructor to initialize the border with a symbol and ANSI settings.
         * 
         *  \param symbol_ The character symbol for the border brick.
         *  \param settings_ The ANSISettings for the border brick.
         */
        Border(char, const ANSISettings&);

        /** \brief Prints the border symbol to the terminal, applying ANSI settings if specified.
         * 
         *  \param apply_settings If true, applies the ANSI settings before printing the symbol.
         * 
         *  This method prints the border's symbol to the terminal. If apply_settings is true,
         *  it first applies the stored ANSI settings (foreground color, background color, and attribute)
         *  to ensure the symbol is displayed with the desired formatting.
         * 
         *  \see ANSISettings::apply
        */
        virtual void print(bool=true) const;
    };
};
