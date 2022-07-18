#ifndef _H_CORE_VALUE_
#define _H_CORE_VALUE_
#include "Object.hpp"
#include "util.hpp"
namespace lux::core {
class Value : public Object {};
template <class T, c_string token> class SimpleValue : public Value {
private:
  T _value{};

public:
  DEFINE_TOKEN(token);
  void setValue(T val) { _value = val; }
  T getValue() { return _value; }
  static core::Pointer<Value> create(T val){
    using Self = SimpleValue<T,token>;
    auto ptr = INJECT(Self);
    ptr->setValue(val);
    return ptr.cast<Value>();
  }
};
using Integer = SimpleValue<int,"lux::core::integer">;
using Double = SimpleValue<double,"lux::core::double">;
using String = SimpleValue<std::string,"lux::core::string">;
using Boolean = SimpleValue<bool,"lux::core::boolean">;
} // namespace lux::core

#endif