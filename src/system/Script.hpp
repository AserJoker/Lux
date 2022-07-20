#ifndef _H_LUX_SYSTEM_SCRIPT_
#define _H_LUX_SYSTEM_SCRIPT_

#include<lua.hpp>
#include "interface/IScript.hpp"
#include "interface/IGraphic.hpp"
#include "interface/IResource.hpp"
#include "event/RenderEvent.hpp"

#include "graphic/Sprite.hpp"

namespace lux::system {
    class Script
            : public IScript,
              public core::Dependence<system::IGraphic, system::IResource> {
    private:
        lua_State *_pState;
    public:
        Script() : _pState(nullptr) {
        };
    };
} // namespace lux::system

#endif