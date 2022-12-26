// g++ sista.cpp -o sista -std=c++17 -Wall -Wextra
#include <chrono>
#include <thread>
#include "include/sista/sista.hpp"

#define TEST_SIZE 30


int main() {
    std::ios_base::sync_with_stdio(false);
    ANSI::reset(); // Reset the settings
    std::cout << HIDE_CURSOR;
    clearScreen();
    sista::Pawn* pawn = new sista::Pawn(
        'X', sista::Coordinates(0, 0),
        ANSI::Settings(
            ANSI::ForegroundColor::F_RED,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );
    sista::Pawn* pawn2 = new sista::Pawn(
        'O', sista::Coordinates(TEST_SIZE*0.2, TEST_SIZE*0.7),
        ANSI::Settings(
            ANSI::ForegroundColor::F_BLUE,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );
    sista::Pawn* pawn3 = new sista::Pawn(
        '@', sista::Coordinates(TEST_SIZE*0.3, 0),
        ANSI::Settings(
            ANSI::ForegroundColor::F_MAGENTA,
            ANSI::BackgroundColor::B_YELLOW,
            ANSI::Attribute::REVERSE
        )
    );
    sista::Pawn* pawn4 = new sista::Pawn(
        '%', sista::Coordinates(0, TEST_SIZE*0.5),
        ANSI::Settings(
            ANSI::ForegroundColor::F_YELLOW,
            ANSI::BackgroundColor::B_MAGENTA,
            ANSI::Attribute::REVERSE
        )
    );
    sista::Border border(
        '#', ANSI::Settings(
            ANSI::ForegroundColor::F_WHITE,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );
    sista::SwappableField field(TEST_SIZE, TEST_SIZE);
    field.addPawn(pawn);
    field.addPawn(pawn2);
    field.addPawn(pawn3);
    field.addPawn(pawn4);
    sista::Coordinates coords, coords2, coords3, coords4;
    for (int i=0; i<TEST_SIZE; i++) {
        for (int j=0; j<TEST_SIZE; j++) {
            coords = field.movingByCoordinates(pawn, 1, 1, PACMAN_EFFECT);
            coords2 = field.movingByCoordinates(pawn2, -1, -1, PACMAN_EFFECT);
            coords3 = field.movingByCoordinates(pawn3, -1, 1, PACMAN_EFFECT);
            coords4 = field.movingByCoordinates(pawn4, 1, -1, PACMAN_EFFECT);
            try {
                field.movePawn(pawn, coords);
                field.movePawn(pawn2, coords2);
                field.movePawn(pawn3, coords3);
                field.movePawn(pawn4, coords4);
            } catch (const std::invalid_argument& e) {
                field.addPawnToSwap(pawn, coords);
                field.addPawnToSwap(pawn2, coords2);
                field.addPawnToSwap(pawn3, coords3);
                field.addPawnToSwap(pawn4, coords4);
                field.applySwaps();
            }

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