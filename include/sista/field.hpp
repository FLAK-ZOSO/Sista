#pragma once

#include <vector> // std::vector
#include <memory> // std::shared_ptr, std::move
#include "pawn.hpp" // Pawn
#include "border.hpp" // Border
#include "cursor.hpp" // Cursor

namespace sista {
    enum class Effect { // Effect enum - effect when a coordinate is out of bounds
        PACMAN = 0, // Pacman effect when a coordinate overflows
        MATRIX = 1 // Classic C style matrix effect when a coordinate overflows
    };

    class Field { // Field class - represents the field [parent class]
    protected:
        std::vector<std::vector<std::shared_ptr<Pawn>>> pawns; // Matrix of pawns
        Cursor cursor; // Cursor
        int width; // Width of the matrix
        int height; // Height of the matrix

        void cleanCoordinates(const Coordinates&) const;
        void cleanCoordinates(unsigned short, unsigned short) const;

    public:
        void clear();
        void reset();

        Field(int, int); // Field - constructor (width, height)
        ~Field();

        void print() const;
        void print(char) const;
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
        static int current_priority; // current_priority - priority of the current Path [counter]
        int priority; // priority - priority of the Path (used in operator<)
        Coordinates begin;
        Coordinates end;
        Pawn* pawn; // pawn - the pawn that is moving along the path

        Path(Coordinates, Coordinates, Pawn*);

        bool operator|(const Path&) const; // operator| - check if two paths are opposite
        bool operator<(const Path&) const; // operator< - check if a path has a lower priority than another path
    };    


    class SwappableField final : public Field { // SwappableField class - a Field with no Pawn Swap issues [final class]
    private:
        // pawnsCount[y][x] = 0 - no pawns on the pawns[y][x]
        std::vector<std::vector<short int>> pawnsCount; // pawnsCount[y][x] - number of pawns at pawns[y][x]
        // NOTE: short int instead of bool because of the possibility of having more than 2 pawns on the same field during swap trials
        std::vector<Path> pawnsToSwap; // pawnsToSwap - pawns that need to be swapped

        Coordinates firstInvalidCell(std::vector<std::vector<short int>>&) const; // firstInvalidCell - find the first cell with 2 or more pawns

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
