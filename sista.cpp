// g++ sista.cpp -o sista
#include <chrono>
#include <thread>
#include "field.hpp"


int main() {
    std::ios_base::sync_with_stdio(false);
    ANSI::reset(); // Reset the settings
    std::cout << HIDE_CURSOR << SS;
    Pawn pawn(
        Coordinates(0, 0), 'X',
        ANSI::Settings(
            ANSI::ForegroundColor::F_RED,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );
    Border border(
        '#', ANSI::Settings(
            ANSI::ForegroundColor::F_BLACK,
            ANSI::BackgroundColor::B_WHITE,
            ANSI::Attribute::BRIGHT
        )
    );
    Field field(10, 10);
    field.addPawn(&pawn);
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            field.movePawn(&pawn, Coordinates(i, j));
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            std::cout << SS;
            std::cout << "\x1b[1000A"; // Move the cursor up 1000 lines
            field.print(border);
        }
    }
    std::cout << SS;
    field.print(border);
    std::cout << SHOW_CURSOR;
    return 0;
}