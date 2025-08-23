#include <iostream>
#include "../include/sista/sista.hpp"


int main() {
    sista::setScreenMode(sista::ScreenMode::MONOCROME_TEXT_40_25);
    for (int i = 0; i < 256; i++) {
        sista::setForegroundColor(i);
        std::cout << i << ' ';
        if (i % 16 == 15) {
            std::cout << '\n';
        }
    }
    sista::unsetScreenMode(sista::ScreenMode::LINE_WRAPPING);
    for (int i = 0; i < 256; i++) {
        sista::setForegroundColor(i);
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    sista::setScreenMode(sista::ScreenMode::LINE_WRAPPING);
    for (int i = 0; i < 256; i++) {
        sista::setForegroundColor(i);
        std::cout << i << ' ';
    }
}
