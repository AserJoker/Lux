#ifndef _H_LUX_GAME_ENTITY_POOL_
#define _H_LUX_GAME_ENTITY_POOL_
#include "core/Object.hpp"
#include "graphic/Sprite.hpp"
#include "util.hpp"
#include <list>
namespace lux::game {
class EntityPool : public core::Object {
private:
  std::list<core::Pointer<graphic::Sprite>> _list;

public:
  DEFINE_TOKEN(lux::game::EntityPool);
  void render() {
    _list.sort([](core::Pointer<graphic::Sprite> a,
                  core::Pointer<graphic::Sprite> b) -> bool {
      return a->zIndex() < b->zIndex();
    });
    for (auto &sp : _list) {
      if (sp != nullptr) {
        sp->render();
      }
    }
  }
  void insert(core::Pointer<graphic::Sprite> sp) { _list.push_back(sp); }
  void remove(core::Pointer<graphic::Sprite> sp) { _list.remove(sp); }
};
} // namespace lux::game
#endif