#pragma once
#include <sstream>
#include <string>
namespace Lux::Util {
class Size {
public:
  Size(uint32_t width, uint32_t height);
  Size();
  inline uint32_t &width() { return m_width; };
  inline uint32_t &height() { return m_height; };

private:
  uint32_t m_width;
  uint32_t m_height;
};
} // namespace Lux::Util
namespace std {
std::stringstream &operator>>(std::stringstream &ss, Lux::Util::Size &size);
}