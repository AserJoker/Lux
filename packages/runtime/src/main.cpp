#include "core/interface/IApplication.hpp"
#include <fmt/format.h>
int main(int argc, char *argv[]) {
  try {
    Lux::g_theApp->initialize(argc, argv);
    while (Lux::g_theApp->isRunning()) {
      Lux::g_theApp->tick();
    }
    Lux::g_theApp->finalize();
    return 0;
  } catch (std::exception &e) {
    fmt::print("{}", e.what());
    return -1;
  }
}