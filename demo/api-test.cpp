#include <sista/api.h>
#include <sista/sista.hpp>
#include <time.h>
#include <chrono>
#include <thread>


int main(int argc, char* argv[]) {
    SwappableFieldHandler_t field = sista_createSwappableField(42, 42/2);
    sista_printField(field, '#');
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sista_destroySwappableField(field);
}
