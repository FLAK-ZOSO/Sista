/*
 * SPDX-FileCopyrightText: 2026 FLAK-ZOSO <mattia.marchese.2006@gmail.com>
 * SPDX-License-Identifier: GPL-3.0-only
 */
#include <sista/api.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    if (sista_printHyperlink(NULL, "https://example.com") != SISTA_ERR_NULL_STRING ||
        sista_getLastErrorCode() != SISTA_ERR_NULL_STRING ||
        strcmp(sista_getLastErrorMessage(), "hyperlink text or URL is null") != 0 ||
        sista_printHyperlink("text", NULL) != SISTA_ERR_NULL_STRING ||
        sista_printHyperlink(NULL, NULL) != SISTA_ERR_NULL_STRING) {
        fprintf(stderr, "Hyperlink null argument checks failed\n");
        return 1;
    }
    if (sista_printHyperlink("Sista", "https://example.com/path%20name") != SISTA_OK ||
        sista_getLastErrorCode() != SISTA_OK ||
        strcmp(sista_getLastErrorMessage(), "ok") != 0 ||
        sista_printHyperlink("", "") != SISTA_OK) {
        fprintf(stderr, "Hyperlink success checks failed\n");
        return 1;
    }
    return 0;
}
