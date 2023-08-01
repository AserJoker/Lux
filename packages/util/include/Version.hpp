#pragma once
#include "stdint.h"
#include <sstream>
namespace Lux::Util {
class Version {
public:
  Version();
  Version(int32_t major, int32_t minor);
  inline int32_t &major() { return m_major; };
  inline int32_t &minor() { return m_minor; };

private:
  int32_t m_major;
  int32_t m_minor;
};

} // namespace Lux::Util

namespace std {
std::stringstream &operator>>(std::stringstream &ss, Lux::Util::Version &size);
}