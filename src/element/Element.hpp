#ifndef _H_LUX_ELEMENT_ELEMENT_
#define _H_LUX_ELEMENT_ELEMENT_
#include "core/Object.hpp"
#include <vector>
#define CHECK_PROP(name,value,type) if(value.getType()!=PropType::type){throw new RUNTIME_ERROR(fmt::format("prop '{}' must be {}",name,#type));}
namespace lux::element {
    class Element : public core::Object {
    public:
        class PropType{
            public:
                enum TYPE{
                    STRING,NUMBER,BOOLEAN,EMPTY
                };
            private:
                std::string _value;
                TYPE _type;
            public:
                PropType():_value(""),_type(EMPTY){};
                double toNumber(){
                    return std::stod(_value);
                }
                std::string toString(){
                    return _value;
                }
                bool toBoolean(){
                    return _value=="true";
                }
                TYPE getType(){
                    return _type;
                }
                template<class T> static PropType create(T value){
                    throw RUNTIME_ERROR("unsupport props type");
                }
                template<> static PropType create<const char *>(const char * value){
                    PropType prop;
                    prop._value = value;
                    prop._type = STRING;
                    return prop;
                }
                template<> static PropType create<std::string>(std::string value){
                    PropType prop;
                    prop._value = value;
                    prop._type = STRING;
                    return prop;
                }
                template<> static PropType create<double>(double value){
                    PropType prop;
                    prop._value = fmt::format("{}",value);
                    prop._type = NUMBER;
                    return prop;
                }
                template<> static PropType create<bool>(bool value){
                    PropType prop;
                    prop._value = value?"true":"false";
                    prop._type = BOOLEAN;
                    return prop;
                }
                static PropType create(){
                    PropType prop;
                    return prop;
                }
        };
    private:
        static std::map<std::string, core::Pointer<Element>> _indexed;
        core::Pointer<Element> _pNext;
        core::Pointer<Element> _pChildren;
        Element* _pParent;
        std::string _szName;
        void setName(const std::string& name) {
            if (!_szName.empty()) {
                throw RUNTIME_ERROR("cannot reset element name");
            }
            if (name.empty()) {
                throw RUNTIME_ERROR("element name must not be empty");
            }
            _szName = name;
            Element::_indexed.insert(std::make_pair(name, this));
        }
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
        template<class T>
        void append(T ele) {
            core::Pointer<Element> child = ele.cast<Element>();
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
        template<class T>
        bool remove(T ele) {
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
        virtual void setProp(const std::string& name,PropType value,const std::map<std::string,PropType>& props){
            if(name=="name"){
                CHECK_PROP(name,value,STRING);
                setName(value.toString());
                return;
            }
            throw RUNTIME_ERROR(fmt::format("unknown prop name: {}",name));
        }
    };
    std::map<std::string, core::Pointer<Element>> Element::_indexed;
} // namespace lux::element
#endif