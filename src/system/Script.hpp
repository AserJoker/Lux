#ifndef _H_LUX_SYSTEM_SCRIPT_
#define _H_LUX_SYSTEM_SCRIPT_

#include "event/RenderEvent.hpp"
#include "fmt/format.h"
#include "interface/IGraphic.hpp"
#include "interface/IResource.hpp"
#include "interface/IScript.hpp"
#include <lua.hpp>

#include "core/Defer.hpp"
#include "graphic/Sprite.hpp"
#include "util.hpp"

namespace lux::system {
class Script : public IScript,
               public core::Dependence<system::IGraphic, system::IResource> {
private:
  lua_State *_pState;

public:
  Script() : _pState(nullptr) { _pState = luaL_newstate(); };
  ~Script() override { lua_close(_pState); }
};
} // namespace lux::system

#endif