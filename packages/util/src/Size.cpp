#include "util/include/Size.hpp"
#include "util/include/Strings.hpp"
#include <fmt/format.h>
using namespace Lux::Util;
Size::Size() : m_width(0), m_height(0) {}
Size::Size(uint32_t width, uint32_t height)
    : m_width(width), m_height(height) {}

namespace std {
std::stringstream &operator>>(std::stringstream &ss, Lux::Util::Size &size) {
  ss >> size.width();
  char x;
  ss >> x;
  if (x != 'x') {
    ss << x << size.width();
    throw std::runtime_error(fmt::format("unexcept size source"));
  }
  ss >> size.height();
  return ss;
}
} // namespace std