#ifndef _H_LUX_SCRIPT_OBJECT_
#define _H_LUX_SCRIPT_OBJECT_
#include<map>
#include<string>
#include"Value.hpp"
#include"Undefined.hpp"
namespace lux::script {
    class Object :public Value {
    private:
        std::map<std::string, Value*> _fields;
    public:
        Object() {
            setType(OBJECT);
        }
        void setField(const std::string& name, Value* value) {
            _fields[name] = value;
        }
        Value* getField(const std::string& name) {
            auto pair = _fields.find(name);
            if (pair != _fields.end()) {
                return pair->second;
            }
            return Undefined::singleton();
        }
        bool deleteField(const std::string& name) {
            auto pair = _fields.find(name);
            if (pair != _fields.end()) {
                _fields.erase(pair);
                return true;
            }
            else {
                return false;
            }
        }
        std::vector<std::string> keys() {
            std::vector<std::string> keys;
            for (auto& pair : _fields) {
                keys.push_back(pair.first);
            }
            return keys;
        }
    };
} // namespace lux::script

#endif //_H_LUX_SCRIPT_OBJECT_