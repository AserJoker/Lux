#ifndef _H_LUX_ELEMENT_ELEMENT_
#define _H_LUX_ELEMENT_ELEMENT_
#include "core/Context.hpp"
#include "core/Dependence.hpp"
#include "core/Object.hpp"
#include "core/Value.hpp"
#include <vector>

namespace lux::element {
typedef std::map<std::string, std::string> Props;
class Element : public core::Object {
private:
  core::Pointer<Element> _pNext;
  core::Pointer<Element> _pChildren;
  Element *_pParent;
  std::string _szName;
  std::map<std::string, core::Pointer<core::Object>> _ctx;
  core::Pointer<core::Context> _pContext;

protected:
  template <class T>
  void provide(const std::string &name, core::Pointer<T> value) {
    _ctx[name] = value.cast<core::Object>();
  }
  template <class T> core::Pointer<T> inject(const std::string &name) {
    auto parent = _pParent;
    while (parent) {
      if (parent->_ctx.contains(name)) {
        return parent->_ctx[name].cast<T>();
      }
      parent = parent->_pParent;
    }
    return nullptr;
  }
  virtual void setProps(Props props) {
    if (props.contains("name")) {
      _szName = props.at("name");
      auto indexed =
          _pContext->getContext<std::map<std::string, core::Pointer<Element>>>(
              "element#indexed");
      if (indexed == nullptr) {
        _pContext->setContext<std::map<std::string, core::Pointer<Element>>>(
            "element#indexed", {});
        indexed =
            _pContext
                ->getContext<std::map<std::string, core::Pointer<Element>>>(
                    "element#indexed");
      }
      indexed->getValue().insert({_szName, this});
    }
  }
  virtual void setStateValue(const std::string &name,
                             core::Pointer<core::Value>) {
    throw RUNTIME_ERROR(fmt::format("unknown state '{}'", name));
  };
  bool _isMounted;

public:
  DEFINE_TOKEN(lux::element::Element);
  static core::Pointer<Element> select(const std::string &name) {
    auto context = INJECT(core::Context);
    auto indexed =
        context->getContext<std::map<std::string, core::Pointer<Element>>>(
            "element#indexed");
    if (indexed != nullptr) {
      return indexed->getValue()[name];
    }
    return nullptr;
  }
  Element() {
    _pParent = nullptr;
    _isMounted = false;
    _pContext = INJECT(core::Context);
  }
  ~Element() override {
    auto indexed =
        _pContext->getContext<std::map<std::string, core::Pointer<Element>>>(
            "element#indexed");
    if (!_szName.empty()) {
      indexed->getValue().erase(_szName);
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
      if (!child->_isMounted) {
        child->onMounted();
        child->_isMounted = true;
      }
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
      auto prev = _pChildren;
      while (prev->_pNext != nullptr) {
        prev = prev->_pNext;
      }
      prev->_pNext = child;
    }
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
      child->_isMounted = false;
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
  template <class T> void setState(const std::string &name, T value) {
    setStateValue(name, core::value(value));
  }
  template <class T> static core::Pointer<T> create(const Props &props) {
    auto ele = INJECT(T).cast<Element>();
    ele->setProps(props);
    return ele.cast<T>();
  }
  static core::Pointer<element::Element> create(const std::string &token,
                                                const Props &props) {
    auto ele = core::Container::inject<element::Element>(token);
    if (ele != nullptr) {
      ele->setProps(props);
    }
    return ele;
  }
};
} // namespace lux::element
#endif