#ifndef _H_CORE_VALUE_
#define _H_CORE_VALUE_
#include "Object.hpp"
#include "util.hpp"
namespace lux::core {
  class Value : public Object {};
  template <class T> class SimpleValue : public Value {
  private:
    T _value{};

  public:
    void setValue(T val) { _value = val; }
    T getValue() { return _value; }

  };
  class Integer :public SimpleValue<int> {
  public:
    DEFINE_TOKEN(lux::core::Integer);
  };
  class Double :public SimpleValue<double> {
  public:
    DEFINE_TOKEN(lux::core::Double);
  };
  class String :public SimpleValue<std::string> {
  public:
    DEFINE_TOKEN(lux::core::String);
  };
  class Boolean :public SimpleValue<bool> {
  public:
    DEFINE_TOKEN(lux::core::Boolean);
  };
  template <class T>  core::Pointer<Value> value(T val) {
    return nullptr;
  }
  template <>  core::Pointer<Value> value<unsigned int>(unsigned int val) {
    auto value = INJECT(Integer);
    value->setValue(val);
    return value.cast<Value>();
  }
  template <>  core::Pointer<Value> value<int>(int val) {
    auto value = INJECT(Integer);
    value->setValue(val);
    return value.cast<Value>();
  }
  template <>  core::Pointer<Value> value<double>(double val) {
    auto value = INJECT(Double);
    value->setValue(val);
    return value.cast<Value>();
  }
  template <>  core::Pointer<Value> value<const char*>(const char* val) {
    auto value = INJECT(String);
    value->setValue(val);
    return value.cast<Value>();
  }
  template <>  core::Pointer<Value> value<std::string>(std::string val) {
    auto value = INJECT(String);
    value->setValue(val);
    return value.cast<Value>();
  }
  template <>  core::Pointer<Value> value<bool>(bool val) {
    auto value = INJECT(Boolean);
    value->setValue(val);
    return value.cast<Value>();
  }
} // namespace lux::core

#endif