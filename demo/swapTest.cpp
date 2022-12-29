#include <chrono>
#include <thread>
#include "../include/sista/sista.hpp"
// g++ swapTest.cpp -o swapTest -std=c++17 -Wall


int main() {
    sista::SwappableField field(10, 10);
    std::vector<sista::Pawn*> pawns = {
        new sista::Pawn(
            'X', sista::Coordinates(0, 0),
            ANSI::Settings(
                ANSI::ForegroundColor::F_RED,
                ANSI::BackgroundColor::B_BLACK,
                ANSI::Attribute::DIM
            )
        ),
        new sista::Pawn(
            'O', sista::Coordinates(0, 9),
            ANSI::Settings(
                ANSI::ForegroundColor::F_GREEN,
                ANSI::BackgroundColor::B_BLACK,
                ANSI::Attribute::UNDERSCORE
            )
        )
    };
    for (sista::Pawn* pawn : pawns) {
        field.addPawn(pawn);
    }
    sista::Border border(
        '#', ANSI::Settings(
            ANSI::ForegroundColor::F_WHITE,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BLINK
        )
    );
    field.print(border);
    sista::Coordinates coords[2];
    for (int i = 0; i < 10; i++) {
        coords[0] = field.movingByCoordinates(pawns[0], 0, 1, PACMAN_EFFECT);
        coords[1] = field.movingByCoordinates(pawns[1], 0, -1, PACMAN_EFFECT);
        try {
            field.movePawn(pawns[0], coords[0]);
            field.movePawn(pawns[1], coords[1]);
        } catch (std::invalid_argument& e) {
            field.addPawnToSwap(pawns[0], coords[0]);
            field.addPawnToSwap(pawns[1], coords[1]);
            field.applySwaps();
        }
        std::cout << "\x1b[13;12H";
        std::cout << "(" << pawns[0]->getCoordinates().x << ", " << pawns[0]->getCoordinates().y << ")\n";
        std::flush(std::cout);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}