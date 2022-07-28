//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_EVENT_SDL_EVENT_
#define _H_LUX_EVENT_SDL_EVENT_
#include <SDL.h>
#include "core/EventBus.hpp"
namespace lux::event{
class SDLEvent:public core::EventBus::BaseEvent<"SDL">{
private:
    SDL_Event _event;
public:
    SDLEvent(SDL_Event e): _event(e){}
    SDL_Event getSDLEvent() const{
        return _event;
    }
};
}
#endif //_H_LUX_EVENT_SDL_EVENT_
