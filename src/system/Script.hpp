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
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
#include "util.hpp"

namespace lux::system {
class Script : public IScript,
               public core::Dependence<system::IGraphic, system::IResource> {
private:
  lua_State *_pState;

public:
  Script() : _pState(nullptr) {
    _pState = luaL_newstate();
    luaL_openlibs(_pState);
    luaL_requiref(
        _pState, "native",
        [](lua_State *L) -> int {
          luaL_Reg l[] = {{"log",
                           [](lua_State *L) -> int {
                             auto str = lua_tostring(L, -1);
                             std::cout << str << std::endl;
                             return 0;
                           }},
                          {nullptr, nullptr}};
          luaL_checkversion(L);
          luaL_newlib(L, l);
          return 1;
        },
        0);
    luaL_dofile(_pState, "script/dist/main.lua");
  };
  ~Script() override { lua_close(_pState); }
  void exec(const std::string &file) {}
};
} // namespace lux::system

#endif