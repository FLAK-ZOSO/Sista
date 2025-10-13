/** \file field.hpp
 *  \brief This file contains the Field class and related structures.
 * 
 *  This file contains the core functionalities of the Sista library.
 *
 *  The Field class represents a 2D grid where Pawns can be placed, moved, and managed.
 *  It provides methods to add, remove, move, and print Pawns on the field.
 *  The Field class also handles boundary conditions and occupancy checks.
 *
 *  Additionally, the SwappableField subclass extends Field to handle scenarios where
 *  multiple Pawns may need to swap positions without conflicts.
 *
 *  The Path structure is used to represent movement paths for Pawns, including priority handling.
 *
 *  \see Pawn
 *  \see Coordinates
 *  \see ANSISettings
 *  \see Border
 *  \see Cursor
 *
 *  \author FLAK-ZOSO
 *  \date 2022-2025
 *  \version 3.0.0
 *  \copyright GNU General Public License v3.0
 */
#pragma once

#include <vector> // std::vector
#include <memory> // std::shared_ptr, std::move
#include <map> // std::map
#include <set> // std::set
#include "pawn.hpp"
#include "border.hpp"
#include "cursor.hpp"

namespace sista {
    /** \enum Effect
     *  \brief Enumeration for handling out-of-bounds coordinates.
     *
     *  This enum class defines different effects that can be applied when a Pawn's coordinates
     *  go out of the bounds of the Field. The effects determine how the coordinates are adjusted
     *  to bring them back within valid limits.
     *
     *  - PACMAN: Wraps around to the opposite side of the field (like in the PacMan game).
     *  - MATRIX: Wraps to the beginning of the next line (like in classic C-style arrays).
     * 
     *  \see Field::movingByCoordinates
     *  \see Field::movePawnBy
     */
    enum class Effect { // Effect enum - effect when a coordinate is out of bounds
        PACMAN = 0, // Pacman effect when a coordinate overflows
        MATRIX = 1 // Classic C style matrix effect when a coordinate overflows
    };

    /** \class Field
     *  \brief Represents a 2D grid where Pawns can be placed, moved, and managed.
     *
     *  The Field class encapsulates a 2D grid structure using a vector of vectors to hold shared pointers to Pawn objects.
     *  It provides methods to add, remove, move, and print Pawns on the field. The class also includes functionality
     *  to check if specific coordinates are occupied, free, or out of bounds, and to validate coordinates.
     *
     *  The Field class is designed to be extended for more specialized behavior, such as in the SwappableField subclass,
     *  which handles scenarios where multiple Pawns may need to swap positions without conflicts.
     * 
     *  \see Pawn
     *  \see Coordinates
     *  \see Border
     *  \see Cursor
     *  \see SwappableField
     */
    class Field { // Field class - represents the field [parent class]
    protected:
        /** \brief 2D grid of shared pointers to Pawn objects. */
        std::vector<std::vector<std::shared_ptr<Pawn>>> pawns;
        Cursor cursor; /** Cursor object for terminal operations. */
        int width; /** Width of the matrix */
        int height; /** Height of the matrix */

        /** \brief Cleans the coordinates on screen by printing spaces.
         *  \param coordinates The Coordinates to clean.
        */
        void cleanCoordinates(const Coordinates&) const;
        /** \brief Cleans the coordinates on screen by printing spaces.
         *  \param y The y coordinate (row).
         *  \param x The x coordinate (column).
        */
        void cleanCoordinates(unsigned short, unsigned short) const;

    public:
        /** \brief Clears the field by removing all Pawns and resetting the grid.
         *  \note This does not delete the Pawn objects, it only removes them from the field.
         */
        void clear();

        /** \brief Constructor to initialize the field with specified width and height.
         *  \param width_ The width of the field (number of columns).
         *  \param height_ The height of the field (number of rows).
         *
         *  This constructor initializes a Field object with the given dimensions.
         *  It sets up a 2D grid (vector of vectors) to hold shared pointers to Pawn objects,
         *  and initializes the Cursor for terminal operations.
         *
         *  \see Cursor
        */
        Field(int, int);
        /** \brief Destructor to clean up resources. */
        virtual ~Field() = default;

        /** \brief Prints the entire field to the terminal.
         *
         *  This method iterates through the 2D grid of Pawns and prints each Pawn's symbol
         *  at its respective coordinates.
         *  The method uses the Cursor object to manage terminal cursor positioning.
         *
         *  \see Pawn::print
         *  \see Cursor
        */
        void print() const;
        /** \brief Prints the entire field to the terminal.
         *  \param border A character to use as the border symbol.
         *
         *  This method iterates through the 2D grid of Pawns and prints each Pawn's symbol
         *  at its respective coordinates. It also prints a border around the field using the specified character.
         *  The method uses the Cursor object to manage terminal cursor positioning.
         *
         *  \see Pawn::print
         *  \see Cursor
        */
        void print(char) const;
        /** \brief Prints the entire field to the terminal.
         *  \param border A Border object to use for the border.
         *
         *  This method iterates through the 2D grid of Pawns and prints each Pawn's symbol
         *  at its respective coordinates. It also prints a border around the field using the specified Border object.
         *  The method uses the Cursor object to manage terminal cursor positioning.
         *
         *  \see Pawn::print
         *  \see Border::print
         *  \see Cursor
        */
        void print(Border&) const;

        /** \brief Adds a Pawn to the field at its specified coordinates.
         *  \param pawn A shared pointer to the Pawn to add.
         *
         *  This method places the given Pawn on the field at its current coordinates.
         *  If the coordinates are already occupied, the existing Pawn will be replaced.
         *
         *  \warning The Pawn's coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method takes a shared pointer to manage the Pawn's memory automatically.
         *
         *  \see Pawn
        */
        virtual void addPawn(std::shared_ptr<Pawn>);
        /** \brief Removes a Pawn from the field.
         *  \param pawn A pointer to the Pawn to remove.
         *
         *  This method removes the specified Pawn from the field.
         *  If the Pawn is not found at its coordinates, no action is taken.
         *
         *  \warning The Pawn's coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method does not delete the Pawn object, it only removes it from the field.
         *
         *  \see Pawn
        */
        virtual void removePawn(Pawn*);
        /** \brief Removes a Pawn from the field at specified coordinates.
         *  \param coordinates The Coordinates of the Pawn to remove.
         *
         *  This method removes the Pawn located at the given coordinates from the field.
         *  If no Pawn is found at the specified coordinates, no action is taken.
         *
         *  \warning The coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method does not delete the Pawn object, it only removes it from the field.
         *
         *  \see Pawn
        */
        virtual void removePawn(const Coordinates&);
        /** \brief Removes a Pawn from the field at specified coordinates.
         *  \param pawn A pointer to the Pawn to remove.
         *
         *  This method removes the given Pawn from the field.
         *  Unlike removePawn, this method also cleans the cell on the terminal by printing a space.
         *
         *  \warning The coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method does not delete the Pawn object, it only removes it from the field.
         *
         *  \see Pawn
        */
        virtual void erasePawn(Pawn*);
        /** \brief Removes a Pawn from the field at specified coordinates.
         *  \param coordinates The Coordinates of the Pawn to remove.
         *
         *  This method removes the Pawn located at the given coordinates from the field.
         *  Unlike removePawn, this method also cleans the cell on the terminal by printing a space.
         *
         *  \warning The coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method does not delete the Pawn object, it only removes it from the field.
         *
         *  \see Pawn
        */
        virtual void erasePawn(const Coordinates&);

        /** \brief Adds a Pawn to the field at its specified coordinates and prints it.
         *  \param pawn A shared pointer to the Pawn to add and print.
         * 
         *  This method places the given Pawn on the field at its current coordinates and prints it to the terminal.
         *  If the coordinates are already occupied, the existing Pawn will be replaced.
         *
         *  \warning The Pawn's coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method takes a shared pointer to manage the Pawn's memory automatically.
         *
         *  \see Pawn
         */
        void addPrintPawn(std::shared_ptr<Pawn>);
        /** \brief Reprints a Pawn at its current coordinates.
         *  \param pawn A pointer to the Pawn to reprint.
         *
         *  This method reprints the specified Pawn at its current coordinates on the terminal.
         *  It is useful for updating the Pawn's appearance after changes to its settings or symbol.
         *
         *  \warning The Pawn's coordinates must be valid (within the field bounds) as they are not validated here.
         *
         *  \see Pawn::print
        */
        void rePrintPawn(Pawn*);

        /** \brief Moves a Pawn to new coordinates.
         *  \param pawn A pointer to the Pawn to move.
         *  \param coordinates The new Coordinates to move the Pawn to.
         *
         *  This method moves the specified Pawn to the given coordinates on the field.
         *  If the target coordinates are already occupied, the existing Pawn will be replaced.
         *
         *  \throws `std::invalid_argument` if the coordinates are occupied by another Pawn or out of bounds.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see validateCoordinates
        */
        void movePawn(Pawn*, const Coordinates&);
        /** \brief Moves a Pawn to new coordinates.
         *  \param pawn A pointer to the Pawn to move.
         *  \param y The new y coordinate (row) to move the Pawn to.
         *  \param x The new x coordinate (column) to move the Pawn to.
         *
         *  This method moves the specified Pawn to the given coordinates on the field.
         *  If the target coordinates are already occupied, the existing Pawn will be replaced.
         *
         *  \throws `std::invalid_argument` if the coordinates are occupied by another Pawn or out of bounds.
         *
         *  \note This method is just a convenience overload that constructs a Coordinates object internally.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see validateCoordinates
        */
        void movePawn(Pawn*, unsigned short, unsigned short);

        /** \brief Moves a Pawn by a relative offset.
         *  \param pawn A pointer to the Pawn to move.
         *  \param coordinates The relative Coordinates to move the Pawn by.
         *
         *  This method moves the specified Pawn by the given relative offset.
         *
         *  \throws `std::invalid_argument` if the resulting coordinates are occupied by another Pawn or out of bounds.
         *
         *  \note This method is just a convenience overload that constructs a Coordinates object internally and then calls movePawn.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see validateCoordinates
         */
        void movePawnBy(Pawn*, const Coordinates&);
        /** \brief Moves a Pawn by a relative offset.
         *  \param pawn A pointer to the Pawn to move.
         *  \param y The relative y offset (rows) to move the Pawn by.
         *  \param x The relative x offset (columns) to move the Pawn by.
         *
         *  This method moves the specified Pawn by the given relative offset.
         *
         *  \throws `std::invalid_argument` if the resulting coordinates are occupied by another Pawn or out of bounds.
         *
         *  \note This method is just a convenience overload that constructs a Coordinates object internally and then calls movePawn.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see validateCoordinates
        */
        void movePawnBy(Pawn*, unsigned short, unsigned short);

        // 🎮 movePawnBy() with arcade game effects on coordinates overflow
        /** \brief Moves a Pawn by a relative offset with specified effect on out-of-bounds coordinates.
         *  \param pawn A pointer to the Pawn to move.
         *  \param coordinates The relative Coordinates to move the Pawn by.
         *  \param effect The Effect to apply when the resulting coordinates are out of bounds.
         *
         *  This method moves the specified Pawn by the given relative offset, applying the specified effect
         *  if the resulting coordinates go out of bounds.
         *
         *  \throws `std::invalid_argument` if the resulting coordinates are occupied by another Pawn after applying the effect.
         *  \throws `std::out_of_range` if the effect is MATRIX and the resulting coordinates are out of bounds.
         *
         *  \note This method is just a convenience overload that deconstructs a Coordinates object internally and then calls movePawnBy(y,x).
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see Effect
         *  \see validateCoordinates
        */
        void movePawnBy(Pawn*, const Coordinates&, Effect);
        /** \brief Moves a Pawn by a relative offset with specified effect on out-of-bounds coordinates.
         *  \param pawn A pointer to the Pawn to move.
         *  \param y The relative y offset (rows) to move the Pawn by.
         *  \param x The relative x offset (columns) to move the Pawn by.
         *  \param effect The Effect to apply when the resulting coordinates are out of bounds.
         *
         *  This method moves the specified Pawn by the given relative offset, applying the specified effect
         *  if the resulting coordinates go out of bounds.
         *
         *  \throws `std::invalid_argument` if the resulting coordinates are occupied by another Pawn after applying the effect.
         *  \throws `std::out_of_range` if the effect is MATRIX and the resulting coordinates are out of bounds.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see Effect
         *  \see validateCoordinates
        */
        void movePawnBy(Pawn*, short int, short int, Effect);

        /** \brief Moves a Pawn from one set of coordinates to another.
         *  \param coordinates The current Coordinates of the Pawn.
         *  \param newCoordinates The new Coordinates to move the Pawn to.
         *
         *  This method finds the Pawn at the specified current coordinates and moves it to the new coordinates.
         *
         *  \throws `std::invalid_argument` if there is no Pawn at the current coordinates or if the new coordinates are occupied by another Pawn or out of bounds.
         *
         *  \note This method is a convenience function that calls both getPawn and movePawn internally.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see validateCoordinates
         *  \see getPawn
         *  \see movePawn
         */
        void movePawnFromTo(const Coordinates&, const Coordinates&);
        /** \brief Moves a Pawn from one set of coordinates to another.
         *  \param y The current y coordinate (row) of the Pawn.
         *  \param x The current x coordinate (column) of the Pawn.
         *  \param newY The new y coordinate (row) to move the Pawn to.
         *  \param newX The new x coordinate (column) to move the Pawn to.
         *
         *  This method finds the Pawn at the specified current coordinates and moves it to the new coordinates.
         *
         *  \throws `std::invalid_argument` if there is no Pawn at the current coordinates or if the new coordinates are occupied by another Pawn or out of bounds.
         *
         *  \note This method is a convenience function that calls both getPawn and movePawn internally.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see validateCoordinates
         *  \see getPawn
         *  \see movePawn
        */
        void movePawnFromTo(unsigned short, unsigned short, unsigned short, unsigned short);

        /** \brief Calculates the new coordinates of a Pawn after moving by a relative offset.
         *  \param pawn A pointer to the Pawn to calculate the new coordinates for.
         *  \param y The relative y offset (rows) to move the Pawn by.
         *  \param x The relative x offset (columns) to move the Pawn by.
         *  \return The new Coordinates of the Pawn after applying the movement.
         *
         *  This method calculates the new coordinates of the specified Pawn after moving it by the given relative offset.
         *  It does not modify the Pawn's actual coordinates, it only computes and returns the new position.
         *
         *  \throws `std::out_of_range` if the resulting coordinates are out of bounds.
         *
         *  \note This method only calculates the new coordinates, it does not move the Pawn.
         *
         *  \see Pawn
         *  \see Coordinates
        */
        Coordinates movingByCoordinates(Pawn*, short int, short int) const;        
        /** \brief Calculates the new coordinates of a Pawn after moving by a relative offset with specified effect on out-of-bounds coordinates.
         *  \param pawn A pointer to the Pawn to calculate the new coordinates for.
         *  \param y The relative y offset (rows) to move the Pawn by.
         *  \param x The relative x offset (columns) to move the Pawn by.
         *  \param effect The Effect to apply when the resulting coordinates are out of bounds.
         *  \return The new Coordinates of the Pawn after applying the movement and effect.
         *
         *  This method calculates the new coordinates of the specified Pawn after moving it by the given relative offset.
         *  If the resulting coordinates go out of bounds, the specified effect is applied to adjust them accordingly.
         *
         *  \throws `std::out_of_range` if the resulting coordinates are out of bounds.
         *
         *  \note This method only calculates the new coordinates, it does not move the Pawn.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see Effect
        */
        Coordinates movingByCoordinates(Pawn*, short int, short int, Effect) const; // movingByCoordinates - calculate the coordinates of a pawn after a movement

        /** \brief Gets the Pawn at specified coordinates.
         *  \param coordinates The Coordinates to get the Pawn from.
         *  \return A pointer to the Pawn at the given coordinates, or nullptr if no Pawn is found.
         *
         *  This method retrieves the Pawn located at the specified coordinates on the field.
         *  If no Pawn is found at those coordinates, the method returns nullptr.
         *
         *  \warning The coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method returns a raw pointer to the Pawn that is managed by a shared pointer in the field and thus must not be deleted.
         *
         *  \see Pawn
         *  \see Coordinates
        */
        Pawn* getPawn(const Coordinates&) const;
        /** \brief Gets the Pawn at specified coordinates.
         *  \param y The y coordinate (row) to get the Pawn from.
         *  \param x The x coordinate (column) to get the Pawn from.
         *  \return A pointer to the Pawn at the given coordinates, or nullptr if no Pawn is found.
         *
         *  This method retrieves the Pawn located at the specified coordinates on the field.
         *  If no Pawn is found at those coordinates, the method returns nullptr.
         *
         *  \warning The coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method returns a raw pointer to the Pawn that is managed by a shared pointer in the field and thus must not be deleted.
         *
         *  \see Pawn
         *  \see Coordinates
        */
        Pawn* getPawn(unsigned short, unsigned short) const;

        /** \brief Checks if specified coordinates are occupied by a Pawn.
         *  \param coordinates The Coordinates to check.
         *  \return `true` if the coordinates are occupied, `false` otherwise.
         *
         *  This method checks if there is a Pawn located at the specified coordinates on the field.
         *
         *  \warning The coordinates must be valid (within the field bounds) as they are not validated here
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see isFree
         *  \see isOutOfBounds
         */
        bool isOccupied(const Coordinates&) const;
        /** \brief Checks if specified coordinates are occupied by a Pawn.
         *  \param y The y coordinate (row) to check.
         *  \param x The x coordinate (column) to check.
         *  \return `true` if the coordinates are occupied, `false` otherwise.
         *
         *  This method checks if there is a Pawn located at the specified coordinates on the field.
         *
         *  \warning The coordinates must be valid (within the field bounds) as they are not validated here
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see isFree
         *  \see isOutOfBounds
        */
        bool isOccupied(unsigned short, unsigned short) const;
        /** \brief Checks if specified coordinates are occupied by a Pawn.
         *  \param y The y coordinate (row) to check.
         *  \param x The x coordinate (column) to check.
         *  \return `true` if the coordinates are occupied, `false` otherwise.
         *
         *  This method checks if there is a Pawn located at the specified coordinates on the field.
         *
         *  \note This overload uses signed integers to allow checking for negative coordinates.
         *  \warning The coordinates must be valid (within the field bounds) as they are not validated here
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see isFree
         *  \see isOutOfBounds
        */
        bool isOccupied(short int, short int) const;

        /** \brief Checks if specified coordinates are out of bounds.
         *  \param coordinates The Coordinates to check.
         *  \return `true` if the coordinates are out of bounds, `false` otherwise.
         *
         *  This method checks if the given coordinates are outside the valid range of the field.
         *
         *  \see Coordinates
         *  \see isOccupied
         *  \see isFree
        */
        bool isOutOfBounds(const Coordinates&) const;
        /** \brief Checks if specified coordinates are out of bounds.
         *  \param y The y coordinate (row) to check.
         *  \param x The x coordinate (column) to check.
         *  \return `true` if the coordinates are out of bounds, `false` otherwise.
         *
         *  This method checks if the given coordinates are outside the valid range of the field.
         *
         *  \see Coordinates
         *  \see isOccupied
         *  \see isFree
        */
        bool isOutOfBounds(unsigned short, unsigned short) const;
        /** \brief Checks if specified coordinates are out of bounds.
         *  \param y The y coordinate (row) to check.
         *  \param x The x coordinate (column) to check.
         *  \return `true` if the coordinates are out of bounds, `false` otherwise.
         *
         *  This method checks if the given coordinates are outside the valid range of the field.
         *
         *  \note This overload uses signed integers to allow checking for negative coordinates.
         *
         *  \see Coordinates
         *  \see isOccupied
         *  \see isFree
        */
        bool isOutOfBounds(short int, short int) const;

        /** \brief Checks if specified coordinates are free (not occupied by a Pawn).
         *  \param coordinates The Coordinates to check.
         *  \return `true` if the coordinates are free, `false` otherwise.
         *
         *  This method checks if there is no Pawn located at the specified coordinates on the field.
         *
         *  \note This is a negation of isOccupied provided that isOutOfBounds returns false. Read implementation for more details.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see isOccupied
         *  \see isOutOfBounds
        */
        bool isFree(const Coordinates&) const;
        /** \brief Checks if specified coordinates are free (not occupied by a Pawn).
         *  \param y The y coordinate (row) to check.
         *  \param x The x coordinate (column) to check.
         *  \return `true` if the coordinates are free, `false` otherwise.
         *
         *  This method checks if there is no Pawn located at the specified coordinates on the field.
         *
         *  \note This is a negation of isOccupied provided that isOutOfBounds returns false. Read implementation for more details.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see isOccupied
         *  \see isOutOfBounds
        */
        bool isFree(unsigned short, unsigned short) const;
        /** \brief Checks if specified coordinates are free (not occupied by a Pawn).
         *  \param y The y coordinate (row) to check.
         *  \param x The x coordinate (column) to check.
         *  \return `true` if the coordinates are free, `false` otherwise.
         *
         *  This method checks if there is no Pawn located at the specified coordinates on the field.
         *
         *  \note This overload uses signed integers to allow checking for negative coordinates.
         *  \note This is a negation of isOccupied provided that isOutOfBounds returns false. Read implementation for more details.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see isOccupied
         *  \see isOutOfBounds
        */
        bool isFree(short int, short int) const;

        /** \brief Validates that the given coordinates are within bounds and not occupied.
         *  \param coordinates The Coordinates to validate.
         *
         *  This method checks if the specified coordinates are within the valid range of the field
         *  and not occupied by another Pawn. If either condition is not met, an exception is thrown.
         *
         *  \throws `std::invalid_argument` if the coordinates are occupied by another Pawn.
         *  \throws `std::out_of_range` if the coordinates are out of bounds.
         *
         *  \see Coordinates
         *  \see isOccupied
         *  \see isOutOfBounds
        */
        void validateCoordinates(const Coordinates&) const;
        /** \brief Validates that the given coordinates are within bounds and not occupied.
         *  \param y The y coordinate (row) to validate.
         *  \param x The x coordinate (column) to validate.
         *
         *  This method checks if the specified coordinates are within the valid range of the field
         *  and not occupied by another Pawn. If either condition is not met, an exception is thrown.
         *
         *  \throws `std::invalid_argument` if the coordinates are occupied by another Pawn.
         *  \throws `std::out_of_range` if the coordinates are out of bounds.
         *
         *  \see Coordinates
         *  \see isOccupied
         *  \see isOutOfBounds
        */
        void validateCoordinates(unsigned short, unsigned short) const;
    };    

    /** \struct Path
     *  \brief Represents a movement path for a Pawn, including priority handling.
     *
     *  The Path struct encapsulates the beginning and end coordinates of a movement path for a Pawn.
     *  It includes a priority attribute to determine the order of processing paths, as well as a static
     *  current_priority counter to assign unique priorities to new paths.
     *
     *  The struct provides operator overloads to compare paths based on priority, check for equality,
     *  and determine if two paths are opposite (i.e., one is the reverse of the other).
     *
     *  \note The way this struct is handled assumes that no two identical paths (same begin and end coordinates) will be created, as no two pawns can occupy the same coordinates at the same time.
     *
     *  \see Coordinates
     *  \see Pawn
    */
    struct Path {
        static long long int current_priority; /** Static counter to assign unique priorities to new paths. */
        int priority; /** priority - priority of the path (lower number = higher priority) */
        Coordinates begin; /** begin - starting coordinates of the path */
        Coordinates end; /** end - ending coordinates of the path */
        Pawn* pawn; /** pawn - the pawn that is moving along the path */

        /** \brief Constructor to initialize a Path with begin and end coordinates and associated Pawn.
         *  \param begin_ The starting Coordinates of the path.
         *  \param end_ The ending Coordinates of the path.
         *  \param pawn_ A pointer to the Pawn associated with this path.
         *
         *  This constructor initializes a Path object with the specified begin and end coordinates,
         *  assigns a unique priority based on the static current_priority counter, and associates it
         *  with the given Pawn.
         *
         *  \see Coordinates
         *  \see Pawn
        */
        Path(Coordinates, Coordinates, Pawn*);

        /** \brief Overloaded operator to check if two paths are opposite (reverse of each other).
         *  \param other The other Path to compare with.
         *  \return `true` if the paths are opposite, `false` otherwise.
         *
         *  This operator checks if the current path is the reverse of the other path,
         *  meaning that the begin coordinates of one path match the end coordinates of the other and vice versa.
         *
         *  \see begin
         *  \see end
        */
        bool operator|(const Path&) const;
        /** \brief Overloaded operator to compare paths based on priority.
         *  \param other The other Path to compare with.
         *  \return `true` if this path has a higher priority (lower number) than the other path, `false` otherwise.
         *
         *  This operator allows comparing two Path objects based on their priority attribute.
         *  It is useful for sorting or ordering paths when processing multiple movements.
         *
         *  \see priority
        */
        bool operator<(const Path&) const;
        /** \brief Overloaded operator to check if two paths are equal (same begin and end coordinates).
         *  \param other The other Path to compare with.
         *  \return `true` if both paths have the same begin and end coordinates, `false` otherwise.
         *
         *  This operator checks if two Path objects represent the same movement path,
         *  ignoring the priority and associated Pawn.
         *
         *  \see begin
         *  \see end
        */
        bool operator==(const Path&) const;
    };
}

namespace std {
    /** \brief Specialization of std::hash for sista::Path to allow usage in unordered containers.
     *
     * This specialization provides a hash function for the sista::Path struct, enabling its use as a key
     * in unordered containers like std::unordered_set or std::unordered_map. The hash is computed based
     * on the begin and end coordinates of the path.
     *
     * \see sista::Path
    */
    template<>
    struct hash<sista::Path> {
        std::size_t operator()(const sista::Path& k) const noexcept {
            auto h1 = std::hash<sista::Coordinates>{}(k.begin);
            auto h2 = std::hash<sista::Coordinates>{}(k.end);
            return h1 ^ (h2 << 1);
        }
    };
}

namespace sista {
    /** \class SwappableField
     *  \brief A specialized Field that handles Pawn swaps without conflicts.
     *
     *  The SwappableField class extends the Field class to manage scenarios where multiple Pawns may need to swap positions.
     *  It maintains a count of Pawns at each position and a set of paths representing Pawns that need to be moved.
     *  The class provides methods to add and remove Pawns, manage the swap paths, and simulate or apply the swaps.
     *  This class is designed to ensure that Pawn movements are handled correctly, even when multiple Pawns are
     *  attempting to move to the same position.
     *
     *  \see Field
     *  \see Pawn
     *  \see Coordinates
     *  \see Path
     */
    class SwappableField final : public Field {
    private:
        /** \brief 2D grid [y][x] to track the number of Pawns at each position. */
        std::vector<std::vector<short int>> pawnsCount;
        /** \brief Set of Paths representing Pawns that need to be swapped. */
        std::set<Path> pawnsToSwap;
        
        Coordinates firstInvalidCell(std::map<Coordinates, short int>&) const; // firstInvalidCell - find the first cell with 2 or more pawns

        /** \brief Cleans the internal state of pawnsToSwap.
         *
         *  This method clears the set of paths representing Pawns that need to be swapped.
         *  It is useful for resetting the state before simulating or applying new swaps.
         *
         *  \see pawnsToSwap
        */
        void clearPawnsToSwap(); // clearPawnsToSwap - clear the pawnsToSwap

    public:
        /** \brief Constructor to initialize the SwappableField with specified width and height.
         *  \param width The width of the field (number of columns).
         *  \param height The height of the field (number of rows).
         *
         *  This constructor initializes a SwappableField object with the given dimensions.
         *  It sets up a 2D grid to track the number of Pawns at each position and initializes
         *  the base Field class.
         *
         *  \see Field
        */
        SwappableField(int, int);
        /** \brief Destructor to clean up resources. */
        ~SwappableField();

        /** \brief Adds a Pawn to the field and updates the pawnsCount grid.
         *  \param pawn A shared pointer to the Pawn to add.
         *
         *  This method places the given Pawn on the field at its current coordinates and increments
         *  the count of Pawns at that position in the pawnsCount grid.
         *  If the coordinates are already occupied, the existing Pawn will be replaced.
         *
         *  \warning The Pawn's coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method takes a shared pointer to manage the Pawn's memory automatically.
         *
         *  \see Field::addPawn
         *  \see Pawn
        */
        void addPawn(std::shared_ptr<Pawn>) override; // addPawn - add a pawn to the field
        /** \brief Removes a Pawn from the field and updates the pawnsCount grid.
         *  \param pawn A pointer to the Pawn to remove.
         *
         *  This method removes the specified Pawn from the field based on its coordinates and decrements
         *  the count of Pawns at that position in the pawnsCount grid.
         *  If the Pawn is not found at its coordinates, no action is taken.
         *
         *  \warning The Pawn's coordinates must be valid (within the field bounds) as they are not validated here.
         *  \note The method does not delete the Pawn object, it only removes it from the field.
         *
         *  \see Field::removePawn
         *  \see Pawn
        */
        void removePawn(Pawn*) override; // removePawn - remove a pawn from the field

        /** \brief Moves a Pawn to new coordinates and updates the pawnsCount grid.
         *  \param pawn A pointer to the Pawn to move.
         *  \param coordinates The new Coordinates to move the Pawn to.
         *
         *  This method moves the specified Pawn to the given coordinates on the field
         *  and updates the pawnsCount grid accordingly by decrementing the count at the
         *  old position and setting it to 1 at the new position.
         *
         *  \throws `std::invalid_argument` if the coordinates are occupied by another Pawn or out of bounds.
         *
         *  \see Field::movePawn
         *  \see Pawn
         *  \see Coordinates
        */
        void movePawn(Pawn*, const Coordinates&); // movePawn - move a pawn to the coordinates
        /** \brief Moves a Pawn to new coordinates and updates the pawnsCount grid.
         *  \param pawn A pointer to the Pawn to move.
         *  \param y The new y coordinate (row) to move the Pawn to.
         *  \param x The new x coordinate (column) to move the Pawn to.
         *
         *  This method moves the specified Pawn to the given coordinates on the field
         *  and updates the pawnsCount grid accordingly by decrementing the count at the
         *  old position and setting it to 1 at the new position.
         *
         *  \throws `std::invalid_argument` if the coordinates are occupied by another Pawn or out of bounds.
         *
         *  \note This method is just a convenience overload that constructs a Coordinates object internally.
         *
         *  \see Field::movePawn
         *  \see Pawn
         *  \see Coordinates
        */
        void movePawn(Pawn*, unsigned short, unsigned short); // movePawn - move a pawn to the coordinates

        /** \brief Adds a Pawn to the set of pawnsToSwap.
         *  \param pawn A pointer to the Pawn to add.
         *  \param destination The Coordinates representing the destination of the Pawn.
         *
         *  This method adds the specified Pawn and its target coordinates to the set of pawnsToSwap,
         *  indicating that the Pawn needs to be moved. The method ensures that no duplicate entries
         *  are added and handles conflicts where multiple Pawns may want to move to the same position.
         *
         *  \throws `std::invalid_argument` if the pawn is a nullptr.
         *  \throws `std::out_of_range` if the destination coordinates are out of bounds.
         *
         *  \note If the Pawn's current coordinates are the same as the target coordinates, it is ignored.
         *
         *  \see Pawn
         *  \see Coordinates
         *  \see pawnsToSwap
        */
        void addPawnToSwap(Pawn*, const Coordinates&); // addPawnToSwap - add a pawn to the pawnsToSwap
        /** \brief Adds a Path to the set of pawnsToSwap.
         *  \param path A Path representing the Pawn movement to add.
         *
         *  This method adds the specified Path to the set of pawnsToSwap, indicating that the Pawn
         *  associated with the path needs to be moved. The method ensures that no duplicate paths
         *  are added and handles conflicts where multiple Pawns may want to move to the same position.
         *
         *  \throws `std::invalid_argument` if the pawn is a nullptr.
         *  \throws `std::out_of_range` if the destination coordinates of the path are out of bounds.
         *
         *  \note If the start and end coordinates of the path are the same, the path is ignored.
         *
         *  \see Path
         *  \see pawnsToSwap
        */
        void addPawnToSwap(Path&); // addPawnToSwap - add a path to the pawnsToSwap

        /** \brief Simulates the swaps of the pawnsToSwap and removes unfeasible paths.
         *
         *  This method processes the set of pawnsToSwap to simulate the movements of the Pawns.
         *  It identifies and removes any paths that cannot be executed due to conflicts or cycles,
         *  ensuring that only feasible swaps remain in the set.
         *
         *  \todo Make the function return the paths that were removed as unfeasible.
         *
         *  \see pawnsToSwap
        */
        void simulateSwaps(); // simulateSwaps - simulate the swaps of the pawnsToSwap
        /** \brief Applies the swaps of the pawnsToSwap to the field.
         *
         *  This method executes the movements of the Pawns as specified in the pawnsToSwap set.
         *  It updates the positions of the Pawns on the field and clears the pawnsToSwap set afterward.
         *
         *  \see pawnsToSwap
         *  \see Path
        */
        void applySwaps(); // applySwaps - apply the swaps of the pawnsToSwap

        /** \brief Swaps two Pawns at the specified coordinates.
         *  \param first The Coordinates of the first Pawn.
         *  \param second The Coordinates of the second Pawn.
         *
         *  This method swaps the positions of the two Pawns located at the given coordinates on the field.
         *
         *  \warning The coordinates must be valid (within the field bounds) as they are not validated here.
         *
         *  \see Pawn
         *  \see Coordinates
        */
        void swapTwoPawns(const Coordinates&, const Coordinates&);
        /** \brief Swaps two Pawns.
         *  \param first A pointer to the first Pawn.
         *  \param second A pointer to the second Pawn.
         *
         *  This method swaps the positions of the two specified Pawns on the field.
         *
         *  \warning The Pawns must have valid coordinates (within the field bounds) as they are not validated here.
         *
         *  \see Pawn
        */
        void swapTwoPawns(Pawn*, Pawn*);
    };
};
