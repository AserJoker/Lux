#include <SDL.h>
#include <iostream>
#if defined(_WIN32)
#include <Windows.h>
#endif

#include "core/Container.hpp"
#include "core/Object.hpp"

#include "system/Application.hpp"
#include "system/EventBus.hpp"
#include "system/Native.hpp"
#include "system/Graphic.hpp"
using namespace lux;

int main(int argc, char* argv[]) {
#if defined(_WIN32)
  // Set console code page to UTF-8 so console known how to interpret string
  // data
  SetConsoleOutputCP(CP_UTF8);
  // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
  setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
  PROVIDE(system::EventBus);
  PROVIDE(system::Native);
  PROVIDE(system::Application);
  PROVIDE(system::Graphic);
  try {
    INJECT(system::Native);
    INJECT(system::Graphic);
    auto app = INJECT(system::Application);
    app->run();
    return 0;
  }
  catch (std::exception& exp) {
    std::cout << exp.what() << std::endl;
    return -1;
  }
}