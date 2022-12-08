// g++ sista.cpp -o sista
#include <chrono>
#include <thread>
#include "include/sista/sista.hpp"


int main() {
    std::ios_base::sync_with_stdio(false);
    ANSI::reset(); // Reset the settings
    std::cout << HIDE_CURSOR << CLS;
    Pawn pawn(
        Coordinates(0, 0), 'X',
        ANSI::Settings(
            ANSI::ForegroundColor::F_RED,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );
    Pawn pawn2(
        Coordinates(49, 49), 'O',
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
    Field field(50, 50);
    field.addPawn(&pawn);
    field.addPawn(&pawn2);
    Coordinates coords(0, 0);
    for (int i=0; i<50; i++) {
        for (int j=0; j<50; j++) {
            field.movePawnBy(&pawn, 1, 1, MATRIX_EFFECT);
            field.movePawnBy(&pawn2, -1, -1, MATRIX_EFFECT);

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            clearScreen();
            field.print(border);
        }
    }
    std::cout << CLS;
    field.print(border);
    std::cout << SHOW_CURSOR;
    return 0;
}