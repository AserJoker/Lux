#ifndef _H_LUX_CORE_DEFER_
#define _H_LUX_CORE_DEFER_
#include <functional>
namespace lux::core {
class Defer {
public:
  typedef void (*DEFER_FN)();

private:
  std::function<void(void)> _pFn;

public:
  Defer(std::function<void(void)> fn) : _pFn(fn) {}
  ~Defer() { _pFn(); }
};
} // namespace lux::core
#endif