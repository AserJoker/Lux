#ifndef _H_LUX_GAME_ENTITY_
#define _H_LUX_GAME_ENTITY_
#include "EntityPool.hpp"
#include "core/Dependence.hpp"
#include "core/Object.hpp"
#include "graphic/Sprite.hpp"
#include "util.hpp"

namespace lux::game {
class Entity : public core::Object {
private:
  core::Pointer<graphic::Sprite> _pSprite;

protected:
  core::Pointer<EntityPool> _pPool;

public:
  DEFINE_TOKEN(lux::game::Entity);
  Entity() : _pSprite(nullptr), _pPool(INJECT(EntityPool)) {}
  void setTexture(const std::string &token) {
    if (_pSprite != nullptr) {
      _pPool->remove(_pSprite);
    }
    _pSprite = graphic::Sprite::create(token);
    _pPool->insert(_pSprite);
  }
  ~Entity() override {
    if (_pSprite != nullptr) {
      // auto pool = INJECT(EntityPool);
      _pPool->remove(_pSprite);
    }
  }
  core::Pointer<graphic::Sprite> getSprite() { return _pSprite; }
  static core::Pointer<Entity> create(const std::string &token,
                                      core::Pointer<Entity> raw = nullptr) {
    auto result = raw == nullptr ? INJECT(Entity) : raw;
    if (result->_pSprite != nullptr) {
      result->_pPool->remove(result->_pSprite);
    }
    result->_pSprite = graphic::Sprite::create(token);
    result->_pPool->insert(result->_pSprite);
    result->_pSprite->IsAbsolute() = false;
    return result;
  }
};

} // namespace lux::game
#endif