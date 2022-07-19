#ifndef _H_LUX_SYSTEM_ISCRIPT_
#define _H_LUX_SYSTEM_ISCRIPT_
#include "IComponent.hpp"
namespace lux::system
{
    class IScript:public IComponent{
        public:
        DEFINE_TOKEN(lux::system::IScript);
    };    
} // namespace lux::system

#endif