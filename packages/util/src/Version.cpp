#include "util/include/Version.hpp"
#include <fmt/format.h>
using namespace Lux::Util;
Version::Version() : m_major(0), m_minor(0) {}
Version::Version(int32_t major, int32_t minor)
    : m_major(major), m_minor(minor) {}

namespace std {
std::stringstream &operator>>(std::stringstream &ss,
                              Lux::Util::Version &version) {
  ss >> version.major();
  char x;
  ss >> x;
  if (x != '.') {
    ss << x << version.major();
    throw std::runtime_error(fmt::format("unexcept version source"));
  }
  ss >> version.minor();
  return ss;
}
} // namespace std