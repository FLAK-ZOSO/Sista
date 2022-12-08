#pragma once

#include <vector> // std::vector
#include "pawn.hpp" // Pawn
#include "border.hpp" // Border


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

    void movePawn(Pawn* pawn, Coordinates coordinates) { // Move a pawn to the coordinates
        removePawn(pawn); // Remove the pawn from the matrix
        pawn->coordinates = coordinates;
        addPawn(pawn); // Add the pawn to the matrix
    }
    void movePawn(Pawn* pawn, Coord coordinates) { // Move a pawn to the coordinates
        movePawn(pawn, Coordinates(coordinates)); // Move the pawn to the coordinates
    }
    void movePawn(Pawn* pawn, unsigned short y, unsigned short x) { // Move a pawn to the coordinates
        movePawn(pawn, Coordinates(y, x)); // Move the pawn to the coordinates
    }

    Pawn* getPawn(Coordinates coordinates) { // Get the pawn at the coordinates
        return pawns[coordinates.y][coordinates.x]; // Return the pawn at the coordinates
    }
    bool isOccupied(Coordinates coordinates) { // Check if the coordinates are occupied
        return (getPawn(coordinates) != nullptr); // Return if the coordinates are occupied
    }
    bool isOccupied(Coord coordinates) { // Check if the coordinates are occupied
        return isOccupied(Coordinates(coordinates)); // Return if the coordinates are occupied
    }
    bool isOccupied(unsigned short y, unsigned short x) { // Check if the coordinates are occupied
        return isOccupied(Coordinates(y, x)); // Return if the coordinates are occupied
    }

    bool isOutOfBounds(Coordinates coordinates) { // Check if the coordinates are out of bounds
        return (coordinates.y < 0 || coordinates.y >= height || coordinates.x < 0 || coordinates.x >= width); // Return if the coordinates are out of bounds
    }
    bool isOutOfBounds(Coord coordinates) { // Check if the coordinates are out of bounds
        return isOutOfBounds(Coordinates(coordinates)); // Return if the coordinates are out of bounds
    }
    bool isOutOfBounds(unsigned short y, unsigned short x) { // Check if the coordinates are out of bounds
        return isOutOfBounds(Coordinates(y, x)); // Return if the coordinates are out of bounds
    }

    bool isFree(Coordinates coordinates) { // Check if the coordinates are occupied or out of bounds
        return !(isOutOfBounds(coordinates) || isOccupied(coordinates)); // Return if the coordinates are occupied or out of bounds
    }
    bool isFree(Coord coordinates) { // Check if the coordinates are occupied or out of bounds
        return isFree(Coordinates(coordinates)); // Return if the coordinates are occupied or out of bounds
    }
    bool isFree(unsigned short y, unsigned short x) { // Check if the coordinates are occupied or out of bounds
        return isFree(Coordinates(y, x)); // Return if the coordinates are occupied or out of bounds
    }
};