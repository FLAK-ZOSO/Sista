#include <sista/api.h>
#include <iostream>
#include <chrono>
#include <thread>

/* When reading this file, consider that checking for nullptr each time can be
*  omitted for clarity, as it is just defensive programming... a failed allocation
*  would be very rare in a simple demo like this.
*/ 
int main() {
    SwappableFieldHandler_t field = sista_createSwappableField(10, 10);
    if (field == nullptr) {
        return 1; // Could not allocate memory for the field
    }
    ANSISettingsHandler_t settings_x = sista_createANSISettings(
        F_RED,
        B_BLACK,
        A_FAINT
    );
    if (settings_x == nullptr) {
        sista_destroySwappableField(field);
        return 1; // Could not allocate memory for the settings
    }
    PawnHandler_t pawn_x = sista_createPawnInSwappableField(
        field, 'X',
        settings_x,
        {4, 5}
    );
    if (pawn_x == nullptr) {
        sista_destroyANSISettings(settings_x);
        sista_destroySwappableField(field);
        return 1; // Could not allocate memory for the pawn
    }
    ANSISettingsHandler_t settings_o = sista_createANSISettings(
        F_GREEN,
        B_BLACK,
        A_UNDERLINE
    );
    if (settings_o == nullptr) {
        sista_destroyANSISettings(settings_x);
        sista_destroySwappableField(field);
        return 1; // Could not allocate memory for the settings
    }
    PawnHandler_t pawn_o = sista_createPawnInSwappableField(
        field, 'O',
        settings_o,
        {5, 5}
    );
    if (pawn_o == nullptr) {
        sista_destroyANSISettings(settings_o);
        sista_destroyANSISettings(settings_x);
        sista_destroySwappableField(field);
        return 1; // Could not allocate memory for the pawn
    }
    ANSISettingsHandler_t settings_border = sista_createANSISettings(
        F_WHITE,
        B_BLACK,
        A_BLINK
    );
    if (settings_border == nullptr) {
        sista_destroyANSISettings(settings_o);
        sista_destroyANSISettings(settings_x);
        sista_destroySwappableField(field);
        return 1; // Could not allocate memory for the settings
    }
    BorderHandler_t border = sista_createBorder(
        '#', settings_border
    );
    if (border == nullptr) {
        sista_destroyANSISettings(settings_o);
        sista_destroyANSISettings(settings_x);
        sista_destroySwappableField(field);
        return 1; // Could not allocate memory for the border
    }
    sista_printSwappableFieldWithBorder(field, border);
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sista_addPawnToSwap(field, pawn_x, {5, 5});
    sista_addPawnToSwap(field, pawn_o, {4, 5});
    sista_applySwaps(field);
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    sista_resetAnsi();
    sista_destroyANSISettings(settings_o);
    sista_destroyANSISettings(settings_x);
    sista_destroyBorder(border);
    sista_destroyANSISettings(settings_border);
    sista_destroySwappableField(field);
    return 0;
}
