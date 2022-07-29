#ifndef _H_CORE_VALUE_
#define _H_CORE_VALUE_

#include "Object.hpp"
#include "util.hpp"
#include "Container.hpp"

namespace lux::core {
    class Value : public Object {
    };

    template<class T>
    class RefValue : public Value {
    private:
        T _value{};

    public:
        DEFINE_TOKEN(lux::core::RefValue);

        void setValue(T val) { _value = val; }

        T &getValue() { return _value; }

    };

    template<class T>
    core::Pointer<Value> value(T val) {
        core::Container::provide<RefValue<T>>(RefValue<T>::TOKEN, Container::PROTOTYPE);
        auto ref = INJECT(RefValue<T>);
        ref->setValue(val);
        return ref.template cast<Value>();
    }

    template<>
    core::Pointer<Value> value<const char *>(const char *val) {
        return value(std::string(val));
    }
} // namespace lux::core

#endif