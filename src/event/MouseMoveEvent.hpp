//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_EVENT_MOUSE_MOVE_
#define _H_LUX_EVENT_MOUSE_MOVE_
#include <SDL.h>
#include "core/EventBus.hpp"
namespace lux::event{
class MouseMoveEvent:public core::EventBus::BaseEvent<"mouse move">{
private:
    SDL_Point _position;
public:
    MouseMoveEvent(SDL_Point pos): _position(pos){}
    [[nodiscard]] SDL_Point  getPosition() const{
        return _position;
    }
};
}
#endif //_H_LUX_EVENT_MOUSE_MOVE_
