#ifndef _H_LUX_GAME_CHARACTOR_
#define _H_LUX_GAME_CHARACTOR_
#include "Entity.hpp"
#include "SDL_rect.h"
#include "SDL_timer.h"
#include "core/EventBus.hpp"
#include "core/Object.hpp"
#include "event/MainloopEvent.hpp"
#include "util.hpp"
#include <stdlib.h>
namespace lux::game {
class Charactor : public Entity,
                  core::EventBus::EventListener<event::MainloopEvent> {
private:
  SDL_Point _step;

public:
  DEFINE_TOKEN(lux::game::Charactor);
  static core::Pointer<Charactor>
  create(const std::string &token, core::Pointer<Charactor> raw = nullptr) {
    auto result = raw == nullptr ? INJECT(Charactor) : raw;
    Entity::create(token, result.cast<Entity>());
    auto p = result->getSprite();
    p->getSrcRect() = {0, 0, 32, 48};
    p->getDstRect() = {0, -16, 32, 48};
    return result;
  }
  SDL_Point getPosition() {
    auto rc = getSprite()->getDstRect();
    return {rc.x, rc.y + 16};
  }
  void setPosition(SDL_Point pos) {
    getSprite()->getDstRect().x = pos.x;
    getSprite()->getDstRect().y = pos.y - 16;
  }
  void setStep(SDL_Point step) {
    _step.x = step.x;
    _step.y = step.y;
  }
  void setStepX(int x) { _step.x = x; }
  void setStepY(int y) { _step.y = y; }
  void setFace(int face) { getSprite()->getSrcRect().y = face * 48; }
  void updateFace() {
    if (abs(_step.x) >= abs(_step.y)) {
      if (_step.x > 0) {
        setFace(2);
      } else {
        setFace(1);
      }
    } else {
      if (_step.y > 0) {
        setFace(0);
      } else {
        setFace(3);
      }
    }
  }
  void on(event::MainloopEvent *) override {
    static auto old = SDL_GetTicks();
    auto now = SDL_GetTicks();
    if (now - old > 10) {
      old = now;
      static int frame = 0;
      if (_step.x || _step.y) {
        auto &rc = getSprite()->getDstRect();
        rc.x += _step.x;
        rc.y += _step.y;
        updateFace();
        getSprite()->getSrcRect().x = frame / 32 * 32;
        frame += 4;
        if (frame >= 32 * 4) {
          frame = 0;
        }
      } else {
        frame = 0;
        getSprite()->getSrcRect().x = 0;
      }
    }
  }
};
} // namespace lux::game
#endif