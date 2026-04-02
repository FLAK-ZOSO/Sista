#include <sista/api.h>
#include <stdio.h>
#include <unistd.h>

static int fail_call(const char* name) {
    fprintf(stderr, "%s failed: code=%d message=%s\n", name,
            sista_getLastErrorCode(), sista_getLastErrorMessage());
    return 1;
}

int main() {
    CursorHandler_t cursor = sista_createCursor();
    if (cursor == NULL) {
        return fail_call("sista_createCursor");
    }

    // Use the cursor for some operations here (not implemented in this test)
    printf("Cursor created successfully\n");
    sleep(1);
    if (sista_moveCursor(cursor, DOWN, 5) != SISTA_OK) return fail_call("sista_moveCursor");
    printf("Moved cursor down by 5\n");
    sleep(1);
    if (sista_cursorGoTo(cursor, 10, 10) != SISTA_OK) return fail_call("sista_cursorGoTo");
    printf("Moved cursor to (10, 10)\n");
    sleep(1);
    struct sista_Coordinates coords = {20, 20};
    if (sista_cursorGoToCoordinates(cursor, coords) != SISTA_OK) return fail_call("sista_cursorGoToCoordinates");
    printf("Moved cursor to (20, 20) using Coordinates struct\n");
    sleep(1);

    // Clean up
    if (sista_destroyCursor(cursor) != SISTA_OK) return fail_call("sista_destroyCursor");
    return 0;
}
