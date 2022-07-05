#ifndef _H_LUX_SCRIPT_SIMPLE_VALUE_
#define _H_LUX_SCRIPT_SIMPLE_VALUE_
#include<string>
#include<duktape.h>
#include"Value.hpp"
namespace lux::script {
    template<typename T, Value::TYPE type>
    class SimpleValue :public Value {
    private:
        T _value{};
    public:
        SimpleValue() {
            setType(type);
        }
        T getValue() {
            return _value;
        }
        void setValue(T value) {
            _value = value;
        }
    };
    using Number = SimpleValue<double, Value::NUMBER>;
    using String = SimpleValue<std::string, Value::STRING>;
    using Boolean = SimpleValue<bool, Value::BOOLEAN>;
    using Function = SimpleValue<duk_c_function, Value::FUNCTION>;
} // namespace lux::script

#endif //_H_LUX_SCRIPT_SIMPLE_VALUE_