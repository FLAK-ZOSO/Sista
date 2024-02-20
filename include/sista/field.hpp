#pragma once

#include <vector> // std::vector
#include <queue> // std::queue, std::priority_queue
#include <algorithm> // std::sort
#include "pawn.hpp" // Pawn
#include "border.hpp" // Border
#include "cursor.hpp" // Cursor

#define PACMAN_EFFECT 0 // Pacman effect when a coordinate overflows
#define MATRIX_EFFECT 1 // Classic C style matrix effect when a coordinate overflows

namespace sista {
    class Field { // Field class - represents the field [parent class]
    protected:
        std::vector<std::vector<Pawn*>> pawns; // Matrix of pawns
        Cursor cursor; // Cursor
        int width; // Width of the matrix
        int height; // Height of the matrix

    public:
        void clear();
        void reset();

        Field(int, int);
        ~Field();

        void print();
        void print(char);
        void print(Border&);

        virtual void addPawn(Pawn*);
        virtual void removePawn(Pawn*);
        virtual void erasePawn(Pawn*);

        void addPrintPawn(Pawn*);

        void movePawn(Pawn*, Coordinates&);
        void movePawn(Pawn*, Coord&);
        void movePawn(Pawn*, unsigned short, unsigned short);

        void movePawnBy(Pawn*, Coordinates&);
        void movePawnBy(Pawn*, Coord&);
        void movePawnBy(Pawn*, unsigned short, unsigned short);

        // 🎮 movePawnBy() with arcade game effects on coordinates overflow
        void movePawnBy(Pawn*, Coordinates&, bool);
        void movePawnBy(Pawn*, Coord&, bool);
        void movePawnBy(Pawn*, short int, short int, bool);

        void movePawnFromTo(Coordinates&, Coordinates&);
        void movePawnFromTo(Coord&, Coord&);
        void movePawnFromTo(unsigned short, unsigned short, unsigned short, unsigned short);

        Pawn* getPawn(Coordinates&);
        Pawn* getPawn(Coord&);
        Pawn* getPawn(unsigned short, unsigned short);

        bool isOccupied(Coordinates&);
        bool isOccupied(Coord&);
        bool isOccupied(unsigned short, unsigned short);
        bool isOccupied(short int, short int);

        bool isOutOfBounds(Coordinates&);
        bool isOutOfBounds(Coord&);
        bool isOutOfBounds(unsigned short, unsigned short);
        bool isOutOfBounds(short int, short int);

        bool isFree(Coordinates&);
        bool isFree(Coord&);
        bool isFree(unsigned short, unsigned short);
        bool isFree(short int, short int);

        // ⚠️ This throws an exception if the coordinates are invalid
        void validateCoordinates(Coordinates&);
        void validateCoordinates(Coord&);
        void validateCoordinates(unsigned short, unsigned short);
    };

    struct Path { // Path struct - begin and end Coordinates of a path
        static int current_priority; // current_priority - priority of the current Path [counter]
        int priority; // priority - priority of the Path (used in operator<)
        Coordinates begin;
        Coordinates end;
        Pawn* pawn; // pawn - the pawn that is moving along the path

        Path(Coordinates, Coordinates, Pawn*);

        bool operator|(const Path&) const; // operator| - check if two paths are opposite
        bool operator<(const Path&) const; // operator< - check if a path has a lower priority than another path
    };


    class SwappableField : public Field { // SwappableField class - a Field with no Pawn Swap issues [final class]
    private:
        // pawnsCount[y][x] = 0 - no pawns on the pawns[y][x]
        std::vector<std::vector<short int>> pawnsCount; // pawnsCount[y][x] - number of pawns at pawns[y][x]
        // NOTE: short int instead of bool because of the possibility of having more than 2 pawns on the same field during swap trials
        std::vector<Path> pawnsToSwap; // pawnsToSwap - pawns that need to be swapped

        Coord firstInvalidCell(std::vector<std::vector<short int>>&); // firstInvalidCell - find the first cell with 2 or more pawns

    public:
        SwappableField(int, int);
        ~SwappableField();

        void addPawn(Pawn*) override; // addPawn - add a pawn to the field
        void removePawn(Pawn*) override; // removePawn - remove a pawn from the field

        void clearPawnsToSwap(); // clearPawnsToSwap - clear the pawnsToSwap

        // ℹ️ - The following function calculates coordinates, but does not apply them to the pawns
        Coordinates movingByCoordinates(Pawn*, short int, short int); // movingByCoordinates - calculate the coordinates of a pawn after a movement
        // ℹ️ - The following function calculates coordinates, but does not apply them to the pawns
        Coordinates movingByCoordinates(Pawn*, short int, short int, bool); // movingByCoordinates - calculate the coordinates of a pawn after a movement

        void addPawnToSwap(Pawn*, Coordinates&); // addPawnToSwap - add a pawn to the pawnsToSwap
        void addPawnToSwap(Path&); // addPawnToSwap - add a path to the pawnsToSwap
        void simulateSwaps(); // simulateSwaps - simulate the swaps of the pawnsToSwap
        void applySwaps(); // applySwaps - apply the swaps of the pawnsToSwap

        void swapTwoPawns(Coordinates&, Coordinates&);
        void swapTwoPawns(Pawn*, Pawn*);
    };
};
