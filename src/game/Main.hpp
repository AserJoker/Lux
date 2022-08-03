//
// Created by w30029682 on 2022/7/25.
//

#ifndef _H_LUX_GAME_MAIN_
#define _H_LUX_GAME_MAIN_

#include "Background.hpp"
#include "Charactor.hpp"
#include "Entity.hpp"
#include "EntityPool.hpp"
#include "Map.hpp"
#include "core/Container.hpp"
#include "core/Dependence.hpp"
#include "core/EventBus.hpp"
#include "core/Object.hpp"
#include "event/KeyEvent.hpp"
#include "event/MainloopEvent.hpp"
#include "event/MouseButtonEvent.hpp"
#include "event/RenderEvent.hpp"
#include "event/SDLEvent.hpp"
#include "graphic/Sprite.hpp"
#include "graphic/TileGroup.hpp"
#include "resource/Font.hpp"
#include "system/Graphic.hpp"
#include "system/interface/IGraphic.hpp"

namespace lux::game {
class Main
    : public core::Object,
      public core::Dependence<system::Application, Background, Map, EntityPool>,
      public core::EventBus::EventListener<event::RenderEvent>,
      public core::EventBus::EventListener<event::KeyEvent>,
      public core::EventBus::EventListener<event::SDLEvent>,
      public core::EventBus::EventListener<event::MouseButtonEvent>,
      public core::EventBus::EventListener<event::MainloopEvent> {
private:
  core::Pointer<Entity> _pEntity;
  core::Pointer<graphic::Sprite> _pText;

public:
  DEFINE_TOKEN(lux::game::Main);
  Main() : _pEntity(nullptr) {
    auto bg = getDependence<Background>();
    PROVIDE_PROTOTYPE(Entity);
    PROVIDE_PROTOTYPE(Charactor);
    _pEntity = Charactor::create("player").cast<Entity>();
  }

  void on(event::RenderEvent *) override {
    getDependence<Background>()->render();
    getDependence<EntityPool>()->render();
    auto c = _pEntity.cast<Charactor>();
    _pText = graphic::Sprite::create(
        resource::Font::create("font::demo", 32),
        fmt::format("x:{},y:{}", c->getPosition().x, c->getPosition().y)
            .c_str(),
        255, 255, 255, 255);
    _pText->render();
  }
  void on(event::MainloopEvent *) override {
    static int count = 0;
    if (count % 100 == 0) {
      getDependence<Background>()->move(1, 0);
    }
    count++;
  }

  void on(event::KeyEvent *event) override {
    auto charactor = _pEntity.cast<Charactor>();
    if (event->getKey() == SDLK_a) {
      if (event->getAction() == event::KeyEvent::KEYDOWN) {
        charactor->getStep().x = -1;
      } else {
        charactor->getStep().x = 0;
      }
    }
    if (event->getKey() == SDLK_d) {
      if (event->getAction() == event::KeyEvent::KEYDOWN) {
        charactor->getStep().x = 1;
      } else {
        charactor->getStep().x = 0;
      }
    }
    if (event->getKey() == SDLK_w) {
      if (event->getAction() == event::KeyEvent::KEYDOWN) {
        charactor->getStep().y = -1;
      } else {
        charactor->getStep().y = 0;
      }
    }
    if (event->getKey() == SDLK_s) {
      if (event->getAction() == event::KeyEvent::KEYDOWN) {
        charactor->getStep().y = 1;
      } else {
        charactor->getStep().y = 0;
      }
    }
  }
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
