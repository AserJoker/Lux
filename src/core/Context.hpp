#ifndef _H_LUX_CORE_CONTEXT_
#define _H_LUX_CORE_CONTEXT_
#include "Object.hpp"
#include "Value.hpp"
namespace lux::core {
class Context : public Object {
private:
  std::map<std::string, Pointer<Value>> _context;

public:
  DEFINE_TOKEN(lux::core::Context);
  template <class T> void setContext(const std::string &name, T val) {
    _context[name] = value(val);
  }
  template <class T>
  core::Pointer<RefValue<T>> getContext(const std::string &name) {
    if (_context.contains(name)) {
      return _context[name].cast<RefValue<T>>();
    }
    return nullptr;
  }
};
} // namespace lux::core

#endif