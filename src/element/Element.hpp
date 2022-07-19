#ifndef _H_LUX_ELEMENT_ELEMENT_
#define _H_LUX_ELEMENT_ELEMENT_
#include "core/Object.hpp"
#include "core/Value.hpp"
#include <vector>

namespace lux::element {
    typedef std::map<std::string, core::Pointer<core::Value>> Props;
    class Element : public core::Object {
    private:
        static std::map<std::string, core::Pointer<Element>> _indexed;
        core::Pointer<Element> _pNext;
        core::Pointer<Element> _pChildren;
        Element* _pParent;
        std::string _szName;
        std::map<std::string, core::Pointer<core::Object>> _ctx;

    protected:
        template <class T>
        void provide(const std::string& name, core::Pointer<T> value) {
            _ctx[name] = value.cast<core::Object>();
        }
        template <class T> core::Pointer<T> inject(const std::string& name) {
            auto parent = _pParent;
            while (parent) {
                if (parent->_ctx.contains(name)) {
                    return parent->_ctx[name].cast<T>();
                }
                parent = parent->_pParent;
            }
            return nullptr;
        }
        virtual void
            setProps(std::map<std::string, core::Pointer<core::Value>> props) {
            if (props.contains("name")) {
                auto name = props.at("name").cast<core::RefValue<std::string>>();
                _szName = name->getValue();
                Element::_indexed.insert({_szName,this});
            }
        }
        virtual void setStateValue(const std::string& name, core::Pointer<core::Value>) {
            throw RUNTIME_ERROR(fmt::format("unknown state '{}'", name));
        };

    public:
        static core::Pointer<Element> select(const std::string& name) {
            return Element::_indexed[name];
        }
        Element() { _pParent = nullptr; }
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
            }
            else {
                auto prev = _pChildren;
                while (prev->_pNext != nullptr) {
                    prev = prev->_pNext;
                }
                prev->_pNext = child;
            }
            child->onMounted();
        }
        template <class T> bool remove(T ele) {
            core::Pointer<Element> child = ele.cast<Element>();
            bool result = false;
            if (child == _pChildren) {
                _pChildren = child->_pNext;
                result = true;
            }
            else {
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
        template<class T>
        void setState(const std::string& name, T value) {
            setStateValue(name, core::value(value));
        }
        template<class T>
        static core::Pointer<T> create(const std::map<std::string, core::Pointer<core::Value>>& props) {
            auto ele = INJECT(T).cast<Element>();
            ele->setProps(props);
            return ele.cast<T>();
        }
    };
    std::map<std::string, core::Pointer<Element>> Element::_indexed;
} // namespace lux::element
#endif