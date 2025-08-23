#include <iostream>
#include "../include/sista/sista.hpp"


int main() {
    sista::setAttribute(sista::Attribute::BLINK);
    sista::setAttribute(sista::Attribute::ITALIC);
    std::cout << "Hello " << std::endl;
    sista::resetAttribute(sista::Attribute::BLINK);
    std::cout << "World" << std::endl;
    sista::resetAttribute(sista::Attribute::ITALIC);
    std::cout << "!" << std::endl;
    return 0;
}
