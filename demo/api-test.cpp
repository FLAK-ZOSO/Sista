#include <sista/api.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <stdio.h>

static int fail_call(const char* name) {
    fprintf(stderr, "%s failed: code=%d message=%s\n", name,
            sista_getLastErrorCode(), sista_getLastErrorMessage());
    return 1;
}


int main(int argc, char* argv[]) {
    SwappableFieldHandler_t field = sista_createSwappableField(42, 42/2);
    if (field == nullptr) {
        return fail_call("sista_createSwappableField");
    }
    if (sista_printSwappableField(field, '#') != SISTA_OK) {
        return fail_call("sista_printSwappableField");
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    if (sista_destroySwappableField(field) != SISTA_OK) {
        return fail_call("sista_destroySwappableField");
    }

    if (sista_resetAnsi() != SISTA_OK) return fail_call("sista_resetAnsi");
    if (sista_setForegroundColor(sista_ForegroundColor::F_RED) != SISTA_OK) return fail_call("sista_setForegroundColor");
    printf("This text is red on default background.\n");
    if (sista_setBackgroundColor(sista_BackgroundColor::B_GREEN) != SISTA_OK) return fail_call("sista_setBackgroundColor");
    printf("This text is red on green background.\n");
    if (sista_setForegroundColor(sista_ForegroundColor::F_WHITE) != SISTA_OK) return fail_call("sista_setForegroundColor");
    printf("This text is white on green background.\n");
    if (sista_setBackgroundColor(sista_BackgroundColor::B_BLACK) != SISTA_OK) return fail_call("sista_setBackgroundColor");
    printf("This text is white on default background.\n");
    if (sista_setAttribute(sista_Attribute::A_BRIGHT) != SISTA_OK) return fail_call("sista_setAttribute");
    printf("This text is bright white on default background.\n");
    if (sista_resetAttribute(sista_Attribute::A_BRIGHT) != SISTA_OK) return fail_call("sista_resetAttribute");
    printf("This text is normal white on default background.\n");
    sista_RGBColor color { 255, 165, 0 };
    if (sista_setForegroundColorRGB(&color) != SISTA_OK) return fail_call("sista_setForegroundColorRGB");
    printf("This text is orange (RGB 255,165,0) on default background.\n");
    color = { 0, 0, 255 };
    if (sista_setBackgroundColorRGB(&color) != SISTA_OK) return fail_call("sista_setBackgroundColorRGB");
    printf("This text is orange (RGB 255,165,0) on blue (RGB 0,0,255) background.\n");
    if (sista_setForegroundColorRGB(nullptr) != SISTA_ERR_NULL_COLOR) return fail_call("sista_setForegroundColorRGB(nullptr)");
    if (sista_setBackgroundColorRGB(nullptr) != SISTA_ERR_NULL_COLOR) return fail_call("sista_setBackgroundColorRGB(nullptr)");
    printf("This text is still orange (RGB 255,165,0) on blue (RGB 0,0,255) background.\n");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    ANSISettingsHandler_t settings = sista_createANSISettings(
        sista_ForegroundColor::F_CYAN,
        sista_BackgroundColor::B_BLACK,
        sista_Attribute::A_UNDERLINE
    );
    if (settings != nullptr) {
        if (sista_applyANSISettings(settings) != SISTA_OK) return fail_call("sista_applyANSISettings");
        printf("This text is cyan on black background and underlined.\n");
        if (sista_destroyANSISettings(settings) != SISTA_OK) return fail_call("sista_destroyANSISettings");
    } else {
        return fail_call("sista_createANSISettings");
    }
    settings = sista_createANSISettingsRGB(
        { 255, 20, 147 }, // Deep Pink
        { 0, 0, 0 },      // Black
        sista_Attribute::A_ITALIC
    );
    if (settings != nullptr) {
        if (sista_applyANSISettings(settings) != SISTA_OK) return fail_call("sista_applyANSISettings");
        printf("This text is deep pink (RGB 255,20,147) on black background and italic.\n");
        if (sista_destroyANSISettings(settings) != SISTA_OK) return fail_call("sista_destroyANSISettings");
    } else {
        return fail_call("sista_createANSISettingsRGB");
    }
    if (sista_resetAnsi() != SISTA_OK) return fail_call("sista_resetAnsi");
    return 0;
}
