#include <sista/api.h>
#include <stdio.h>

static int fail_call(const char* name) {
    fprintf(stderr, "%s failed: code=%d message=%s\n", name,
            sista_getLastErrorCode(), sista_getLastErrorMessage());
    return 1;
}


int main() {
    if (sista_setAttribute(A_BRIGHT) != SISTA_OK) return fail_call("sista_setAttribute(A_BRIGHT)");
    printf("This text is bright.\n");
    if (sista_setAttribute(A_UNDERLINE) != SISTA_OK) return fail_call("sista_setAttribute(A_UNDERLINE)");
    printf("This text is bright and underlined.\n");
    if (sista_resetAnsi() != SISTA_OK) return fail_call("sista_resetAnsi");
    printf("This text is normal.\n");
    return 0;
}
