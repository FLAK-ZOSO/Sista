// make
#include "../include/sista/sista.hpp"
#include <chrono>
#include <thread>


ANSI::Settings default_settings(
    ANSI::ForegroundColor::F_WHITE,
    ANSI::BackgroundColor::B_BLACK,
    ANSI::Attribute::RESET
);
sista::Border border(
    '#', ANSI::Settings(
        ANSI::ForegroundColor::F_WHITE,
        ANSI::BackgroundColor::B_BLACK,
        ANSI::Attribute::BLINK
    )
);


int main() {
    sista::SwappableField field(50, 50);
    std::vector<std::shared_ptr<sista::Pawn>> pawns;
    for (int i = 0; i < 50; i++) {
        pawns.push_back(
            std::make_shared<sista::Pawn>(
                'X', sista::Coordinates{
                    rand() % 50,
                    rand() % 50
                }, default_settings
            )
        );
        field.addPawn(pawns[i]);
    }
    field.print(border);

    std::vector<sista::Coordinates> coords(pawns.size());
    for (int i = 0; i < 1000; i++) {
        for (int k = 0; k < pawns.size(); k++) {
            coords[k] = field.movingByCoordinates(
                pawns[k].get(), rand() % 3 - 1, rand() % 3 - 1, PACMAN_EFFECT
            );
        }
        try {
            for (int k = 0; k < pawns.size(); k++) {
                field.movePawn(pawns[k].get(), coords[k]);
            }
        } catch (std::invalid_argument& e) {
            for (int k = 0; k < pawns.size(); k++) {
                field.addPawnToSwap(pawns[k].get(), coords[k]);
            }
            field.applySwaps();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}