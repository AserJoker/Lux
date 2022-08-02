//
// Created by w30029682 on 2022/7/25.
//

#ifndef _H_LUX_GAME_MAIN_
#define _H_LUX_GAME_MAIN_

#include "core/Dependence.hpp"
#include "core/EventBus.hpp"
#include "core/Object.hpp"
#include "event/KeyEvent.hpp"
#include "event/MouseButtonEvent.hpp"
#include "event/RenderEvent.hpp"
#include "event/SDLEvent.hpp"
#include "graphic/Sprite.hpp"
#include "graphic/TileGroup.hpp"
#include "system/Graphic.hpp"
#include "system/interface/IGraphic.hpp"

namespace lux::game {
class Main : public core::Object,
             public core::Dependence<system::Application, system::IGraphic>,
             public core::EventBus::EventListener<event::RenderEvent>,
             public core::EventBus::EventListener<event::KeyEvent>,
             public core::EventBus::EventListener<event::SDLEvent>,
             public core::EventBus::EventListener<event::MouseButtonEvent> {
private:
  core::Pointer<graphic::Sprite> _sp;
  core::Pointer<graphic::Sprite> _sp2;

public:
  DEFINE_TOKEN(lux::game::Main);
  Main() : _sp(nullptr), _sp2(nullptr) {
    _sp = graphic::Sprite::create("player");
    _sp2 = graphic::Sprite::create("player2");
    _sp->getSrcRect().w = 32;
    _sp->getSrcRect().h = 48;
    _sp->getDstRect().w = 32;
    _sp->getDstRect().h = 48;
    _sp2->getSrcRect().w = 32;
    _sp2->getSrcRect().h = 48;
    _sp2->getDstRect().w = 32;
    _sp2->getDstRect().h = 48;
    _sp2->getDstRect().x = 32;
  }

  void on(event::RenderEvent *) override {
    _sp->render();
    _sp2->render();
  }

  void on(event::KeyEvent *event) override {}
  void on(event::MouseButtonEvent *event) override {}
  void on(event::SDLEvent *event) override {
    if (event->getSDLEvent().type == SDL_QUIT) {
      auto app = getDependence<system::Application>();
      app->exit();
    }
  }
};
} // namespace lux::game
#endif //_H_LUX_GAME_MAIN_
