// g++ sista.cpp -o sista
#include <chrono>
#include <thread>
#include "include/sista/sista.hpp"

#define TEST_SIZE 50


class Character: public Pawn {
public:
    Character(char symbol_, Coordinates coordinates_, ANSI::Settings settings_): Pawn(symbol_, coordinates_, settings_) {}

    void print() override {
        Pawn::print();
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    ANSI::reset(); // Reset the settings
    std::cout << HIDE_CURSOR << CLS;
    Character pawn(
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
    Field field(TEST_SIZE, TEST_SIZE);
    field.addPawn(&pawn);
    field.addPawn(&pawn2);
    Coordinates coords(0, 0);
    for (int i=0; i<TEST_SIZE; i++) {
        for (int j=0; j<TEST_SIZE; j++) {
            field.movePawnBy(&pawn, 0, 1, MATRIX_EFFECT);
            field.movePawnBy(&pawn2, 0, -1, MATRIX_EFFECT);

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