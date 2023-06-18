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
        void clear() { // Clear the matrix
            for (auto& row: pawns) // For each row
                for (auto& pawn: row) // For each pawn
                    pawn = nullptr; // Set the pawn to nullptr
        }
        void reset() {
            for (auto& row: pawns) { // For each row
                for (auto& pawn: row) {
                    if (pawn != nullptr) // If the pawn is not nullptr
                        delete pawn; // Delete the pawn
                    pawn = nullptr; // Set the pawn to nullptr
                }
            }        
        }

        Field(int width_, int height_): width(width_), height(height_) { // Constructor
            pawns.resize(height); // Resize the vector
            for (int i = 0; i < height; i++) // For each row
                pawns[i].resize(width); // Resize the vector
            this->clear(); // Clear the matrix
        }
        ~Field() {
            for (int i = 0; i < (int)pawns.size(); i++) // For each row
                for (int j = 0; j < (int)pawns[i].size(); j++) // For each pawn
                    delete pawns[i][j]; // Delete the pawn
            pawns.clear(); // Clear the pawns
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
                border.print(false); // Print the border
            ANSI::reset(); // Reset the settings
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
                ANSI::reset(); // Reset the settings
                previousPawn = true; // Set the previousPawn to true
                std::cout << '\n';
            }
            border.print(); // Print the border
            for (int i=0; i<width+1; i++) // For each row
                border.print(false); // Print the border
            ANSI::reset(); // Reset the settings
            std::cout << std::flush; // Flush the output
        }

        virtual void addPawn(Pawn* pawn) { // Add a pawn to the matrix
            pawns[pawn->getCoordinates().y][pawn->getCoordinates().x] = pawn; // Set the pawn to the coordinates
        }
        virtual void removePawn(Pawn* pawn) { // Remove a pawn from the matrix
            pawns[pawn->getCoordinates().y][pawn->getCoordinates().x] = nullptr; // Set the pawn to nullptr
        }

        void addPrintPawn(Pawn* pawn) { // Add a pawn to the matrix and print it
            addPawn(pawn); // Add the pawn to the matrix
            this->cursor.set(pawn->getCoordinates()); // Set the cursor to the pawn's coordinates
            pawn->print(); // Print the pawn
        }

        void movePawn(Pawn* pawn, Coordinates& coordinates) { // Move a pawn to the coordinates
            try {
                validateCoordinates(coordinates);
            } catch (const std::invalid_argument& e) {
                if (pawn->getCoordinates() == coordinates) // If the coordinates are the same...
                    return; // ...the cell is occupied by the pawn, so no need to move it
                // ...otherwise, if the coordinates are occupied by another pawn, throw an exception
                throw std::invalid_argument("The coordinates are occupied by another pawn");
            }
            // Cursor ANSI stuff
            cursor.set(pawn->getCoordinates()); // Set the cursor to the pawn's coordinates
            ANSI::reset(); // Reset the settings for that cell
            std::cout << ' '; // Print a space to clear the cell
            cursor.set(coordinates); // Set the cursor to the coordinates
            pawn->print(); // Print the pawn

            // sista::Field stuff
            removePawn(pawn); // Remove the pawn from the matrix
            pawn->setCoordinates(coordinates); // Set the pawn's
            addPawn(pawn); // Add the pawn to the matrix
        }
        void movePawn(Pawn* pawn, Coord& coordinates) { // Move a pawn to the coordinates
            // [Call the original function because it's anyway declaring a new Coordinates object]
            Coordinates coordinates_(coordinates.first, coordinates.second);
            movePawn(pawn, coordinates_);
        }
        void movePawn(Pawn* pawn, unsigned short y, unsigned short x) { // Move a pawn to the coordinates
            Coordinates coordinates_(y, x);
            movePawn(pawn, coordinates_);
        }

        void movePawnBy(Pawn* pawn, Coordinates& coordinates) { // Move a pawn by the coordinates
            Coordinates coordinates_ = pawn->getCoordinates() + coordinates;
            movePawn(pawn, coordinates_);
        }
        void movePawnBy(Pawn* pawn, Coord& coordinates) {
            Coordinates coordinates_(coordinates);
            movePawnBy(pawn, coordinates_);
        }
        void movePawnBy(Pawn* pawn, unsigned short y, unsigned short x) {
            movePawn(pawn, pawn->getCoordinates().y + y, pawn->getCoordinates().x + x);
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
            short int y_ = pawn->getCoordinates().y + y;
            short int x_ = pawn->getCoordinates().x + x;
            if (!isOutOfBounds(y_, x_)) { // If the coordinates are not out of bounds...
                movePawn(pawn, y_, x_); // ...no need to apply any effect
            } else if (effect == PACMAN_EFFECT) { // If the effect is PACMAN_EFFECT...
                // ...well, you know how Pac Man works
                if (x_ < 0) {
                    x_ = width-1-(x_ % width);
                    if (x_ == width)
                        x_ = width - 1;
                } else if (x_ >= width) {
                    x_ %= width;
                }
                if (y_ < 0) {
                    y_ = height-1-(y_ % width);
                    if (y_ == height)
                        y_ = height -1;
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

    struct Path { // Path struct - begin and end Coordinates of a path
        static int current_priority; // current_priority - priority of the current Path [counter]
        int priority; // priority - priority of the Path (used in operator<)
        Coordinates begin;
        Coordinates end;
        Pawn* pawn; // pawn - the pawn that is moving along the path

        Path(Coordinates begin_, Coordinates end_, Pawn* pawn_) : begin(begin_), end(end_), pawn(pawn_) {
            priority = current_priority++;
        }

        bool operator|(const Path& other) const { // operator| - check if two paths are switching each other
            return (
                (this->begin == other.begin && this->end == other.end) ||
                (this->begin == other.end && this->end == other.begin)
            );
        }
        bool operator<(const Path& other) const { // operator< - give priority order to paths
            return this->priority < other.priority;
        }
    };
    int Path::current_priority = 0; // priority - priority of the current Path


    class SwappableField : public Field { // SwappableField class - a Field with no Pawn Swap issues [final class]
    private:
        // pawnsCount[y][x] = 0 - no pawns on the pawns[y][x]
        std::vector<std::vector<short int>> pawnsCount; // pawnsCount[y][x] - number of pawns at pawns[y][x]
        // NOTE: short int instead of bool because of the possibility of having more than 2 pawns on the same field during swap trials
        std::vector<Path> pawnsToSwap; // pawnsToSwap - pawns that need to be swapped

        Coord firstInvalidCell(std::vector<std::vector<short int>>& pawnsCount_) { // lowerBound - find the first cell with a value >= value
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    if (pawnsCount_[y][x] >= 2) {
                        return Coord(y, x);
                    }
                }
            }
            throw std::runtime_error("No invalid cells found");
        }

    public:
        SwappableField(int width, int height) : Field(width, height) {
            pawnsCount.resize(height);
            for (int y = 0; y < height; y++) {
                pawnsCount[y].resize(width);
                for (int x = 0; x < width; x++) {
                    pawnsCount[y][x] = 0;
                }
            }
        }
        ~SwappableField() {
            for (int i = 0; i < (int)pawns.size(); i++) // For each row
                for (int j = 0; j < (int)pawns[i].size(); j++) // For each pawn
                    delete pawns[i][j]; // Delete the pawn
            pawns.clear(); // Clear the pawns
        }

        void addPawn(Pawn* pawn) override { // addPawn - add a pawn to the field
            Field::addPawn(pawn);
            pawnsCount[pawn->getCoordinates().y][pawn->getCoordinates().x]++;
        }
        void removePawn(Pawn* pawn) override { // removePawn - remove a pawn from the field
            Field::removePawn(pawn);
            pawnsCount[pawn->getCoordinates().y][pawn->getCoordinates().x]--;
        }

        void clearPawnsToSwap() { // clearPawnsToSwap - clear the pawnsToSwap
            Path::current_priority = 0;
            pawnsToSwap.clear();
        }

        // ℹ️ - The following function calculates coordinates, but does not apply them to the pawns
        Coordinates movingByCoordinates(Pawn* pawn, short int y, short int x) {
            return Coordinates(pawn->getCoordinates().y + y, pawn->getCoordinates().x + x);
        }
        // ℹ️ - The following function calculates coordinates, but does not apply them to the pawns
        Coordinates movingByCoordinates(Pawn* pawn, short int y, short int x, bool effect) {
            short int y_ = pawn->getCoordinates().y + y;
            short int x_ = pawn->getCoordinates().x + x;
            if (!isOutOfBounds(y_, x_)) {
                return Coordinates(y_, x_);
            } else if (effect == PACMAN_EFFECT) {
                if (x_ < 0) {
                    x_ = width-1-(x_ % width);
                    if (x_ == width)
                        x_ = width - 1;
                } else if (x_ >= width) {
                    x_ = abs(x_ % width);
                }
                if (y_ < 0) {
                    y_ = height-1-(y_ % width);
                    if (y_ == height)
                        y_ = height -1;
                } else if (y_ >= height) {
                    y_ = abs(y_ % height);
                }
                return Coordinates(y_, x_);
            } else if (effect == MATRIX_EFFECT) {
                short int y__ = y_;
                short int x__ = x_;
                if (x_ < 0) {
                    x_ = width+(x_ % width);
                    y_ = y__ + (short int)(x__ / width) - 1;
                } else if (x_ >= width) {
                    x_ %= width;
                    y_ = y__ + (short int)(x__ / width);
                }
                // This [y_] could lead to a coordinate out of bounds...
                if (!isOutOfBounds(y_, x_))
                    return Coordinates(y_, x_);
                else
                    throw std::range_error("Invalid Coordinates, the movement is not possible");
            } else {
                throw std::range_error("Invalid Coordinates, the movement is not possible");
            }
        }

        void addPawnToSwap(Pawn* pawn, Coordinates& first) { // addPawnToSwap - add a pawn to the pawnsToSwap
            if (!isOutOfBounds(first)) {
                Coordinates start = pawn->getCoordinates();
                std::vector<Path>::iterator it = std::find_if(
                    pawnsToSwap.begin(), pawnsToSwap.end(), [&](Path& path_) {
                        return (path_.begin == first && path_.end == start);
                    }
                ); // Search for the opposite of the swap
                if (it != pawnsToSwap.end()) { // If the opposite of the swap is found...
                    swapTwoPawns(it->pawn, pawn); // Swap the pawns
                    pawnsToSwap.erase(it);
                } else {
                    pawnsToSwap.push_back(Path(start, first, pawn));
                }
            }
        }
        void addPawnToSwap(Path& path) { // addPawnToSwap - add a pawn to the pawnsToSwap
            if (!isOutOfBounds(path.begin) && !isOutOfBounds(path.end)) {
                std::vector<Path>::iterator it = std::find_if(
                    pawnsToSwap.begin(), pawnsToSwap.end(), [&](Path& path_) {
                        return path | path_;
                    }
                ); // Search for the opposite of the swap
                if (it != pawnsToSwap.end()) { // If the opposite of the swap is found...
                    swapTwoPawns(it->pawn, path.pawn); // Swap the pawns
                    pawnsToSwap.erase(it);
                } else {
                    pawnsToSwap.push_back(path);
                }
            }
        }
        void simulateSwaps() { // simulateSwaps - simulate all the swaps in the pawnsToSwap
            std::vector<std::vector<short int>> pawnsCount_ = pawnsCount; // Copy the pawnsCount
            for (Path& path : pawnsToSwap) { // Simulate all the swaps in the pawnsToSwap
                pawnsCount_[path.begin.y][path.begin.x]--; // Decrease the number of pawns at the begin of the path (because the pawn will be removed from there)
                pawnsCount_[path.end.y][path.end.x]++; // Increase the number of pawns at the end of the path (because the pawn will be added there)
            }

            std::sort(pawnsToSwap.begin(), pawnsToSwap.end()); // Sort the pawnsToSwap by priority
            std::vector<Path>::iterator it = pawnsToSwap.begin();
            Coord arrive_coord; // Coordinates of the cell with 2 or more pawns (so where a certain pawn arrived and should never be arrived at)
            try {
                while (true) {
                    // Find the first cell with 2 or more pawns
                    arrive_coord = firstInvalidCell(pawnsCount_); // throw std::runtime_error("No invalid cells found");
                    Coordinates arrive_(arrive_coord); // Coordinates of the cell with 2 or more pawns (so where a certain pawn arrived and should never be arrived at)

                    // Find a pawn that arrived at the cell with 2 or more pawns
                    // Pawn* pawn = getPawn(arrive_); // NO! Swap weren't applied yet, so the pawn is still at the begin of the path
                    pawnsCount_[arrive_.y][arrive_.x]--; // Decrease the number of pawns at the cell with 2 or more pawns (because the pawn will be removed from there)
                    for (it = pawnsToSwap.begin(); it != pawnsToSwap.end(); it++) {
                        if (it->end == arrive_) { // If the pawn arrived at the cell with 2 or more pawns
                            pawnsCount_[it->begin.y][it->begin.x]++; // Increase the number of pawns at the begin of the path (because the pawn will be added there)
                            pawnsToSwap.erase(it); // Remove the path from the pawnsToSwap (this movement can't be applied anymore)
                            break;
                        }
                    }
                } // This loop will be broken when the firstInvalidCell throws an exception
            } catch (std::runtime_error& e) {
                pawnsCount = pawnsCount_; // Apply the swaps
                return; // No more invalid cells found
            }
        }
        void applySwaps() {
            simulateSwaps(); // This assures that the pawnsToSwap is valid

            // The swaps can be applied as it stands
            for (Path& path : pawnsToSwap) {
                removePawn(path.pawn); // Remove the pawn from the begin of the path
                path.pawn->setCoordinates(path.end); // Set the pawn's coordinates to the end of the path
                addPawn(path.pawn); // Add the pawn to the end of the path
            }
            clearPawnsToSwap();
        }

        void swapTwoPawns(Coordinates& first, Coordinates& second) {
            // Swap the coordinates of the two pawns (into the Pawn object)
            Pawn* first_ = getPawn(first);
            Pawn* second_ = getPawn(second);
            if (first_ != nullptr) {
                first_->setCoordinates(second);
            }
            if (second_ != nullptr) {
                second_->setCoordinates(first);
            }
            // std::swap the pointers Pawn* in the pawns 2D-std::vector
            std::swap(
                pawns[first.y][first.x],
                pawns[second.y][second.x]
            );
        }
        void swapTwoPawns(Pawn* first, Pawn* second) {
            // Swap the coordinates of the two pawns (into the Pawn object)
            Coordinates temp = first->getCoordinates();
            Coordinates app = second->getCoordinates();
            first->setCoordinates(app);
            second->setCoordinates(temp);

            // Draw the first pawn at the second pawn's coordinates
            cursor.set(temp);
            std::cout << ' ';
            cursor.set(app);
            first->print();
            // Draw the second pawn at the first pawn's coordinates
            cursor.set(temp);
            second->print();

            // std::swap the pointers Pawn* in the pawns 2D-std::vector
            std::swap(
                pawns[temp.y][temp.x],
                pawns[app.y][app.x]
            );
        }
    };
};