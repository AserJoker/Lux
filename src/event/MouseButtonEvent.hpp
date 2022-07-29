//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_MOUSE_BUTTON_EVENT_
#define _H_LUX_MOUSE_BUTTON_EVENT_
#include "core/EventBus.hpp"
#include <SDL.h>
namespace lux::event{
class MouseButtonEvent:public core::EventBus::BaseEvent<"mouse button">{
public:
    enum ACTION{
        DOWN,UP
    };
private:
    int _nButton;
    ACTION _action;
    SDL_Point _position;
public:
    MouseButtonEvent(int nButton,ACTION action,SDL_Point pos):_nButton(nButton),_action(action), _position(pos){}
    [[nodiscard]] int getButton() const{
        return _nButton;
    }
    [[nodiscard]] ACTION getAction() const{
        return _action;
    }
    [[nodiscard]] SDL_Point getPosition() const{
        return _position;
    }
};
}
#endif //_H_LUX_MOUSE_BUTTON_EVENT_
