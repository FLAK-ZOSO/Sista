#pragma once

void clearScreen(bool spaces=true) {
    if (spaces) {
        std::cout << CSI_ << "2J"; // Clear screen
        std::cout << "\x1b[3J"; // Clear scrollback buffer
    }
    std::cout << "\x1b[0;0H"; // Move cursor to top-left corner
}