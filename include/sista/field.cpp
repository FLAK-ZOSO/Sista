#include "field.hpp" // Field, Pawn, ANSI, <iostream>, <vector>, <algorithm>, <stdexcept>, <unordered_map>, <memory>, <map>
#include <queue> // std::queue, std::priority_queue
#include <algorithm> // std::sort
#include <iostream> // std::cout, std::flush

namespace sista {
    void Field::clear() { // Clear the matrix
        for (auto& row: pawns) // For each row
            for (auto& pawn: row) // For each pawn
                pawn = nullptr; // Set the pawn to nullptr
    }
    void Field::reset() {
        for (auto& row: pawns) { // For each row
            for (auto& pawn: row) {
                if (pawn != nullptr) // If the pawn is not nullptr
                    pawn.reset(); // Delete the pawn
                pawn = nullptr; // Set the pawn to nullptr
            }
        }        
    }

    Field::Field(int width_, int height_): width(width_), height(height_) { // Constructor
        pawns.resize(height); // Resize the vector
        for (int i = 0; i < height; i++) // For each row
            pawns[i].resize(width); // Resize the vector
        this->clear(); // Clear the matrix
    }
    Field::~Field() {
        for (int i = 0; i < (int)pawns.size(); i++) // For each row
            for (int j = 0; j < (int)pawns[i].size(); j++) // For each pawn
                pawns[i][j].reset(); // Delete the pawn
        pawns.clear(); // Clear the pawns
    }

    void Field::print() const { // Print the matrix
        resetAnsi(); // Reset the settings
        bool previousPawn = false; // If the previous element was a Pawn
        for (auto& row: pawns) { // For each row
            for (auto& pawn: row) { // For each pawn
                if (pawn != nullptr) { // If the pawn is not nullptr
                    pawn->print(); // Print the pawn
                    previousPawn = true; // Set the previousPawn to true
                } else { // If the pawn is nullptr
                    if (previousPawn) { // If the previous element was a Pawn
                        resetAnsi(); // Reset the settings
                        previousPawn = false; // Set the previousPawn to false
                    }
                    std::cout << ' ';
                }
            }
            std::cout << '\n';
        }
        resetAnsi(); // Reset the settings
        std::cout << std::flush; // Flush the output
    }
    void Field::print(char border) const { // Prints with custom border
        resetAnsi(); // Reset the settings
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
                        resetAnsi(); // Reset the settings
                        previousPawn = false; // Set the previousPawn to false
                    }
                    std::cout << ' ';
                }
            }
            resetAnsi(); // Reset the settings
            std::cout << border << '\n'; // Print the border and a new line
        }
        for (int i=0; i<width+2; i++) // For each row
            std::cout << border; // Print the border
        std::cout << std::flush; // Flush the output
    }
    void Field::print(Border& border) const { // Prints with custom border
        resetAnsi(); // Reset the settings
        std::cout << '\n';
        border.print(); // Print the border
        for (int i=0; i<width+1; i++) // For each row
            border.print(false); // Print the border
        resetAnsi(); // Reset the settings
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
                        resetAnsi(); // Reset the settings
                        previousPawn = false; // Set the previousPawn to false
                    }
                    std::cout << ' ';
                }
            }
            border.print();
            resetAnsi(); // Reset the settings
            previousPawn = true; // Set the previousPawn to true
            std::cout << '\n';
        }
        border.print(); // Print the border
        for (int i=0; i<width+1; i++) // For each row
            border.print(false); // Print the border
        resetAnsi(); // Reset the settings
        std::cout << std::flush; // Flush the output
    }

    void Field::addPawn(std::shared_ptr<Pawn> pawn) { // Add a pawn to the matrix
        pawns[pawn->getCoordinates().y][pawn->getCoordinates().x] = pawn; // Set the pawn to the coordinates
    }
    void Field::removePawn(Pawn* pawn) { // Remove a pawn from the matrix
        pawns[pawn->getCoordinates().y][pawn->getCoordinates().x].reset(); // Release the reference to the pointer
    }
    void Field::removePawn(const Coordinates& coordinates) { // Remove a pawn from the matrix
        pawns[coordinates.y][coordinates.x].reset(); // Release the reference to the pointer
    }
    void Field::erasePawn(Pawn* pawn) { // Erase a pawn from the matrix
        removePawn(pawn); // Remove the pawn from the matrix
        cursor.goTo(pawn->getCoordinates()); // Set the cursor to the pawn's coordinates
        resetAnsi(); // Reset the settings for that cell
        std::cout << ' '; // Print a space to clear the cell
    }
    void Field::erasePawn(const Coordinates& coordinates) { // Erase a pawn from the matrix
        removePawn(coordinates);
        cursor.goTo(coordinates); // Set the cursor to the coordinates
        resetAnsi(); // Reset the settings for that cell
        std::cout << ' '; // Print a space to clear the cell
    }
    void Field::cleanCoordinates(const Coordinates& coordinates) const { // Clean a cell from the matrix
        cursor.goTo(coordinates); // Set the cursor to the coordinates
        resetAnsi(); // Reset the settings for that cell
        std::cout << ' '; // Print a space to clear the cell
    }
    void Field::cleanCoordinates(unsigned short y, unsigned short x) const { // Clean a cell from the matrix
        Coordinates coordinates(y, x);
        cleanCoordinates(coordinates);
    }

    void Field::addPrintPawn(std::shared_ptr<Pawn> pawn) { // Add a pawn to the matrix and print it
        addPawn(pawn); // Add the pawn to the matrix
        this->cursor.goTo(pawn->getCoordinates()); // Set the cursor to the pawn's coordinates
        pawn->print(); // Print the pawn
    }
    void Field::rePrintPawn(Pawn* pawn) { // Print a pawn
        cursor.goTo(pawn->getCoordinates()); // Set the cursor to the pawn's coordinates
        pawn->print(); // Print the pawn
    }

    void Field::movePawn(Pawn* pawn, const Coordinates& coordinates) { // Move a pawn to the coordinates
        try {
            validateCoordinates(coordinates);
        } catch (const std::invalid_argument& e) {
            if (pawn->getCoordinates() == coordinates) // If the coordinates are the same...
                return; // ...the cell is occupied by the pawn, so no need to move it
            // ...otherwise, if the coordinates are occupied by another pawn, throw an exception
            throw std::invalid_argument("The coordinates are occupied by another pawn");
        }
        // Cursor ANSI stuff
        cursor.goTo(pawn->getCoordinates()); // Set the cursor to the pawn's coordinates
        resetAnsi(); // Reset the settings for that cell
        std::cout << ' '; // Print a space to clear the cell
        cursor.goTo(coordinates); // Set the cursor to the coordinates
        pawn->print(); // Print the pawn

        // sista::Field stuff
        std::shared_ptr<Pawn>& old_cell = pawns[pawn->getCoordinates().y][pawn->getCoordinates().x];
        pawns[coordinates.y][coordinates.x] = std::move(old_cell); // Moving Pawn ownership away from the old cell
        removePawn(pawn); // Releasing ownership, now pointing to the void nullptr
        // Removal must take place *before* updating the coordinates, as it is based on these
        pawn->setCoordinates(coordinates);
    }
    void Field::movePawn(Pawn* pawn, unsigned short y, unsigned short x) { // Move a pawn to the coordinates
        Coordinates coordinates_(y, x);
        movePawn(pawn, coordinates_);
    }

    void Field::movePawnBy(Pawn* pawn, const Coordinates& coordinates) { // Move a pawn by the coordinates
        Coordinates coordinates_ = pawn->getCoordinates() + coordinates;
        movePawn(pawn, coordinates_);
    }
    void Field::movePawnBy(Pawn* pawn, unsigned short y, unsigned short x) {
        movePawn(pawn, pawn->getCoordinates().y + y, pawn->getCoordinates().x + x);
    }

    // 🎮 movePawnBy() with arcade game effects on coordinates overflow
    void Field::movePawnBy(Pawn* pawn, const Coordinates& coordinates, Effect effect) {
        movePawnBy(pawn, coordinates.y, coordinates.x, effect);
    }
    void Field::movePawnBy(Pawn* pawn, short int y, short int x, Effect effect) {
        short int y_ = pawn->getCoordinates().y + y;
        short int x_ = pawn->getCoordinates().x + x;
        if (!isOutOfBounds(y_, x_)) { // If the coordinates are not out of bounds...
            movePawn(pawn, y_, x_); // ...no need to apply any effect
        } else if (effect == Effect::PACMAN) { // If the effect is PACMAN...
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
        } else if (effect == Effect::MATRIX) { // If the effect is MATRIX...
            // ...the coordinates "wrap around" like in a classic C style matrix
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

    void Field::movePawnFromTo(const Coordinates& coordinates, const Coordinates& newCoordinates) {
        movePawn(getPawn(coordinates), newCoordinates);
    }
    void Field::movePawnFromTo(unsigned short y, unsigned short x, unsigned short newY, unsigned short newX) {
        movePawn(getPawn(y, x), newY, newX);
    }

    Pawn* Field::getPawn(const Coordinates& coordinates) const { // Get the pawn at the coordinates
        return pawns[coordinates.y][coordinates.x].get(); // Return the pawn at the coordinates
    }
    Pawn* Field::getPawn(unsigned short y, unsigned short x) const {
        return pawns[y][x].get();
    }

    bool Field::isOccupied(const Coordinates& coordinates) const { // Check if the coordinates are occupied
        return (getPawn(coordinates) != nullptr);
    }
    bool Field::isOccupied(unsigned short y, unsigned short x) const {
        return (getPawn(y, x) != nullptr);
    }
    bool Field::isOccupied(short int y, short int x) const {
        return (getPawn(y, x) != nullptr);
    }

    bool Field::isOutOfBounds(const Coordinates& coordinates) const { // Check if the coordinates are out of bounds
        return (coordinates.y >= height || coordinates.x >= width); // Return if the coordinates are out of bounds
    }
    bool Field::isOutOfBounds(unsigned short y, unsigned short x) const {
        return  (y >= height || x >= width);
    }
    bool Field::isOutOfBounds(short int y, short int x) const {
        return  (y < 0 || y >= height || x < 0 || x >= width);
    }

    bool Field::isFree(const Coordinates& coordinates) const { // Check if the coordinates are occupied or out of bounds
        return !(isOutOfBounds(coordinates) || isOccupied(coordinates));
    }
    bool Field::isFree(unsigned short y, unsigned short x) const {
        return !(isOutOfBounds(y, x) || isOccupied(y, x));
    }
    bool Field::isFree(short int y, short int x) const {
        return !(isOutOfBounds(y, x) || isOccupied(y, x));
    }

    // ⚠️ This throws an exception if the coordinates are invalid
    void Field::validateCoordinates(const Coordinates& coordinates) const { // Validate the coordinates
        if (isOutOfBounds(coordinates)) // If the coordinates are out of bounds
            throw std::out_of_range("Coordinates are out of bounds");
        if (isOccupied(coordinates)) // If the coordinates are occupied
            throw std::invalid_argument("Coordinates are occupied");
    }
    void Field::validateCoordinates(unsigned short y, unsigned short x) const {
        if (isOutOfBounds(y, x))
            throw std::out_of_range("Coordinates are out of bounds");
        if (isOccupied(y, x))
            throw std::invalid_argument("Coordinates are occupied");
    }

    Path::Path(Coordinates begin_, Coordinates end_, Pawn* pawn_) : begin(begin_), end(end_), pawn(pawn_) {
        priority = current_priority++;
    }

    bool Path::operator|(const Path& other) const { // operator| - check if two paths are switching each other
        return (
            (this->begin == other.begin && this->end == other.end) ||
            (this->begin == other.end && this->end == other.begin)
        );
    }
    bool Path::operator<(const Path& other) const { // operator< - give priority order to paths
        return this->priority < other.priority;
    }
    bool Path::operator==(const Path& other) const { // operator== - check if two paths are equal (both begin and end coordinates are the same, ignores priority and pawn)
        return (this->begin == other.begin && this->end == other.end);
    }
    long long int Path::current_priority = 0; // priority - priority of the current Path


    Coordinates SwappableField::firstInvalidCell(std::map<Coordinates, short int>& pawnsCount_) const { // lowerBound - find the first cell with a value >= value
        for (std::pair<const Coordinates, short int>& pair : pawnsCount_) {
            if (pair.second >= 2) // If the cell has 2 or more pawns
                return pair.first; // Return the coordinates of the cell
        }
        throw std::runtime_error("No invalid cells found");
    }

    SwappableField::SwappableField(int width, int height) : Field(width, height) {
        pawnsCount.resize(height);
        for (int y = 0; y < height; y++) {
            pawnsCount[y].resize(width);
            for (int x = 0; x < width; x++) {
                pawnsCount[y][x] = 0;
            }
        }
    }
    SwappableField::~SwappableField() {
        for (int i = 0; i < (int)pawns.size(); i++) // For each row
            for (int j = 0; j < (int)pawns[i].size(); j++) // For each pawn
                pawns[i][j].reset();
        pawns.clear(); // Clear the pawns
    }

    void SwappableField::addPawn(std::shared_ptr<Pawn> pawn) { // addPawn - add a pawn to the field
        Field::addPawn(pawn);
        pawnsCount[pawn->getCoordinates().y][pawn->getCoordinates().x]++;
    }
    void SwappableField::removePawn(Pawn* pawn) { // removePawn - remove a pawn from the field
        Field::removePawn(pawn);
        pawnsCount[pawn->getCoordinates().y][pawn->getCoordinates().x]--;
    }

    void SwappableField::clearPawnsToSwap() { // clearPawnsToSwap - clear the pawnsToSwap
        Path::current_priority = 0;
        pawnsToSwap.clear();
    }

    // ℹ️ - The following function calculates coordinates, but does not apply them to the pawns
    Coordinates Field::movingByCoordinates(Pawn* pawn, short int y, short int x) const {
        return Coordinates(pawn->getCoordinates().y + y, pawn->getCoordinates().x + x);
    }
    // ℹ️ - The following function calculates coordinates, but does not apply them to the pawns
    Coordinates Field::movingByCoordinates(Pawn* pawn, short int y, short int x, Effect effect) const {
        short int y_ = pawn->getCoordinates().y + y;
        short int x_ = pawn->getCoordinates().x + x;
        if (!isOutOfBounds(y_, x_)) {
            return Coordinates(y_, x_);
        } else if (effect == Effect::PACMAN) {
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
        } else if (effect == Effect::MATRIX) {
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

    void SwappableField::addPawnToSwap(Pawn* pawn, const Coordinates& destination) { // addPawnToSwap - add a pawn to the pawnsToSwap
        if (pawn == nullptr) // If the pawn is nullptr...
            throw std::invalid_argument("Pawn is nullptr"); // ...throw an exception
        if (isOutOfBounds(destination)) // If the destination is out of bounds...
            throw std::out_of_range("Destination is out of bounds"); // ...throw an exception
        if (pawn->getCoordinates() == destination) // If the destination is the same as the pawn's coordinates...
            return; // ...no need to add the pawn to the pawnsToSwap
        // Note: destination can be occupied, as the swap will be simulated later
        Coordinates start = pawn->getCoordinates();
        Path oppositePath(destination, start, nullptr); // Create the opposite path
        std::set<Path>::iterator it = pawnsToSwap.find(oppositePath); // Find the opposite path in the pawnsToSwap
        if (it != pawnsToSwap.end()) { // If the opposite path is found
            swapTwoPawns(pawn, it->pawn); // Swap the two pawns
            pawnsToSwap.erase(it); // Remove the opposite path from the pawnsToSwap
            return; // Return
        }
        // If the opposite path is not found, add the path to the pawnsToSwap
        pawnsToSwap.insert(Path(pawn->getCoordinates(), destination, pawn));
    }
    void SwappableField::addPawnToSwap(Path& path) { // addPawnToSwap - add a pawn to the pawnsToSwap
        if (path.pawn == nullptr) // If the pawn is nullptr...
            throw std::invalid_argument("Pawn is nullptr"); // ...throw an exception
        if (isOutOfBounds(path.end)) // If the destination is out of bounds...
            throw std::out_of_range("Destination is out of bounds"); // ...throw an exception
        if (path.begin == path.end) // If the destination is the same as the pawn's coordinates...
            return; // ...no need to add the pawn to the pawnsToSwap
        // Note: destination can be occupied, as the swap will be simulated later
        Path oppositePath(path.end, path.begin, nullptr); // Create the opposite path
        std::set<Path>::iterator it = pawnsToSwap.find(oppositePath); // Find the opposite path in the pawnsToSwap
        if (it != pawnsToSwap.end()) { // If the opposite path is found
            swapTwoPawns(path.pawn, it->pawn); // Swap the two pawns
            pawnsToSwap.erase(it); // Remove the opposite path from the pawnsToSwap
            return; // Return
        }
        // If the opposite path is not found, add the path to the pawnsToSwap
        pawnsToSwap.insert(path);
    }
    void SwappableField::simulateSwaps() { // simulateSwaps - simulate all the swaps in the pawnsToSwap
        std::map<Coordinates, short int> endCount; // Count the number of pawns at the begin of the path
        if (pawnsToSwap.empty()) { // If there are no swaps to simulate,
            return; // ...return
        }
        for (const Path& path : pawnsToSwap) { // Simulate all the swaps in the pawnsToSwap
            if (endCount.count(path.end) == 0 || endCount.count(path.begin) == 0) { // If one of the coordinates of the path is not in the map...
                endCount[path.begin] = pawnsCount[path.begin.y][path.begin.x]; // ...add it to the map with the current number of pawns at the begin of the path
            }
            if (endCount.count(path.end) == 0) {
                endCount[path.end] = pawnsCount[path.end.y][path.end.x]; // ...add it to the map with the current number of pawns at the end of the path
            }
            endCount[path.begin]--; // Decrease the number of pawns at the begin of the path (because the pawn will be removed from there)
            endCount[path.end]++; // Increase the number of pawns at the end of the path (because the pawn will be added there)
        }

        // Paths are stored in a std::set, so they are automatically sorted by priority
        std::set<Path>::iterator it = pawnsToSwap.begin();
        Coordinates arrive_; // Coordinates of the cell with 2 or more pawns (so where a certain pawn arrived and should never be arrived at)
        try {
            while (true) {
                // Find the first cell with 2 or more pawns heading there
                arrive_ = firstInvalidCell(endCount); // Coordinates of the cell with 2 or more pawns (so where a certain pawn arrived and should never be arrived at)


                // Find a pawn that arrived at the cell with 2 or more pawns
                // Pawn* pawn = getPawn(arrive_); // NO! Swap weren't applied yet, so the pawn is still at the begin of the path
                for (it = pawnsToSwap.begin(); it != pawnsToSwap.end();) {
                    if (it->end == arrive_) { // If the pawn arrived at the cell with 2 or more pawns
                        endCount[arrive_]--; // Increase the number of pawns at the begin of the path (because the pawn will be added there)
                        endCount[it->begin]++; // Decrease the number of pawns at the cell with 2 or more pawns (because the pawn will be removed from there)
                        it = pawnsToSwap.erase(it); // Remove the path from the pawnsToSwap (this movement can't be applied anymore)
                    } else {
                        ++it;
                    }
                    if (endCount[arrive_] < 2) { // If the cell with 2 or more pawns is now valid...
                        break; // ...break the loop and find another cell with 2 or more pawns
                    }
                }
            } // This loop will be broken when the firstInvalidCell throws an exception
        } catch (std::runtime_error& e) {
            // No more invalid cells found
        }
    }
    void SwappableField::applySwaps() {
        simulateSwaps(); // This assures that the pawnsToSwap is valid
        
        // Store the starting positions of the pawns to swap
        std::unordered_map<Coordinates, std::shared_ptr<Pawn>> startingBoard;
        for (const Path& path : pawnsToSwap) {
            startingBoard[path.begin] = std::move(pawns[path.begin.y][path.begin.x]); // Remove the pawn from the begin of the path
        }
        // The swaps can be applied as it stands
        for (const Path& path : pawnsToSwap) {
            pawnsCount[path.begin.y][path.begin.x]--; // Decrease the number of pawns at the begin of the path (because the pawn will be removed from there)
            pawnsCount[path.end.y][path.end.x]++; // Increase the number of pawns at the end of the path (because the pawn will be added there)
            pawns[path.end.y][path.end.x] = startingBoard[path.begin]; // Move the pawn to the end of the path
            if (isFree(path.begin)) {
                cleanCoordinates(path.begin); // Clean the cell at the begin of the path
            }
            path.pawn->setCoordinates(path.end); // Update the coordinates of the pawn
            rePrintPawn(path.pawn); // Reprint the pawn at the new coordinates
        }
        clearPawnsToSwap();
    }

    void SwappableField::swapTwoPawns(const Coordinates& first, const Coordinates& second) {
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
        if (first_ != nullptr) {
            rePrintPawn(first_);
        }
        if (second_ != nullptr) {
            rePrintPawn(second_);
        }
    }
    void SwappableField::swapTwoPawns(Pawn* first, Pawn* second) {
        // Swap the coordinates of the two pawns (into the Pawn object)
        Coordinates temp = first->getCoordinates();
        Coordinates app = second->getCoordinates();
        first->setCoordinates(app);
        second->setCoordinates(temp);
        // std::swap the pointers Pawn* in the pawns 2D-std::vector
        std::swap(
            pawns[temp.y][temp.x],
            pawns[app.y][app.x]
        );
        rePrintPawn(first);
        rePrintPawn(second);
    }
};
