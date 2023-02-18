// g++ sista.cpp -o sista -std=c++17 -Wall
#include <chrono>
#include <thread>
#include "include/sista/sista.hpp"

#define TEST_SIZE 50


int main() {
    std::ios_base::sync_with_stdio(false);
    ANSI::reset(); // Reset the settings

    std::vector<sista::Pawn*> pawns = {
        new sista::Pawn(
            'X', sista::Coordinates(0, 0),
            ANSI::Settings(
                ANSI::ForegroundColor::F_RED,
                ANSI::BackgroundColor::B_BLACK,
                ANSI::Attribute::BRIGHT
            )
        ),
        new sista::Pawn(
            'O', sista::Coordinates(TEST_SIZE*0.2, TEST_SIZE*0.7),
            ANSI::Settings(
                ANSI::ForegroundColor::F_BLUE,
                ANSI::BackgroundColor::B_BLACK,
                ANSI::Attribute::BRIGHT
            )
        ),
        new sista::Pawn(
            '@', sista::Coordinates(TEST_SIZE*0.3, 0),
            ANSI::Settings(
                ANSI::ForegroundColor::F_MAGENTA,
                ANSI::BackgroundColor::B_YELLOW,
                ANSI::Attribute::REVERSE
            )
        ),
        new sista::Pawn(
            '%', sista::Coordinates(TEST_SIZE*0.5, TEST_SIZE*0.5),
            ANSI::Settings(
                ANSI::ForegroundColor::F_YELLOW,
                ANSI::BackgroundColor::B_MAGENTA,
                ANSI::Attribute::REVERSE
            )
        ),
        new sista::Pawn(
            '!', sista::Coordinates(TEST_SIZE*0.7, TEST_SIZE*0.2),
            ANSI::Settings(
                ANSI::ForegroundColor::F_CYAN,
                ANSI::BackgroundColor::B_BLACK,
                ANSI::Attribute::BRIGHT
            )
        ),
        new sista::Pawn(
            '#', sista::Coordinates(TEST_SIZE*0.8, TEST_SIZE*0.8),
            ANSI::Settings(
                ANSI::ForegroundColor::F_GREEN,
                ANSI::BackgroundColor::B_BLACK,
                ANSI::Attribute::BRIGHT
            )
        )
    };
    sista::Border border(
        '@', ANSI::Settings(
            ANSI::ForegroundColor::F_YELLOW,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BLINK
        )
    );
    sista::SwappableField field(TEST_SIZE, TEST_SIZE);
    for (auto pawn : pawns) {
        field.addPawn(pawn);
    }
    std::vector<sista::Coordinates> coords(pawns.size());
    field.print(border);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    for (int i=0; i<TEST_SIZE*TEST_SIZE; i++) {
        coords[0] = field.movingByCoordinates(pawns[0], 1, 1, PACMAN_EFFECT);
        coords[1] = field.movingByCoordinates(pawns[1], -1, -1, PACMAN_EFFECT);
        coords[2] = field.movingByCoordinates(pawns[2], -1, 1, PACMAN_EFFECT);
        coords[3] = field.movingByCoordinates(pawns[3], 1, -1, PACMAN_EFFECT);
        coords[4] = field.movingByCoordinates(pawns[4], 1, 0, PACMAN_EFFECT);
        coords[5] = field.movingByCoordinates(pawns[5], 0, 1, PACMAN_EFFECT);
        try {
            for (int k=0; k<(int)pawns.size(); k++) {
                field.movePawn(pawns[k], coords[k]);
            }
        } catch (const std::invalid_argument& e) {
            for (int k=0; k<(int)pawns.size(); k++) {
                field.addPawnToSwap(pawns[k], coords[k]);
            }
            field.applySwaps();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << std::flush;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return 0;
}