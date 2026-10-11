/*
 * SPDX-FileCopyrightText: 2026 FLAK-ZOSO <mattia.marchese.2006@gmail.com>
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <iostream>
#include <sstream>
#include <string>
#include "../include/sista/ansi.hpp"

int main() {
    std::ostringstream output;
    auto* original = std::cout.rdbuf(output.rdbuf());
    sista::printHyperlink("Sista", "https://example.com/path%20name?q=1&x=2#part");
    std::cout << " plain ";
    sista::printHyperlink("", "https://example.com");
    sista::printHyperlink("no destination", "");
    sista::printHyperlink(u8"Tere, maailm! 🌍", "https://example.com/world");
    sista::printHyperlink("next", "https://example.com/next");
    std::cout.rdbuf(original);

    const std::string expected =
        "\x1b]8;;https://example.com/path%20name?q=1&x=2#part\x1b\\"
        "Sista\x1b]8;;\x1b\\ plain "
        "\x1b]8;;https://example.com\x1b\\\x1b]8;;\x1b\\"
        "\x1b]8;;\x1b\\no destination\x1b]8;;\x1b\\"
        "\x1b]8;;https://example.com/world\x1b\\"
        u8"Tere, maailm! 🌍\x1b]8;;\x1b\\"
        "\x1b]8;;https://example.com/next\x1b\\next\x1b]8;;\x1b\\";
    if (output.str() != expected) {
        std::cerr << "Hyperlink output differs from the expected OSC 8 bytes\n";
        return 1;
    }
    std::cout << "Hyperlink output checks passed\n";
}
