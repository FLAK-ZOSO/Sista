#include <iostream>
#include "../include/sista/sista.hpp"

int main() {
    sista::ANSISettings settings(
        sista::RGBColor(10, 10, 10),
        sista::RGBColor(100, 100, 100), {
            sista::Attribute::BRIGHT,
            sista::Attribute::UNDERSCORE
        }
    );
    settings.apply();
    std::cout << "This is bright yellow text on blue background with underscore." << std::endl;
    settings.reset();
    std::cout << "Back to normal text." << std::endl;
    return 0;
}
