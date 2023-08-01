#include "util/include/Strings.hpp"
#include <sstream>
using namespace Lux::Util;
std::vector<std::string> Strings::split(const std::string &source,
                                        const std::string &spliter) {
  std::vector<std::string> result;
  auto selector = source;
  for (;;) {
    auto offset = selector.find(spliter);
    if (offset == std::string::npos) {
      result.push_back(selector);
      break;
    }
    result.push_back(selector.substr(0, offset));
    selector = selector.substr(offset + 1);
  }
  return result;
}

std::string Strings::join(const std::vector<std::string> &strings) {
  std::string result;
  for (auto &str : strings) {
    result += str;
  }
  return result;
}
std::string &Strings::tirmLeft(std::string &source) {
  source.erase(0, source.find_first_not_of("\n\t\r "));
  return source;
}
std::string &Strings::tirmRight(std::string &source) {
  source.erase(source.find_last_not_of("\n\t\r ") + 1);
  return source;
}
std::string &Strings::tirm(std::string &source) {
  return Strings::tirmLeft(Strings::tirmRight(source));
}