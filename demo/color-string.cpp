#include <iostream>
#include "../include/sista/sista.hpp"

int main() {
    std::cout << sista::fgColorStr(sista::ForegroundColor::RED) << "This is red text" << sista::fgColorStr(sista::ForegroundColor::WHITE) << std::endl;
    std::string bgBlue = sista::bgColorStr(sista::BackgroundColor::BLUE);
    std::string attrBright = sista::attrStr(sista::Attribute::BRIGHT);
    std::cout << bgBlue << attrBright << "This is bright text on blue background";
    sista::resetAnsi();
    std::cout << " - back to normal" << std::endl;
    return 0;
}
