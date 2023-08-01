#pragma once
#include <fmt/format.h>
#include <sstream>
#include <string>
#include <vector>
namespace Lux::Util {
class Strings {
private:
  Strings() = delete;
  Strings(const Strings &) = delete;

public:
  static std::vector<std::string> split(const std::string &source,
                                        const std::string &spliter);
  static std::string join(const std::vector<std::string> &strings);
  template <class T> static T to(const std::string &source) {
    std::stringstream ss(source);
    T value{};
    ss >> value;
    if (!ss.eof()) {
      throw std::runtime_error(fmt::format(
          "failed to convert string '{}' to {}", source, typeid(T).name()));
    }
    return value;
  }

  static std::string &tirmLeft(std::string &source);
  static std::string &tirmRight(std::string &source);
  static std::string &tirm(std::string &source);
};
} // namespace Lux::Util