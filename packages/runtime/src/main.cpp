#include "core/interface/IApplication.hpp"
#include <fmt/format.h>
int main(int argc, char *argv[]) {
  auto error = Lux::g_theApp->Initialize(argc, argv);
  if (error != 0) {
    fmt::print("failed to init application,error is {}", error);
    return -1;
  }
  while (Lux::g_theApp->isRunning()) {
    Lux::g_theApp->Tick();
  }
  Lux::g_theApp->Finalize();
  return 0;
}