#pragma once

#include <vector> // std::vector
#include "pawn.hpp" // Pawn
#include "border.hpp" // Border

#define PACMAN_EFFECT 0 // Pacman effect when a coordinate overflows
#define MATRIX_EFFECT 1 // Classic C style matrix effect when a coordinate overflows


class Field { // Field class - represents the field
public:
    std::vector<std::vector<Pawn*>> pawns; // Matrix of pawns
    int width; // Width of the matrix
    int height; // Height of the matrix

    void clear() { // Clear the matrix
        for (auto& row: pawns) // For each row
            for (auto& pawn: row) // For each pawn
                pawn = nullptr; // Set the pawn to nullptr
    }

    Field(int width_, int height_): width(width_), height(height_) { // Constructor
        pawns.resize(height); // Resize the vector
        for (int i = 0; i < height; i++) // For each row
            pawns[i].resize(width); // Resize the vector
        this->clear(); // Clear the matrix
    }

    void print() { // Print the matrix
        ANSI::reset(); // Reset the settings
        bool previousPawn = false; // If the previous element was a Pawn
        for (auto& row: pawns) { // For each row
            for (auto& pawn: row) { // For each pawn
                if (pawn != nullptr) { // If the pawn is not nullptr
                    pawn->print(); // Print the pawn
                    previousPawn = true; // Set the previousPawn to true
                } else { // If the pawn is nullptr
                    if (previousPawn) { // If the previous element was a Pawn
                        ANSI::reset(); // Reset the settings
                        previousPawn = false; // Set the previousPawn to false
                    }
                    std::cout << ' ';
                }
            }
            std::cout << '\n';
        }
        ANSI::reset(); // Reset the settings
        std::cout << std::flush; // Flush the output
    }
    void print(char border) { // Prints with custom border
        ANSI::reset(); // Reset the settings
        std::cout << '\n';
        for (int i=0; i<width+2; i++) // For each row
            std::cout << border; // Print the border
        std::cout << '\n';
        bool previousPawn = false; // If the previous element was a Pawn
        for (auto& row: pawns) { // For each row
            std::cout << border; // Print the border
            for (auto& pawn: row) { // For each pawn
                if (pawn != nullptr) { // If the pawn is not nullptr
                    pawn->print(); // Print the pawn
                    previousPawn = true; // Set the previousPawn to true
                } else { // If the pawn is nullptr
                    if (previousPawn) { // If the previous element was a Pawn
                        ANSI::reset(); // Reset the settings
                        previousPawn = false; // Set the previousPawn to false
                    }
                    std::cout << ' ';
                }
            }
            ANSI::reset(); // Reset the settings
            std::cout << border << '\n'; // Print the border and a new line
        }
        for (int i=0; i<width+2; i++) // For each row
            std::cout << border; // Print the border
        std::cout << std::flush; // Flush the output
    }
    void print(Border& border) { // Prints with custom border
        ANSI::reset(); // Reset the settings
        std::cout << '\n';
        border.print(); // Print the border
        for (int i=0; i<width+1; i++) // For each row
            border.print(true); // Print the border
        std::cout << '\n';
        bool previousPawn = true; // If the previous element was a Pawn
        for (auto& row: pawns) { // For each row
            border.print(); // Print the border
            for (auto& pawn: row) { // For each pawn
                if (pawn != nullptr) { // If the pawn is not nullptr
                    pawn->print(); // Print the pawn
                    previousPawn = true; // Set the previousPawn to true
                } else { // If the pawn is nullptr
                    if (previousPawn) { // If the previous element was a Pawn
                        ANSI::reset(); // Reset the settings
                        previousPawn = false; // Set the previousPawn to false
                    }
                    std::cout << ' ';
                }
            }
            border.print();
            previousPawn = true; // Set the previousPawn to true
            std::cout << '\n';
        }
        border.print(); // Print the border
        for (int i=0; i<width+1; i++) // For each row
            border.print(true); // Print the border
        ANSI::reset(); // Reset the settings
        std::cout << std::flush; // Flush the output
    }

    void addPawn(Pawn* pawn) { // Add a pawn to the matrix
        pawns[pawn->coordinates.y][pawn->coordinates.x] = pawn; // Set the pawn to the coordinates
    }
    void removePawn(Pawn* pawn) { // Remove a pawn from the matrix
        pawns[pawn->coordinates.y][pawn->coordinates.x] = nullptr; // Set the pawn to nullptr
    }

    void movePawn(Pawn* pawn, Coordinates& coordinates) { // Move a pawn to the coordinates
        try {
            validateCoordinates(coordinates);
        } catch (const std::invalid_argument& e) {
            if (pawn->coordinates == coordinates) // If the coordinates are the same...
                return; // ...the cell is occupied by the pawn, so no need to move it
            // ...otherwise, if the coordinates are occupied by another pawn, throw an exception
            throw std::invalid_argument("The coordinates are occupied by another pawn");
        }
        removePawn(pawn); // Remove the pawn from the matrix
        pawn->coordinates = coordinates;
        addPawn(pawn); // Add the pawn to the matrix
    }
    void movePawn(Pawn* pawn, Coord& coordinates) { // Move a pawn to the coordinates
        // [Call the original function because it's anyway declaring a new Coordinates object]
        Coord coordinates_ = coordinates;
        movePawn(pawn, coordinates_);
    }
    void movePawn(Pawn* pawn, unsigned short y, unsigned short x) { // Move a pawn to the coordinates
        Coordinates coordinates_(y, x);
        movePawn(pawn, coordinates_);
    }

    void movePawnBy(Pawn* pawn, Coordinates& coordinates) { // Move a pawn by the coordinates
        Coordinates coordinates_ = pawn->coordinates + coordinates;
        movePawn(pawn, coordinates_);
    }
    void movePawnBy(Pawn* pawn, Coord& coordinates) {
        Coordinates coordinates_(coordinates);
        movePawnBy(pawn, coordinates_);
    }
    void movePawnBy(Pawn* pawn, unsigned short y, unsigned short x) {
        movePawn(pawn, pawn->coordinates.y + y, pawn->coordinates.x + x);
    }

    // 🎮 movePawnBy() with arcade game effects on coordinates overflow
    void movePawnBy(Pawn* pawn, Coordinates& coordinates, bool effect) {
        movePawnBy(pawn, coordinates.y, coordinates.x, effect);
    }
    void movePawnBy(Pawn* pawn, Coord& coordinates, bool effect) {
        Coordinates coordinates_(coordinates);
        movePawnBy(pawn, coordinates_, effect);
    }
    void movePawnBy(Pawn* pawn, short int y, short int x, bool effect) {
        short int y_ = pawn->coordinates.y + y;
        short int x_ = pawn->coordinates.x + x;
        if (!isOutOfBounds(y_, x_)) { // If the coordinates are not out of bounds...
            movePawn(pawn, y_, x_); // ...no need to apply any effect
        } else if (effect == PACMAN_EFFECT) { // If the effect is PACMAN_EFFECT...
            // ...well, you know how Pac Man works
            if (x_ < 0) {
                x_ = width-1-(x_ % width);
            } else if (x_ >= width) {
                x_ %= width;
            }
            if (y_ < 0) {
                y_ = height-1-(y_ % width);
            } else if (y_ >= height) {
                y_ %= height;
            }
        } else if (effect == MATRIX_EFFECT) {
            short int y = y_;
            short int x = x_;
            if (x_ < 0) {
                x_ = width+(x_ % width);
                y_ = y + (short int)(x / width) - 1;
            } else if (x_ >= width) {
                x_ %= width;
                y_ = y + (short int)(x / width);
            }
            // This [y_] could lead to a coordinate out of bounds...
            validateCoordinates(y_, x_); // ...so we need to validate it
        }
        movePawn(pawn, y_, x_);
    }

    void movePawnFromTo(Coordinates& coordinates, Coordinates& newCoordinates) {
        movePawn(getPawn(coordinates), newCoordinates);
    }
    void movePawnFromTo(Coord& coordinates, Coord& newCoordinates) {
        movePawn(getPawn(coordinates), newCoordinates);
    }
    void movePawnFromTo(unsigned short y, unsigned short x, unsigned short newY, unsigned short newX) {
        movePawn(getPawn(y, x), newY, newX);
    }

    Pawn* getPawn(Coordinates& coordinates) { // Get the pawn at the coordinates
        return pawns[coordinates.y][coordinates.x]; // Return the pawn at the coordinates
    }
    Pawn* getPawn(Coord& coordinates) {
        return pawns[coordinates.first][coordinates.second];
    }
    Pawn* getPawn(unsigned short y, unsigned short x) {
        return pawns[y][x];
    }

    bool isOccupied(Coordinates& coordinates) { // Check if the coordinates are occupied
        return (getPawn(coordinates) != nullptr);
    }
    bool isOccupied(Coord& coordinates) {
        return (getPawn(coordinates) != nullptr);
    }
    bool isOccupied(unsigned short y, unsigned short x) {
        return (getPawn(y, x) != nullptr);
    }
    bool isOccupied(short int y, short int x) {
        return (getPawn(y, x) != nullptr);
    }

    bool isOutOfBounds(Coordinates& coordinates) { // Check if the coordinates are out of bounds
        return (coordinates.y >= height || coordinates.x >= width); // Return if the coordinates are out of bounds
    }
    bool isOutOfBounds(Coord& coordinates) {
        return (coordinates.first >= height || coordinates.second >= width);
    }
    bool isOutOfBounds(unsigned short y, unsigned short x) {
        return  (y >= height || x >= width);
    }
    bool isOutOfBounds(short int y, short int x) {
        return  (y < 0 || y >= height || x < 0 || x >= width);
    }

    bool isFree(Coordinates& coordinates) { // Check if the coordinates are occupied or out of bounds
        return !(isOutOfBounds(coordinates) || isOccupied(coordinates));
    }
    bool isFree(Coord& coordinates) {
        return !(isOutOfBounds(coordinates) || isOccupied(coordinates));
    }
    bool isFree(unsigned short y, unsigned short x) {
        return !(isOutOfBounds(y, x) || isOccupied(y, x));
    }
    bool isFree(short int y, short int x) {
        return !(isOutOfBounds(y, x) || isOccupied(y, x));
    }

    // ⚠️ This throws an exception if the coordinates are invalid
    void validateCoordinates(Coordinates& coordinates) { // Validate the coordinates
        if (isOutOfBounds(coordinates)) // If the coordinates are out of bounds
            throw std::out_of_range("Coordinates are out of bounds");
        if (isOccupied(coordinates)) // If the coordinates are occupied
            throw std::invalid_argument("Coordinates are occupied");
    }
    void validateCoordinates(Coord& coordinates) {
        if (isOutOfBounds(coordinates))
            throw std::out_of_range("Coordinates are out of bounds");
        if (isOccupied(coordinates))
            throw std::invalid_argument("Coordinates are occupied");
    }
    void validateCoordinates(unsigned short y, unsigned short x) {
        if (isOutOfBounds(y, x))
            throw std::out_of_range("Coordinates are out of bounds");
        if (isOccupied(y, x))
            throw std::invalid_argument("Coordinates are occupied");
    }
};