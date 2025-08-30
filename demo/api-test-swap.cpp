#include <sista/api.h>
#include <iostream>
#include <chrono>
#include <thread>


int main() {
    SwappableFieldHandler_t field = sista_createSwappableField(10, 10);
    if (field == nullptr) {
        return 1; // Could not allocate memory for the field
    }
    PawnHandler_t pawn_x = sista_createPawnInSwappableField(
        field, 'X',
        sista_createANSISettings(
            F_RED,
            B_BLACK,
            A_FAINT
        ),
        {4, 5}
    );
    if (pawn_x == nullptr) {
        return 1; // Could not allocate memory for the pawn
    }
    PawnHandler_t pawn_o = sista_createPawnInSwappableField(
        field, 'O',
        sista_createANSISettings(
            F_GREEN,
            B_BLACK,
            A_UNDERLINE
        ),
        {5, 5}
    );
    if (pawn_o == nullptr) {
        return 1; // Could not allocate memory for the pawn
    }
    BorderHandler_t border = sista_createBorder(
        '#', sista_createANSISettings(
            F_WHITE,
            B_BLACK,
            A_BLINK
        )
    );
    sista_printSwappableFieldWithBorder(field, border);
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sista_addPawnToSwap(field, pawn_x, {5, 5});
    sista_addPawnToSwap(field, pawn_o, {4, 5});
    sista_applySwaps(field);
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    sista_resetAnsi();
    sista_destroyBorder(border);
    sista_destroySwappableField(field);
    return 0;
}
