#include <sista/api.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    CursorHandler_t cursor = sista_createCursor();
    if (cursor == NULL) {
        fprintf(stderr, "Failed to create cursor\n");
        return 1;
    }

    // Use the cursor for some operations here (not implemented in this test)
    printf("Cursor created successfully\n");
    sleep(1);
    sista_moveCursor(cursor, DOWN, 5);
    printf("Moved cursor down by 5\n");
    sleep(1);
    sista_cursorGoTo(cursor, 10, 10);
    printf("Moved cursor to (10, 10)\n");
    sleep(1);
    struct sista_Coordinates coords = {20, 20};
    sista_cursorGoToCoordinates(cursor, coords);
    printf("Moved cursor to (20, 20) using Coordinates struct\n");
    sleep(1);

    // Clean up
    sista_destroyCursor(cursor);
    return 0;
}
