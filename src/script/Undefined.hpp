#ifndef _H_LUX_SCRIPT_UNDEFINED_
#define _H_LUX_SCRIPT_UNDEFINED_
#include"Value.hpp"
namespace lux::script {
    class Undefined :public Value {
    public:
        Undefined() {
            setType(UNDEFINED);
        }
        static Undefined* singleton() {
            static Undefined value;
            return &value;
        }
    };
} // namespace lux::script

#endif //_H_LUX_SCRIPT_UNDEFINED_