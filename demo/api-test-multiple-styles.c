#include <sista/api.h>
#include <stdio.h>


int main() {
    sista_setAttribute(A_BRIGHT);
    printf("This text is bright.\n");
    sista_setAttribute(A_UNDERLINE);
    printf("This text is bright and underlined.\n");
    sista_resetAnsi();
    printf("This text is normal.\n");
    return 0;
}
