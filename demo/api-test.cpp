#include <sista/api.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <stdio.h>


int main(int argc, char* argv[]) {
    SwappableFieldHandler_t field = sista_createSwappableField(42, 42/2);
    sista_printSwappableField(field, '#');
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sista_destroySwappableField(field);

    sista_resetAnsi();
    sista_setForegroundColor(sista_ForegroundColor::F_RED);
    printf("This text is red on default background.\n");
    sista_setBackgroundColor(sista_BackgroundColor::B_GREEN);
    printf("This text is red on green background.\n");
    sista_setForegroundColor(sista_ForegroundColor::F_WHITE);
    printf("This text is white on green background.\n");
    sista_setBackgroundColor(sista_BackgroundColor::B_BLACK);
    printf("This text is white on default background.\n");
    sista_setAttribute(sista_Attribute::A_BRIGHT);
    printf("This text is bright white on default background.\n");
    sista_resetAttribute(sista_Attribute::A_BRIGHT);
    printf("This text is normal white on default background.\n");
    sista_RGBColor color { 255, 165, 0 };
    sista_setForegroundColorRGB(&color);
    printf("This text is orange (RGB 255,165,0) on default background.\n");
    color = { 0, 0, 255 };
    sista_setBackgroundColorRGB(&color);
    printf("This text is orange (RGB 255,165,0) on blue (RGB 0,0,255) background.\n");
    sista_setForegroundColorRGB(nullptr); // This call has no effect
    sista_setBackgroundColorRGB(nullptr); // This call has no effect
    printf("This text is still orange (RGB 255,165,0) on blue (RGB 0,0,255) background.\n");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    ANSISettingsHandler_t settings = sista_createANSISettings(
        sista_ForegroundColor::F_CYAN,
        sista_BackgroundColor::B_BLACK,
        sista_Attribute::A_UNDERLINE
    );
    if (settings != nullptr) {
        sista_applyANSISettings(settings);
        printf("This text is cyan on black background and underlined.\n");
        sista_destroyANSISettings(settings);
    }
    settings = sista_createANSISettingsRGB(
        { 255, 20, 147 }, // Deep Pink
        { 0, 0, 0 },      // Black
        sista_Attribute::A_ITALIC
    );
    if (settings != nullptr) {
        sista_applyANSISettings(settings);
        printf("This text is deep pink (RGB 255,20,147) on black background and italic.\n");
        sista_destroyANSISettings(settings);
    }
    sista_resetAnsi();
    return 0;
}
