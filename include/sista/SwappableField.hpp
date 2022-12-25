#pragma once

#include <queue> // std::queue, std::priority_queue
#include <algorithm> // std::sort
#include "field.hpp" // Field, Pawn

#include <fstream> // std::ofstream
std::ofstream debug("debug.txt"); // debug - debug file


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

    void addPawn(Pawn* pawn) override { // addPawn - add a pawn to the field
        Field::addPawn(pawn);
        pawnsCount[pawn->getCoordinates().y][pawn->getCoordinates().x]++;
    }
    void removePawn(Pawn* pawn) override { // removePawn - remove a pawn from the field
        Field::removePawn(pawn);
        pawnsCount[pawn->getCoordinates().y][pawn->getCoordinates().x]--;
    }

    void clearPawnsToSwap() { // clearPawnsToSwap - clear the pawnsToSwap
        pawnsToSwap.clear();
    }

    Coordinates movingByCoordinates(Pawn* pawn, short int y, short int x) { // Function to calculate the resulting coordinates of a pawn after moving by y and x
        return Coordinates(pawn->getCoordinates().y + y, pawn->getCoordinates().x + x);
    }
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
            pawnsToSwap.push_back(Path(pawn->getCoordinates(), first, pawn));
        }
    }
    void addPawnToSwap(Path& path) { // addPawnToSwap - add a pawn to the pawnsToSwap
        if (!isOutOfBounds(path.begin) && !isOutOfBounds(path.end)) {
            pawnsToSwap.push_back(path);
        }
    }
    void simulateSwaps() { // simulateSwaps - simulate all the swaps in the pawnsToSwap
        std::vector<std::vector<short int>> pawnsCount_ = pawnsCount; // Copy the pawnsCount
        debug << "Before:\n";
        for (auto& row: pawnsCount_) {
            for (auto& cell: row) {
                debug << cell;
            }
            debug << "\n";
        }
        for (Path& path : pawnsToSwap) { // Simulate all the swaps in the pawnsToSwap
            pawnsCount_[path.begin.y][path.begin.x]--; // Decrease the number of pawns at the begin of the path (because the pawn will be removed from there)
            pawnsCount_[path.end.y][path.end.x]++; // Increase the number of pawns at the end of the path (because the pawn will be added there)
        }

        debug << "After:\n";
        for (auto& row: pawnsCount_) {
            for (auto& cell: row) {
                debug << cell;
            }
            debug << "\n";
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
        debug << "Applying swaps..." << std::endl;
        std::cerr << "Applying swaps..." << std::endl;
        debug << "Swaps to apply: " << pawnsToSwap.size() << std::endl;
        std::cerr << "Swaps to apply: " << pawnsToSwap.size() << std::endl;
        for (Path& path: pawnsToSwap) {
            debug << "Pawn at (" << path.begin.y << ", " << path.begin.x << ") will arrive at (" << path.end.y << ", " << path.end.x << ")" << std::endl;
            std::cerr << "Pawn at (" << path.begin.y << ", " << path.begin.x << ") will arrive at (" << path.end.y << ", " << path.end.x << ")" << std::endl;
        }

        simulateSwaps(); // This assures that the pawnsToSwap is valid

        // The swaps can be applied as it stands
        for (Path& path : pawnsToSwap) {
            swapTwoPawns(path.begin, path.end);
        }
        clearPawnsToSwap();
    }

    void swapTwoPawns(Coordinates& first, Coordinates& second) {
        debug << "Swapping (" << first.y << ", " << first.x << ") with (" << second.y << ", " << second.x << ")\n";
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
        Pawn* now_first = getPawn(first);
        Pawn* now_second = getPawn(second);
        if (now_first != nullptr) {
            Coordinates now_first_coord = now_first->getCoordinates();
            debug << "The now-first Pawn reached (" << now_first_coord.y << ", " << now_first_coord.x << ")" << std::endl;
        }
        if (now_second != nullptr) {
            Coordinates now_second_coord = now_second->getCoordinates();
            debug << "The now-second Pawn reached (" << now_second_coord.y << ", " << now_second_coord.x << ")" << std::endl;
        }
    }
    void swapTwoPawns(Pawn* first, Pawn* second) {
        // Swap the coordinates of the two pawns (into the Pawn object)
        Coordinates temp = first->getCoordinates();
        Coordinates app = second->getCoordinates();
        first->setCoordinates(app);
        second->setCoordinates(temp);
        // std::swap the pointers Pawn* in the pawns 2D-std::vector
        std::swap(
            pawns[first->getCoordinates().y][first->getCoordinates().x],
            pawns[second->getCoordinates().y][second->getCoordinates().x]
        );
    }
};