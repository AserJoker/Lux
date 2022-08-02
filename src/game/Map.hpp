#ifndef _H_LUX_GAME_MAP_
#define _H_LUX_GAME_MAP_
#include "core/Object.hpp"
#include "util.hpp"
namespace lux::game {
class Map : public core::Object {
public:
  DEFINE_TOKEN(lux::game::Map);
  void render() {}
};
} // namespace lux::game
#endif