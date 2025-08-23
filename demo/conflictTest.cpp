#include <chrono>
#include <thread>
#include "../include/sista/sista.hpp"


int main() {
    sista::SwappableField field(10, 10);
    std::vector<std::shared_ptr<sista::Pawn>> pawns = {
        std::make_shared<sista::Pawn>(
            'X', sista::Coordinates(0, 0),
            sista::ANSISettings(
                sista::ForegroundColor::RED,
                sista::BackgroundColor::BLACK,
                sista::Attribute::FAINT
            )
        ),
        std::make_shared<sista::Pawn>(
            'O', sista::Coordinates(0, 8),
            sista::ANSISettings(
                sista::ForegroundColor::GREEN,
                sista::BackgroundColor::BLACK,
                sista::Attribute::UNDERSCORE
            )
        )
    };
    for (std::shared_ptr<sista::Pawn>& pawn : pawns) {
        field.addPawn(pawn);
    }
    sista::Border border(
        '#', sista::ANSISettings(
            sista::ForegroundColor::WHITE,
            sista::BackgroundColor::BLACK,
            sista::Attribute::BLINK
        )
    );
    field.print(border);
    sista::Coordinates coords[2];
    for (int i = 0; i < 10; i++) {
        coords[0] = field.movingByCoordinates(pawns[0].get(), 0, 1, sista::Effect::PACMAN);
        coords[1] = field.movingByCoordinates(pawns[1].get(), 0, -1, sista::Effect::PACMAN);
        try {
            field.movePawn(pawns[0].get(), coords[0]);
            field.movePawn(pawns[1].get(), coords[1]);
        } catch (std::invalid_argument& e) {
            field.addPawnToSwap(pawns[0].get(), coords[0]);
            field.addPawnToSwap(pawns[1].get(), coords[1]);
            field.applySwaps();
        }
        std::cout << "\x1b[13;12H";
        std::cout << "(" << pawns[0]->getCoordinates().x << ", " << pawns[0]->getCoordinates().y << ")\n";
        std::flush(std::cout);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
