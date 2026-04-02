#include <sista/api.h>
#include <stdio.h>
#include <string.h>

static int expect_code(const char* label, int actual, int expected) {
    if (actual != expected) {
        fprintf(stderr, "%s: expected code %d, got %d\n", label, expected, actual);
        return 1;
    }
    return 0;
}

static int expect_message(const char* label, const char* expected) {
    const char* actual = sista_getLastErrorMessage();
    if (actual == NULL) {
        fprintf(stderr, "%s: expected message '%s', got NULL\n", label, expected);
        return 1;
    }
    if (strcmp(actual, expected) != 0) {
        fprintf(stderr, "%s: expected message '%s', got '%s'\n", label, expected, actual);
        return 1;
    }
    return 0;
}

int main(void) {
    int failures = 0;
    struct sista_Coordinates zero_coords;
    zero_coords.y = 0;
    zero_coords.x = 0;

    failures += expect_code("print null field return", sista_printField(NULL, '#'), SISTA_ERR_NULL_FIELD);
    failures += expect_code("print null field last error", sista_getLastErrorCode(), SISTA_ERR_NULL_FIELD);
    failures += expect_message("print null field message", "field is null");

    failures += expect_code("fg rgb null return", sista_setForegroundColorRGB(NULL), SISTA_ERR_NULL_COLOR);
    failures += expect_code("fg rgb null last error", sista_getLastErrorCode(), SISTA_ERR_NULL_COLOR);
    failures += expect_message("fg rgb null message", "color is null");

    failures += expect_code("move null field return", sista_movePawn(NULL, NULL, zero_coords), SISTA_ERR_NULL_FIELD);
    failures += expect_code("move null field last error", sista_getLastErrorCode(), SISTA_ERR_NULL_FIELD);
    failures += expect_message("move null field message", "field is null");

    failures += expect_code("add swap null field return", sista_addPawnToSwap(NULL, NULL, zero_coords), SISTA_ERR_NULL_FIELD);
    failures += expect_code("add swap null field last error", sista_getLastErrorCode(), SISTA_ERR_NULL_FIELD);
    failures += expect_message("add swap null field message", "field is null");

    failures += expect_code("apply swaps null field return", sista_applySwaps(NULL), SISTA_ERR_NULL_FIELD);
    failures += expect_code("apply swaps null field last error", sista_getLastErrorCode(), SISTA_ERR_NULL_FIELD);
    failures += expect_message("apply swaps null field message", "field is null");

    failures += expect_code("destroy null cursor return", sista_destroyCursor(NULL), SISTA_ERR_NULL_CURSOR);
    failures += expect_code("destroy null cursor last error", sista_getLastErrorCode(), SISTA_ERR_NULL_CURSOR);
    failures += expect_message("destroy null cursor message", "cursor is null");

    failures += expect_code("destroy null border return", sista_destroyBorder(NULL), SISTA_ERR_NULL_BORDER);
    failures += expect_code("destroy null border last error", sista_getLastErrorCode(), SISTA_ERR_NULL_BORDER);
    failures += expect_message("destroy null border message", "border is null");

    failures += expect_code("destroy null field return", sista_destroyField(NULL), SISTA_ERR_NULL_FIELD);
    failures += expect_code("destroy null field last error", sista_getLastErrorCode(), SISTA_ERR_NULL_FIELD);
    failures += expect_message("destroy null field message", "field is null");

    if (failures != 0) {
        fprintf(stderr, "api-test-errors: %d assertion(s) failed\n", failures);
        return 1;
    }

    printf("api-test-errors: all checks passed\n");
    return 0;
}
