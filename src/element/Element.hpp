#ifndef _H_LUX_ELEMENT_ELEMENT_
#define _H_LUX_ELEMENT_ELEMENT_
#include "core/Object.hpp"
#include <vector>
#define CHECK_PROP(name, value, type)                                          \
  if (value.getType() != StateType::type) {                                     \
    throw new RUNTIME_ERROR(fmt::format("prop '{}' must be {}", name, #type)); \
  }
namespace lux::element {
class Element : public core::Object {
public:
  class StateType {
  public:
    enum TYPE { STRING, NUMBER, BOOLEAN, EMPTY };

  private:
    std::string _value;
    TYPE _type;

  public:
    StateType() : _value(""), _type(EMPTY){};
    double toNumber() { return std::stod(_value); }
    std::string toString() { return _value; }
    bool toBoolean() { return _value == "true"; }
    TYPE getType() { return _type; }
    StateType(bool val):_value(val?"true":"false"),_type(BOOLEAN){}
    StateType(double val):_value(fmt::format("{}",val)),_type(NUMBER){}
    StateType(int val):_value(fmt::format("{}",val)),_type(NUMBER){}
    StateType(const std::string& val):_value(val),_type(STRING){}
    StateType(const char * val):_value(val),_type(STRING){}
  };

private:
  static std::map<std::string, core::Pointer<Element>> _indexed;
  core::Pointer<Element> _pNext;
  core::Pointer<Element> _pChildren;
  Element *_pParent;
  std::string _szName;
  void setName(const std::string &name) {
    if (!_szName.empty()) {
      throw RUNTIME_ERROR("cannot reset element name");
    }
    if (name.empty()) {
      throw RUNTIME_ERROR("element name must not be empty");
    }
    _szName = name;
    Element::_indexed.insert(std::make_pair(name, this));
  }
protected:
  virtual void setProp(const std::string &name, StateType value) {
    if (name == "name") {
      CHECK_PROP(name, value, STRING);
      setName(value.toString());
      return;
    }
    throw RUNTIME_ERROR(fmt::format("unknown prop name: {}", name));
  }
public:
  static core::Pointer<Element> select(const std::string &name) {
    return Element::_indexed[name];
  }
  ~Element() override {
    if (!_szName.empty()) {
      Element::_indexed.erase(_szName);
    }
  }
  core::Pointer<Element> getNext() const { return _pNext; }
  core::Pointer<Element> getParent() const { return _pParent; }
  core::Pointer<Element> getChildren() const { return _pChildren; }
  virtual void onMounted() {}
  virtual void onUnmounted() {}
  virtual void onUpdate() {
    auto child = _pChildren;
    while (child != nullptr) {
      child->onUpdate();
      child = child->getNext();
    }
  }
  template <class T> void append(T ele) {
    core::Pointer<Element> child = ele.cast<Element>();
    child->_pParent = this;
    if (_pChildren == nullptr) {
      _pChildren = child;
    } else {
      auto child = _pChildren;
      while (child->_pNext != nullptr) {
        child = child->_pNext;
      }
      child->_pNext = child;
    }
    child->onMounted();
  }
  template <class T> bool remove(T ele) {
    core::Pointer<Element> child = ele.cast<Element>();
    bool result = false;
    if (child == _pChildren) {
      _pChildren = child->_pNext;
      result = true;
    } else {
      auto prev = _pChildren;
      while (prev->_pNext != nullptr) {
        if (prev->_pNext == child) {
          prev->_pNext = child->_pNext;
          result = true;
          break;
        }
        prev = prev->_pNext;
      }
    }
    if (result) {
      child->onUnmounted();
      child->_pParent = nullptr;
      child->_pNext = nullptr;
    }
    return result;
  }
  core::Pointer<Element> find(unsigned childId) {
    auto child = _pChildren;
    while (child != nullptr) {
      if (child->getId() == childId) {
        break;
      }
      child = child->_pNext;
    }
    return child;
  }
  template <class T>
  static core::Pointer<T> create(std::map<std::string, StateType> props) {
    auto ele = INJECT(T).cast<Element>();
    for (auto &pair : props) {
      ele->setProp(pair.first, pair.second);
    }
    return ele.cast<T>();
  }
  virtual void setState(const std::string& name,StateType value){
    throw RUNTIME_ERROR(fmt::format("unknown state name: {}", name));
  }
};
std::map<std::string, core::Pointer<Element>> Element::_indexed;
} // namespace lux::element
#endif