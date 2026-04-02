#include <sista/api.h>
#include <chrono>
#include <thread>
#include <stdio.h>

static int fail_call(const char* name) {
    fprintf(stderr, "%s failed: code=%d message=%s\n", name,
            sista_getLastErrorCode(), sista_getLastErrorMessage());
    return 1;
}


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
        return fail_call("allocation step");
    }
    if (sista_printFieldWithBorder(field, border) != SISTA_OK) {
        return fail_call("sista_printFieldWithBorder");
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    if (sista_destroyBorder(border) != SISTA_OK) return fail_call("sista_destroyBorder");
    if (sista_destroyField(field) != SISTA_OK) return fail_call("sista_destroyField");
    if (sista_destroyANSISettings(settings) != SISTA_OK) return fail_call("sista_destroyANSISettings");
    return 0;
}