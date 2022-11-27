// g++ sista.cpp -o sista
#include "field.hpp"


int main() {
    Pawn pawn(
        Coordinates(5, 4), 'X',
        ANSI::Settings(
            ANSI::ForegroundColor::F_RED,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );
    Field field(10, 10);
    field.addPawn(&pawn);
    field.print();
    return 0;
}