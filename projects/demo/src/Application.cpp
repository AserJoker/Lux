#include "../include/Application.hpp"
#include "util/include/Strings.hpp"
#include <fmt/format.h>
using namespace Lux::Demo;
using namespace Lux::Util;
Application::Application() {
  auto data = Strings::join({""});
  fmt::print("{}", data);
}