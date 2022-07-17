#ifndef _H_LUX_ELEMENT_ELEMENT_
#define _H_LUX_ELEMENT_ELEMENT_
#include "core/Object.hpp"
#include <vector>
namespace lux::element {
    class Element : public core::Object {
    private:
        static std::map<std::string, core::Pointer<Element>> _indexed;
        core::Pointer<Element> _pNext;
        core::Pointer<Element> _pChildren;
        Element* _pParent;
        std::string _szName;
    protected:
        void setName(const std::string& name) { _szName = name; }
    public:
        static core::Pointer<Element> select(const std::string& name) {
            return Element::_indexed[name];
        }
        ~Element()override {
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
        void append(core::Pointer<Element> child) {
            child->_pParent = this;
            if (_pChildren == nullptr) {
                _pChildren = child;
            }
            else {
                auto child = _pChildren;
                while (child->_pNext != nullptr) {
                    child = child->_pNext;
                }
                child->_pNext = child;
            }
            child->onMounted();
        }
        bool remove(core::Pointer<Element> child) {
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
    };
    std::map<std::string, core::Pointer<Element>> Element::_indexed;
} // namespace lux::element
#endif