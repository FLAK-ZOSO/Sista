/** \file coordinates.hpp
 *  \brief Coordinates struct header file.
 * 
 *  This file contains the declaration of the Coordinates struct, which represents 2D coordinates.
 * 
 *  \author FLAK-ZOSO
 *  \date 2022-2025
 *  \version 3.0.0
 *  \see Coordinates
 *  \copyright GNU General Public License v3.0
 */
#pragma once

#include <utility>
#include <functional>

namespace sista {
    /** \struct Coordinates
     *  \brief Represents 2D coordinates with x and y values.
     *
     *  This struct encapsulates 2D coordinates using unsigned short integers for both
     *  the x (column) and y (row) values. It provides constructors, conversion methods,
     *  and overloaded operators for comparison and arithmetic operations.
     * 
     *  The coordinates system in Sista is defined such that `y` represents the row (vertical position)
     *  that increases downwards, and `x` represents the column (horizontal position) that increases to the right.
     *
     *  \see fromPair
     *  \see toPair
    */
    struct Coordinates {
        unsigned short y; /** y coordinate */
        unsigned short x; /** x coordinate */

        /** \brief Default constructor initializing coordinates to (0,0). */
        Coordinates();
        /** \brief Parameterized constructor.
         *  \param y_ The y coordinate (row).
         *  \param x_ The x coordinate (column).
        */
        Coordinates(unsigned short, unsigned short);
        /** \brief Creates a Coordinates instance from a std::pair.
         *  \param p A std::pair where first is y and second is x.
         *  \return A Coordinates instance with the specified y and x values.
         *
         *  This static method constructs a Coordinates object from a given std::pair.
         *  The first element of the pair corresponds to the y coordinate, and the second
         *  element corresponds to the x coordinate.
         *
         *  \see toPair
        */
        static Coordinates fromPair(const std::pair<unsigned short, unsigned short>&);
        /** \brief Converts the Coordinates instance to a std::pair.
         *  \return A std::pair where first is y and second is x.
         *
         *  This method converts the current Coordinates object into a std::pair,
         *  with the first element representing the y coordinate and the second
         *  element representing the x coordinate.
         *
         *  \see fromPair
        */
        std::pair<unsigned short, unsigned short> toPair() const;

        /** \brief Equality operator.
         *  \param other The other Coordinates instance to compare with.
         *  \return True if both coordinates are equal, false otherwise.
        */
        bool operator==(const Coordinates&) const;
        /** \brief Inequality operator.
         *  \param other The other Coordinates instance to compare with.
         *  \return True if the coordinates are not equal, false otherwise.
        */
        bool operator!=(const Coordinates&) const;
        /** \brief Less-than operator for ordering.
         *  \param other The other Coordinates instance to compare with.
         *  \return True if this coordinate is less than the other, false otherwise.
         *
         *  The ordering is first based on the y coordinate (row). If the y coordinates
         *  are equal, then the x coordinate (column) is used for comparison.
        */
        bool operator<(const Coordinates&) const;
        /** \brief Addition operator.
         *  \param other The other Coordinates instance to add.
         *  \return A new Coordinates instance representing the sum of the two coordinates.
         *  \note This operation does not ensure that the resulting coordinates are within any specific bounds.
        */
        Coordinates operator+(const Coordinates&) const;
        /** \brief Subtraction operator.
         *  \param other The other Coordinates instance to subtract.
         *  \return A new Coordinates instance representing the difference of the two coordinates.
         *  \warning This operation does not check for underflow; ensure that the result is valid.
        */
        Coordinates operator-(const Coordinates&) const;
        /** \brief Scalar multiplication operator.
         *  \param multiplier The scalar value to multiply both coordinates by.
         *  \return A new Coordinates instance with both coordinates multiplied by the scalar.
         *  \note This operation does not ensure that the resulting coordinates are within any specific bounds.
        */
        Coordinates operator*(const unsigned short) const;
        /** \brief Compound addition assignment operator.
         *  \param other The other Coordinates instance to add.
         *  \return A reference to the updated Coordinates instance.
         *  \note This operation modifies the current instance and does not ensure that the resulting coordinates are within any specific bounds.
        */
        Coordinates operator+=(const Coordinates&);
        /** \brief Compound subtraction assignment operator.
         *  \param other The other Coordinates instance to subtract.
         *  \return A reference to the updated Coordinates instance.
         *  \warning This operation modifies the current instance and does not check for underflow; ensure that the result is valid.
        */
        Coordinates operator-=(const Coordinates&);
    };
};

namespace std {
    /** \brief Specialization of std::hash for sista::Coordinates.
     *
     *  This specialization allows Coordinates to be used as keys in hash-based containers
     *  like std::unordered_map and std::unordered_set. The hash function combines the y and x
     *  coordinates into a single size_t value.
     *
     *  \see sista::Coordinates
    */
    template<>
    struct hash<sista::Coordinates> {
        std::size_t operator()(const sista::Coordinates&) const noexcept;
    };
};
