#ifndef _H_LUX_SCRIPT_ARRAY_
#define _H_LUX_SCRIPT_ARRAY_
#include<vector>
#include"Value.hpp"
#include"Undefined.hpp"
namespace lux::script {
    class Array :public Value {
    private:
        std::vector<Value*> _data;
    public:
        size_t getLength() {
            return _data.size();
        }
        Value* get(unsigned index) {
            if (index < _data.size()) {
                return _data[index];
            }
            return Undefined::singleton();
        }
        bool set(unsigned index, Value* value) {
            if (index < _data.size()) {
                _data[index] = value;
                return true;
            }
            return false;
        }
        void append(Value* value) {
            _data.push_back(value);
        }
    };
} // namespace lux::script

#endif //_H_LUX_SCRIPT_ARRAY_