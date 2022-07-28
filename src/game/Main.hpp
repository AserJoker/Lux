//
// Created by w30029682 on 2022/7/25.
//

#ifndef _H_LUX_GAME_MAIN_
#define _H_LUX_GAME_MAIN_

#include "core/Object.hpp"
#include "core/Dependence.hpp"
#include "core/EventBus.hpp"
#include "event/RenderEvent.hpp"
#include "event/SDLEvent.hpp"
#include "event/KeyEvent.hpp"
#include "event/MouseButtonEvent.hpp"
#include "graphic/TileGroup.hpp"
#include "Map.hpp"

namespace lux::game {
    class Main
            : public core::Object,
              public core::Dependence<system::Application,Map>,
              public core::EventBus::EventListener<event::RenderEvent>,
              public core::EventBus::EventListener<event::KeyEvent>,
              public core::EventBus::EventListener<event::SDLEvent>,
              public core::EventBus::EventListener<event::MouseButtonEvent> {
    public:
        DEFINE_TOKEN(lux::game::Main);

        void on(event::RenderEvent *) override {
            auto map = getDependence<Map>();
            map->render();
        }

        void on(event::KeyEvent *event) override {
            if (event->getAction() == event::KeyEvent::KEYDOWN) {
                if (event->getKey() == SDLK_a) {
                    auto camera = INJECT(system::ICamera);
                    camera->getPosition().x++;
                }
                if (event->getKey() == SDLK_d) {
                    auto camera = INJECT(system::ICamera);
                    camera->getPosition().x--;
                }
            }
        }

        void on(event::SDLEvent *event) override {
            if (event->getSDLEvent().type == SDL_QUIT) {
                auto app = getDependence<system::Application>();
                app->exit();
            }
        }
        void on(event::MouseButtonEvent *event) override{
        }
    };
}
#endif //_H_LUX_GAME_MAIN_
