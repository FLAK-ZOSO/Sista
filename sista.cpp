// g++ sista.cpp -o sista
#include <chrono>
#include <thread>
#include "field.hpp"


int main() {
    ANSI::reset(); // Reset the settings
    std::cout << HIDE_CURSOR << CLS;
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
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << CLS;
    field.movePawn(&pawn, 2, 2);
    field.print();
    std::cout << SHOW_CURSOR;
    return 0;
}