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
        ~Field();

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

        virtual void addPawn(std::shared_ptr<Pawn>);
        virtual void removePawn(Pawn*);
        virtual void removePawn(const Coordinates&);
        virtual void erasePawn(Pawn*);
        virtual void erasePawn(const Coordinates&);

        void addPrintPawn(std::shared_ptr<Pawn>);
        void rePrintPawn(Pawn*);

        void movePawn(Pawn*, const Coordinates&);
        void movePawn(Pawn*, unsigned short, unsigned short);

        void movePawnBy(Pawn*, const Coordinates&);
        void movePawnBy(Pawn*, unsigned short, unsigned short);

        // 🎮 movePawnBy() with arcade game effects on coordinates overflow
        void movePawnBy(Pawn*, const Coordinates&, Effect);
        void movePawnBy(Pawn*, short int, short int, Effect);
        
        void movePawnFromTo(const Coordinates&, const Coordinates&);
        void movePawnFromTo(unsigned short, unsigned short, unsigned short, unsigned short);
        
        // ℹ️ - The following function calculates coordinates, but does not apply them to the pawns
        Coordinates movingByCoordinates(Pawn*, short int, short int) const; // movingByCoordinates - calculate the coordinates of a pawn after a movement
        // ℹ️ - The following function calculates coordinates, but does not apply them to the pawns
        Coordinates movingByCoordinates(Pawn*, short int, short int, Effect) const; // movingByCoordinates - calculate the coordinates of a pawn after a movement

        Pawn* getPawn(const Coordinates&) const;
        Pawn* getPawn(unsigned short, unsigned short) const;

        bool isOccupied(const Coordinates&) const;
        bool isOccupied(unsigned short, unsigned short) const;
        bool isOccupied(short int, short int) const;

        bool isOutOfBounds(const Coordinates&) const;
        bool isOutOfBounds(unsigned short, unsigned short) const;
        bool isOutOfBounds(short int, short int) const;

        bool isFree(const Coordinates&) const;
        bool isFree(unsigned short, unsigned short) const;
        bool isFree(short int, short int) const;

        // ⚠️ This throws an exception if the coordinates are invalid
        void validateCoordinates(const Coordinates&) const;
        void validateCoordinates(unsigned short, unsigned short) const;
    };    

    struct Path { // Path struct - begin and end Coordinates of a path
        static long long int current_priority; // current_priority - priority of the current Path [counter]
        int priority; // priority - priority of the Path (used in operator<)
        Coordinates begin;
        Coordinates end;
        Pawn* pawn; // pawn - the pawn that is moving along the path

        Path(Coordinates, Coordinates, Pawn*);

        bool operator|(const Path&) const; // operator| - check if two paths are opposite
        bool operator<(const Path&) const; // operator< - check if a path has a lower priority than another path
        bool operator==(const Path&) const; // operator== - check if two paths are equal (both begin and end coordinates are the same, ignores priority and pawn)
    };
}

namespace std {
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
    class SwappableField final : public Field { // SwappableField class - a Field with no Pawn Swap issues [final class]
    private:
        // pawnsCount[y][x] = 0 - no pawns on the pawns[y][x]
        std::vector<std::vector<short int>> pawnsCount; // pawnsCount[y][x] - number of pawns at pawns[y][x]
        // NOTE: short int instead of bool because of the possibility of having more than 2 pawns on the same field during swap trials
        std::set<Path> pawnsToSwap; // pawnsToSwap - pawns that need to be swapped

        Coordinates firstInvalidCell(std::map<Coordinates, short int>&) const; // firstInvalidCell - find the first cell with 2 or more pawns

    public:
        SwappableField(int, int); // SwappableField - constructor (width, height)
        ~SwappableField();

        void addPawn(std::shared_ptr<Pawn>) override; // addPawn - add a pawn to the field
        void removePawn(Pawn*) override; // removePawn - remove a pawn from the field

        void clearPawnsToSwap(); // clearPawnsToSwap - clear the pawnsToSwap

        void addPawnToSwap(Pawn*, const Coordinates&); // addPawnToSwap - add a pawn to the pawnsToSwap
        void addPawnToSwap(Path&); // addPawnToSwap - add a path to the pawnsToSwap
        void simulateSwaps(); // simulateSwaps - simulate the swaps of the pawnsToSwap
        void applySwaps(); // applySwaps - apply the swaps of the pawnsToSwap

        void swapTwoPawns(const Coordinates&, const Coordinates&);
        void swapTwoPawns(Pawn*, Pawn*);
    };
};
