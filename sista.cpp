// g++ sista.cpp -o sista
#include "pawn.hpp"


int main() {
    Pawn pawn(
        Coordinates(0, 0), 'X',
        ANSI::Settings(
            ANSI::ForegroundColor::F_RED,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );
    pawn.print();
    ANSI::reset();
    return 0;
}