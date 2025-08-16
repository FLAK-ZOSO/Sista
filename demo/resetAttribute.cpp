#include "../include/sista/sista.hpp"


int main() {
    ANSI::setAttribute(ANSI::Attribute::BLINK);
    ANSI::setAttribute(ANSI::Attribute::ITALIC);
    std::cout << "Hello " << std::endl;
    ANSI::resetAttribute(ANSI::Attribute::BLINK);
    std::cout << "World" << std::endl;
    ANSI::resetAttribute(ANSI::Attribute::ITALIC);
    std::cout << "!" << std::endl;
    return 0;
}
