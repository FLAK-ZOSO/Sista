#include "../include/sista/sista.hpp"

int main() {
    for (int r = 0; r < 256; r += 16) {
        for (int g = 0; g < 256; g += 16) {
            for (int b = 0; b < 256; b += 16) {
                sista::setBackgroundColor(r, g, b);
                std::cout << ' ';
                sista::resetAnsi();
            }
        }
        std::cout << '\n';
    }
}
