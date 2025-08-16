#include "../include/sista/sista.hpp"


int main() {
    ANSI::setScreenMode(ANSI::ScreenMode::MONOCROME_TEXT_40_25);
    for (int i = 0; i < 256; i++) {
        ANSI::setForegroundColor(i);
        std::cout << i << ' ';
        if (i % 16 == 15) {
            std::cout << '\n';
        }
    }
    ANSI::unsetScreenMode(ANSI::ScreenMode::LINE_WRAPPING);
    for (int i = 0; i < 256; i++) {
        ANSI::setForegroundColor(i);
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    ANSI::setScreenMode(ANSI::ScreenMode::LINE_WRAPPING);
    for (int i = 0; i < 256; i++) {
        ANSI::setForegroundColor(i);
        std::cout << i << ' ';
    }
}
