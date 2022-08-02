#ifndef _H_LUX_GAME_BACKGROUND_
#define _H_LUX_GAME_BACKGROUND_
#include "SDL_video.h"
#include "core/Dependence.hpp"
#include "core/EventBus.hpp"
#include "core/Object.hpp"
#include "event/MainloopEvent.hpp"
#include "graphic/Image.hpp"
#include "graphic/Sprite.hpp"
#include "system/Native.hpp"
#include "util.hpp"

namespace lux::game {
class Background : public core::Object,
                   public core::Dependence<system::Native>,
                   core::EventBus::EventListener<event::MainloopEvent> {
private:
  core::Pointer<graphic::Sprite> _pBackground;
  int _nOffsetX;
  int _nOffsetY;

public:
  DEFINE_TOKEN(lux::game::Background);
  void render() {
    if (_pBackground != nullptr) {
      auto native = getDependence<system::Native>();
      auto window = native->getGameWindow();
      int w, h;
      SDL_GetWindowSize(window, &w, &h);
      for (int y = _nOffsetY; y < h; y += _pBackground->getDstRect().h) {
        for (int x = _nOffsetX; x < w; x += _pBackground->getDstRect().w) {
          _pBackground->getDstRect().x = x;
          _pBackground->getDstRect().y = y;
          _pBackground->render();
        }
      }
    }
  }
  void on(event::MainloopEvent *) override {
    if (_pBackground == nullptr) {
      return;
    }
    if (_nOffsetX > 0) {
      _nOffsetX -= _pBackground->getDstRect().w;
    }
    if (_nOffsetY > 0) {
      _nOffsetY -= _pBackground->getDstRect().h;
    }
  }
  void move(int dx, int dy) {
    _nOffsetX += dx;
    _nOffsetY += dy;
  }
  void setImage(const std::string &token, int suit = 0) {
    _pBackground = graphic::Sprite::create(token);
    auto native = getDependence<system::Native>();
    auto window = native->getGameWindow();
    int w, h;
    int imgW, imgH;
    _pBackground->getImage()->getSize(&imgW, &imgH);
    SDL_GetWindowSize(window, &w, &h);
    if (suit) {
      if (suit == 3) {
        _pBackground->getDstRect().w = w;
        _pBackground->getDstRect().h = h;
      } else if (suit == 1) {
        float scale = w * 1.0f / imgW;
        _pBackground->getDstRect().w = w;
        _pBackground->getDstRect().h = (int)(imgH * scale);
      } else if (suit == 2) {
        float scale = h * 1.0f / imgH;
        _pBackground->getDstRect().w = (int)(imgW * scale);
        _pBackground->getDstRect().h = h;
      }
    }
  }
  Background() : _pBackground(nullptr), _nOffsetX(0), _nOffsetY(0) {}
};
} // namespace lux::game
#endif