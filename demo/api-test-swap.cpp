#include <sista/api.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>

static int fail_call(const char* name) {
    fprintf(stderr, "%s failed: code=%d message=%s\n", name,
            sista_getLastErrorCode(), sista_getLastErrorMessage());
    return 1;
}

int main() {
    if (sista_clearScreen(true) != SISTA_OK) return fail_call("sista_clearScreen(after)");
    std::flush(std::cout);

    SwappableFieldHandler_t field = sista_createSwappableField(10, 10);
    if (field == nullptr) {
        return fail_call("sista_createSwappableField");
    }
    ANSISettingsHandler_t settings_x = sista_createANSISettings(
        F_RED,
        B_BLACK,
        A_FAINT
    );
    if (settings_x == nullptr) {
        sista_destroySwappableField(field);
        return fail_call("sista_createANSISettings(settings_x)");
    }
    PawnHandler_t pawn_x = sista_createPawnInSwappableField(
        field, 'X',
        settings_x,
        {4, 5}
    );
    if (pawn_x == nullptr) {
        sista_destroyANSISettings(settings_x);
        sista_destroySwappableField(field);
        return fail_call("sista_createPawnInSwappableField(pawn_x)");
    }
    ANSISettingsHandler_t settings_o = sista_createANSISettings(
        F_GREEN,
        B_BLACK,
        A_UNDERLINE
    );
    if (settings_o == nullptr) {
        sista_destroyANSISettings(settings_x);
        sista_destroySwappableField(field);
        return fail_call("sista_createANSISettings(settings_o)");
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
        return fail_call("sista_createPawnInSwappableField(pawn_o)");
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
        return fail_call("sista_createANSISettings(settings_border)");
    }
    BorderHandler_t border = sista_createBorder(
        '#', settings_border
    );
    if (border == nullptr) {
        sista_destroyANSISettings(settings_o);
        sista_destroyANSISettings(settings_x);
        sista_destroySwappableField(field);
        return fail_call("sista_createBorder");
    }
    if (sista_clearScreen(1) != SISTA_OK) return fail_call("sista_clearScreen(before)");
    if (sista_printSwappableFieldWithBorder(field, border) != SISTA_OK) return fail_call("sista_printSwappableFieldWithBorder");
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    if (sista_addPawnToSwap(field, pawn_x, {5, 5}) != SISTA_OK) return fail_call("sista_addPawnToSwap(pawn_x)");
    if (sista_addPawnToSwap(field, pawn_o, {4, 5}) != SISTA_OK) return fail_call("sista_addPawnToSwap(pawn_o)");
    if (sista_applySwaps(field) != SISTA_OK) return fail_call("sista_applySwaps");
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    if (sista_resetAnsi() != SISTA_OK) return fail_call("sista_resetAnsi");
    if (sista_destroyANSISettings(settings_o) != SISTA_OK) return fail_call("sista_destroyANSISettings(settings_o)");
    if (sista_destroyANSISettings(settings_x) != SISTA_OK) return fail_call("sista_destroyANSISettings(settings_x)");
    if (sista_destroyBorder(border) != SISTA_OK) return fail_call("sista_destroyBorder");
    if (sista_destroyANSISettings(settings_border) != SISTA_OK) return fail_call("sista_destroyANSISettings(settings_border)");
    if (sista_destroySwappableField(field) != SISTA_OK) return fail_call("sista_destroySwappableField");
    return 0;
}
