// make
#include <chrono>
#include <thread>
#include "include/sista/sista.hpp"

#define TEST_SIZE 50


int main() {
    std::ios_base::sync_with_stdio(false);
    sista::reset(); // Reset the settings

    std::vector<std::shared_ptr<sista::Pawn>> pawns = {
        std::make_shared<sista::Pawn>(
            'X', sista::Coordinates(0, 0),
            sista::ANSISettings(
                sista::ForegroundColor::F_RED,
                sista::BackgroundColor::B_BLACK,
                sista::Attribute::BRIGHT
            )
        ),
        std::make_shared<sista::Pawn>(
            'O', sista::Coordinates(TEST_SIZE*0.2, TEST_SIZE*0.7),
            sista::ANSISettings(
                sista::ForegroundColor::F_BLUE,
                sista::BackgroundColor::B_BLACK,
                sista::Attribute::BRIGHT
            )
        ),
        std::make_shared<sista::Pawn>(
            '@', sista::Coordinates(TEST_SIZE*0.3, 0),
            sista::ANSISettings(
                sista::ForegroundColor::F_MAGENTA,
                sista::BackgroundColor::B_YELLOW,
                sista::Attribute::REVERSE
            )
        ),
        std::make_shared<sista::Pawn>(
            '%', sista::Coordinates(TEST_SIZE*0.5, TEST_SIZE*0.5),
            sista::ANSISettings(
                sista::ForegroundColor::F_YELLOW,
                sista::BackgroundColor::B_MAGENTA,
                sista::Attribute::REVERSE
            )
        ),
        std::make_shared<sista::Pawn>(
            '!', sista::Coordinates(TEST_SIZE*0.7, TEST_SIZE*0.2),
            sista::ANSISettings(
                sista::ForegroundColor::F_CYAN,
                sista::BackgroundColor::B_BLACK,
                sista::Attribute::BRIGHT
            )
        ),
        std::make_shared<sista::Pawn>(
            '#', sista::Coordinates(TEST_SIZE*0.8, TEST_SIZE*0.8),
            sista::ANSISettings(
                sista::ForegroundColor::F_GREEN,
                sista::BackgroundColor::B_BLACK,
                sista::Attribute::BRIGHT
            )
        )
    };
    sista::Border border(
        '@', sista::ANSISettings(
            sista::ForegroundColor::F_YELLOW,
            sista::BackgroundColor::B_BLACK,
            sista::Attribute::BLINK
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
        coords[0] = field.movingByCoordinates(pawns[0].get(), 1, 1, PACMAN_EFFECT);
        coords[1] = field.movingByCoordinates(pawns[1].get(), -1, -1, PACMAN_EFFECT);
        coords[2] = field.movingByCoordinates(pawns[2].get(), -1, 1, PACMAN_EFFECT);
        coords[3] = field.movingByCoordinates(pawns[3].get(), 1, -1, PACMAN_EFFECT);
        coords[4] = field.movingByCoordinates(pawns[4].get(), 1, 0, PACMAN_EFFECT);
        coords[5] = field.movingByCoordinates(pawns[5].get(), 0, 1, PACMAN_EFFECT);
        try {
            for (int k=0; k<(int)pawns.size(); k++) {
                field.movePawn(pawns[k].get(), coords[k]);
            }
        } catch (const std::invalid_argument& e) {
            for (int k=0; k<(int)pawns.size(); k++) {
                field.addPawnToSwap(pawns[k].get(), coords[k]);
            }
            field.applySwaps();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << std::flush;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return 0;
}