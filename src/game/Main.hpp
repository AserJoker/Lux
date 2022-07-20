//
// Created by w30029682 on 2022/7/20.
//

#ifndef _LUX_GAME_MAIN_
#define _LUX_GAME_MAIN_

#include "core/Object.hpp"
#include "core/EventBus.hpp"
#include "core/Dependence.hpp"
#include "system/Application.hpp"
#include "system/interface/IResource.hpp"
#include "system/interface/IGraphic.hpp"
#include "system/interface/INative.hpp"
#include "system/interface/IScript.hpp"
#include "event/RenderEvent.hpp"

#include "Map.hpp"

namespace lux::game {
    class Main
            : public core::Object,
              public core::EventBus::EventListener<event::RenderEvent>,
              public core::Dependence<system::Application, system::IResource, system::IGraphic, system::INative, system::IScript,Map> {
    private:
    public:
        DEFINE_TOKEN(lux::game::Main);

        Main() {
        }

        void on(event::RenderEvent*)override{
            auto map = getDependence<Map>();
            map->render();
        }
    };
}
#endif //_LUX_GAME_MAIN_
