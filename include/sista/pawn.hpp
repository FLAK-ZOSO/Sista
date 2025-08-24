/** \file pawn.hpp
 *  \brief Pawn class header file.
 *
 *  This file contains the declaration of the Pawn class, which represents an object on the field.
 *  Pawns have a symbol, coordinates, and ANSI settings for their appearance in the terminal.
 *  Pawns can be printed to the terminal with their associated ANSI settings.
 *
 *  \see Coordinates
 *  \see ANSISettings
 *
 *  \author FLAK-ZOSO
 *  \date 2022-2025
 *  \version 3.0.0
 *  \copyright GNU General Public License v3.0
 */
#pragma once

#include "ansi.hpp"
#include "coordinates.hpp"

namespace sista {
    /** \class Pawn
     *  \brief Represents an object on the field with a symbol, coordinates, and ANSI settings.
     *
     *  The Pawn class encapsulates a character symbol, its position on the field using Coordinates,
     *  and its appearance using ANSISettings. It provides methods to set and get these properties,
     *  as well as a method to print the pawn to the terminal with its associated ANSI settings.
     *
     *  The Pawn class is designed to be subclassed for specific types of pawns with additional behavior.
     *  Examples of subclasses could include players, enemies, or items in a videogame.
     *
     *  \note Pawns do not manage their own movement; this is handled by the Field class.
     *  \see Coordinates
     *  \see ANSISettings
     *  \see Field
    */
    class Pawn {
    protected:
        char symbol; /** The character symbol representing the pawn */
        Coordinates coordinates; /** The coordinates of the pawn relatively to the field */
        ANSISettings settings; /** The ANSI settings for the pawn */

    public:
        /** \brief Constructor to initialize the pawn with a symbol, coordinates, and ANSI settings.
         *
         *  \param symbol_ The character symbol for the pawn.
         *  \param coordinates_ The Coordinates representing the pawn's position on the field.
         *  \param settings_ The ANSISettings for the pawn's appearance.
         */
        Pawn(char, const Coordinates&, const ANSISettings&);
        /** \brief Virtual destructor. */
        virtual ~Pawn() {}

        /** \brief Sets the coordinates of the pawn.
         *  \param coordinates_ The new Coordinates for the pawn.
        */
        void setCoordinates(const Coordinates&);
        /** \brief Gets the coordinates of the pawn.
         *  \param coordinates_ A reference to a Coordinates object to store the pawn's coordinates.
        */
        void getCoordinates(Coordinates&) const;
        /** \brief Gets the coordinates of the pawn.
         *  \return The Coordinates of the pawn.
        */
        Coordinates getCoordinates() const;

        /** \brief Sets the ANSI settings of the pawn.
         *  \param settings_ The new ANSISettings for the pawn.
        */
        void setSettings(const ANSISettings&);
        /** \brief Gets the ANSI settings of the pawn.
         *  \param settings_ A reference to an ANSISettings object to store the pawn's settings.
        */
        void getSettings(ANSISettings&) const;
        /** \brief Gets the ANSI settings of the pawn.
         *  \return The ANSISettings of the pawn.
        */
        ANSISettings getSettings() const;

        /** \brief Sets the symbol of the pawn.
         *  \param symbol_ The new character symbol for the pawn.
         *  \note The symbol should be a printable character.
         *  \note This method is a sheer setter, it does not handle reprinting the pawn on the field.
        */
        void setSymbol(char);
        /** \brief Gets the symbol of the pawn.
         *  \return The character symbol of the pawn.
        */
        char getSymbol() const;

        /** \brief Prints the pawn to the terminal with its associated ANSI settings.
         *
         *  This method applies the pawn's ANSI settings (foreground color, background color, and attribute)
         *  and then prints the pawn's symbol to the terminal. The settings will be visible on characters
         *  printed after this call until they are reset or changed.
         *
         *  \see ANSISettings::apply
        */
        virtual void print() const;
    };
};
