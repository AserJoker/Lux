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

#ifndef DELAY_STATUS
#define DELAY_STATUS 200
#endif

#ifndef DELAY_MOVE
#define DELAY_MOVE 10
#endif

#ifndef CHARACTOR_WIDTH
#define CHARACTOR_WIDTH 32
#endif

#ifndef CHARACTOR_HEIGHT
#define CHARACTOR_HEIGHT 48
#endif

#define OFFSET_BLOCK (CHARACTOR_HEIGHT - CHARACTOR_WIDTH)

#define ACTION_MOVE 0

#define FACE_SOURTH 0
#define FACE_WEST 1
#define FACE_EAST 2
#define FACE_NORTH 3

namespace lux::game {
class Charactor : public Entity,
                  core::EventBus::EventListener<event::MainloopEvent> {
private:
  SDL_Point _step;
  int _nStatus;
  int _nFace;
  int _nAction;
  void updateFace() {
    if (_step.x || _step.y) {
      if (abs(_step.x) >= abs(_step.y)) {
        if (_step.x > 0) {
          getFace() = FACE_EAST;
        } else {
          getFace() = FACE_WEST;
        }
      } else {
        if (_step.y > 0) {
          getFace() = FACE_SOURTH;
        } else {
          getFace() = FACE_NORTH;
        }
      }
    }
  }
  void updateStatus() {
    static auto old = SDL_GetTicks();
    if (_step.x || _step.y) {
      auto now = SDL_GetTicks();
      if (now - old > DELAY_STATUS) {
        _nStatus++;
        if (_nStatus >= 4) {
          _nStatus = 0;
        }
        old = now;
      }
    } else {
      old = SDL_GetTicks();
      _nStatus = 0;
    }
  }

public:
  DEFINE_TOKEN(lux::game::Charactor);
  static core::Pointer<Charactor>
  create(const std::string &token, core::Pointer<Charactor> raw = nullptr) {
    auto result = raw == nullptr ? INJECT(Charactor) : raw;
    Entity::create(token, result.cast<Entity>());
    auto p = result->getSprite();
    p->getSrcRect() = {0, 0, CHARACTOR_WIDTH, CHARACTOR_HEIGHT};
    p->getDstRect() = {0, -OFFSET_BLOCK, CHARACTOR_WIDTH, CHARACTOR_HEIGHT};
    return result;
  }
  Charactor()
      : _step({0, 0}), _nStatus(0), _nFace(FACE_SOURTH), _nAction(ACTION_MOVE) {
  }
  SDL_Point getPosition() {
    auto rc = getSprite()->getDstRect();
    return {rc.x, rc.y + OFFSET_BLOCK};
  }
  void setPosition(SDL_Point pos) {
    getSprite()->getDstRect().x = pos.x;
    getSprite()->getDstRect().y = pos.y - OFFSET_BLOCK;
  }
  SDL_Point &getStep() { return _step; }
  int &getAction() { return _nAction; }
  int &getFace() { return _nFace; }
  void move(int dx, int dy) {
    static auto old = SDL_GetTicks();
    auto now = SDL_GetTicks();
    if (now - old > DELAY_MOVE) {
      getSprite()->getDstRect().x +=
          (int)(dx * 1.0f * (now - old) / DELAY_MOVE);
      getSprite()->getDstRect().y +=
          (int)(dy * 1.0f * (now - old) / DELAY_MOVE);
      old = now;
    }
  }
  void on(event::MainloopEvent *) override {
    updateStatus();
    updateFace();
    getSprite()->getSrcRect().x = CHARACTOR_WIDTH * _nStatus;
    getSprite()->getSrcRect().y =
        CHARACTOR_HEIGHT * _nFace + _nAction * CHARACTOR_HEIGHT * 4;
    move(_step.x, _step.y);
  }
};
} // namespace lux::game
#endif