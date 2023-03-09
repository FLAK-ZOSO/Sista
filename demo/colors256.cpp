#include "../include/sista/sista.hpp"

int main() {
    for (int i = 0; i < 256; i++) {
        ANSI::setForegroundColor(i);
        std::cout << i << ' ';
        if (i % 16 == 15) {
            std::cout << '\n';
        }
    }
    for (int i = 0; i < 256; i++) {
        ANSI::setBackgroundColor(i);
        std::cout << i << ' ';
        if (i % 16 == 15) {
            std::cout << '\n';
        }
    }
}