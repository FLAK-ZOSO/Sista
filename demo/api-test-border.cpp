#include <sista/api.h>
#include <chrono>
#include <thread>


int main(int argc, char* argv[]) {
    char border_char = '*';
    if (argc > 1) {
        border_char = argv[1][0];
    }
    ANSISettingsHandler_t settings = sista_createANSISettingsRGB(
        { 42, 69, 104 },
        { 200, 0, 100 },
        sista_Attribute::A_BLINK_FAST
    );
    FieldHandler_t field = sista_createField(42, 21);
    BorderHandler_t border = sista_createBorder(border_char, settings);
    if (border == nullptr || field == nullptr || settings == nullptr) {
        return 1; // Could not allocate memory for one of the objects
    }
    sista_printFieldWithBorder(field, border);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sista_destroyBorder(border);
    sista_destroyField(field);
    sista_destroyANSISettings(settings);
    return 0;
}