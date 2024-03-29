#include <chrono>
#include <thread>
#include "../include/sista/sista.hpp"
// g++ horizontalTest.cpp -o horizontalTest -std=c++17 -Wall


int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    ANSI::reset(); // Reset the settings

    sista::SwappableField field(50, 50);
    std::vector<sista::Pawn*> pawns = {};
    for (int i=0; i<50; i++) {
        pawns.push_back(
            new sista::Pawn(
                'v', sista::Coordinates(0, i),
                ANSI::Settings(
                    ANSI::ForegroundColor::F_GREEN,
                    ANSI::BackgroundColor::B_RED,
                    ANSI::Attribute::ITALIC
                )
            )
        );
        field.addPawn(pawns[i]);
    }
    sista::Border border(
        '#', ANSI::Settings(
            ANSI::ForegroundColor::F_YELLOW,
            ANSI::BackgroundColor::B_BLUE,
            ANSI::Attribute::BLINK
        )
    );
    field.print(border);
    sista::Coordinates coords[50];
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 50; j++) {
            coords[j] = field.movingByCoordinates(pawns[j], 1, 0, PACMAN_EFFECT);
            try {
                field.movePawn(pawns[j], coords[j]);
            } catch (std::invalid_argument& e) {
                field.addPawnToSwap(pawns[j], coords[j]);
                field.applySwaps();
            }
        }
        std::flush(std::cout);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
