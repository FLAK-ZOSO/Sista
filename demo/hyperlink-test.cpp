/*
 * SPDX-FileCopyrightText: 2026 FLAK-ZOSO <mattia.marchese.2006@gmail.com>
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include <chrono>
#include <thread>
#include <iostream>
#include "../include/sista/sista.hpp"


int main() {
    sista::printHyperlink("Do you support OSC8?", "https://github.com/Alhadis/OSC8-Adoption");
    std::cout << std::endl;
}