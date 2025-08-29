#include <sista/api.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <stdio.h>


int main(int argc, char* argv[]) {
    SwappableFieldHandler_t field = sista_createSwappableField(42, 42/2);
    sista_printField(field, '#');
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
    sista_resetAnsi();
    return 0;
}
