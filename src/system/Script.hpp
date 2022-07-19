#ifndef _H_LUX_SYSTEM_SCRIPT_
#define _H_LUX_SYSTEM_SCRIPT_
#include<lua.hpp>
#include "interface/IScript.hpp"
namespace lux::system
{
    class Script:public IScript{
        private:
            lua_State *_pState;
        public:
            Script():_pState(0){
            };
    };
} // namespace lux::system

#endif