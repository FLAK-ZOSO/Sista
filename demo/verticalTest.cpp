#include <chrono>
#include <thread>
#include "../include/sista/sista.hpp"


int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    sista::resetAnsi(); // Reset the settings

    sista::SwappableField field(50, 50);
    std::vector<std::shared_ptr<sista::Pawn>> pawns = {};
    for (int i=0; i<50; i++) {
        pawns.push_back(
            std::make_shared<sista::Pawn>(
                'v', sista::Coordinates(0, i),
                sista::ANSISettings(
                    sista::ForegroundColor::GREEN,
                    sista::BackgroundColor::RED,
                    sista::Attribute::ITALIC
                )
            )
        );
        field.addPawn(pawns[i]);
    }
    sista::Border border(
        '#', sista::ANSISettings(
            sista::ForegroundColor::YELLOW,
            sista::BackgroundColor::BLUE,
            sista::Attribute::BLINK
        )
    );
    field.print(border);
    sista::Coordinates coords[50];
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 50; j++) {
            coords[j] = field.movingByCoordinates(pawns[j].get(), 1, 0, sista::Effect::PACMAN);
            try {
                field.movePawn(pawns[j].get(), coords[j]);
            } catch (std::invalid_argument& e) {
                field.addPawnToSwap(pawns[j].get(), coords[j]);
                field.applySwaps();
            }
        }
        std::flush(std::cout);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
