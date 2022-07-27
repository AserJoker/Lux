//
// Created by w30029682 on 2022/7/25.
//

#ifndef _H_LUX_GAME_MAIN_
#define _H_LUX_GAME_MAIN_

#include "core/Object.hpp"
#include "core/Dependence.hpp"
#include "core/EventBus.hpp"
#include "event/RenderEvent.hpp"
#include "graphic/TileGroup.hpp"

namespace lux::game {
class Main : public core::Object,public core::EventBus::EventListener<event::RenderEvent>{
private:
    core::Pointer<graphic::TileGroup> _pGroup;
    int count;
    int x,y;
    public:
        DEFINE_TOKEN(lux::game::Main);
        Main(): _pGroup(nullptr),count(0),x(0),y(0){
            _pGroup = graphic::TileGroup::create(graphic::Tile::create("texture::tile::grass-ground",32,32),16,16);
            _pGroup->IsAbsolute() = false;
        }
        void on(event::RenderEvent*) override{
            count++;
            if(count%1000==0&&x<16&&y<16){
                _pGroup->setCell(x,y,1);
            }
            _pGroup->render();
        }
    };
}
#endif //_H_LUX_GAME_MAIN_
