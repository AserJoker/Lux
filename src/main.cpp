#include <iostream>
#include<SDL.h>
#if defined(_WIN32)
#include<Windows.h>
#endif

#include "core/Object.hpp"
#include "core/Container.hpp"

using namespace lux;

int main(int argc, char* argv[]) {
#if defined(_WIN32)
    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleOutputCP(CP_UTF8);
    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
    try {

        return 0;

    }
    catch (std::exception& exp) {
        std::cout << exp.what() << std::endl;
        return -1;
    }
}