// g++ sista.cpp -o sista -std=c++17 -Wall -Wextra
#include <chrono>
#include <thread>
#include "include/sista/sista.hpp"

#define TEST_SIZE 10


int main() {
    std::ios_base::sync_with_stdio(false);
    ANSI::reset(); // Reset the settings
    std::cout << HIDE_CURSOR;
    clearScreen();
    Pawn pawn(
        'X', Coordinates(0, 0),
        ANSI::Settings(
            ANSI::ForegroundColor::F_RED,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );
    Pawn pawn2(
        'O', Coordinates(TEST_SIZE-1, TEST_SIZE-1),
        ANSI::Settings(
            ANSI::ForegroundColor::F_BLUE,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );
    Border border(
        ' ', ANSI::Settings(
            ANSI::ForegroundColor::F_BLACK,
            ANSI::BackgroundColor::B_WHITE,
            ANSI::Attribute::BRIGHT
        )
    );
    SwappableField field(TEST_SIZE, TEST_SIZE);
    field.addPawn(&pawn);
    field.addPawn(&pawn2);
    Coordinates coords(0, 0);
    for (int i=0; i<TEST_SIZE; i++) {
        for (int j=0; j<TEST_SIZE; j++) {
            debug << "Calculating arrival coordinates for first pawn." << std::endl;
            coords = field.movingByCoordinates(&pawn, 0, 1, MATRIX_EFFECT);

            debug << "Querying swap for first pawn from (" << pawn.getCoordinates().y << ", " << pawn.getCoordinates().x << ") to (" << coords.y << ", " << coords.x << ")" << std::endl;
            field.addPawnToSwap(&pawn, coords);

            debug << "Calculating arrival coordinates for second pawn." << std::endl;
            coords = field.movingByCoordinates(&pawn2, 0, -1, MATRIX_EFFECT);

            debug << "Querying swap for second pawn from (" << pawn2.getCoordinates().y << ", " << pawn2.getCoordinates().x << ") to (" << coords.y << ", " << coords.x << ")" << std::endl;
            field.addPawnToSwap(&pawn2, coords);

            field.applySwaps();

            // field.movePawnBy(&pawn, 0, 1, PACMAN_EFFECT);
            // field.movePawnBy(&pawn2, 0, -1, PACMAN_EFFECT);

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            clearScreen();
            field.print(border);
        }
    }
    clearScreen();
    std::cout << SHOW_CURSOR;
    field.print(border);
    return 0;
}