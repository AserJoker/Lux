//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_SYSTEM_INPUT_
#define _H_LUX_SYSTEM_INPUT_

#include "interface/IInput.hpp"
#include "core/Dependence.hpp"
#include "core/EventBus.hpp"
#include "event/SDLEvent.hpp"
#include "event/MainloopEvent.hpp"
#include "event/KeyEvent.hpp"
#include "event/MouseButtonEvent.hpp"
#include "event/MouseMoveEvent.hpp"

namespace lux::system {
    class Input
            : public IInput,
              public core::Dependence<core::EventBus>,
              public core::EventBus::EventListener<event::SDLEvent>,
              public core::EventBus::EventListener<event::MainloopEvent> {
    private:
        std::map<int,uint32_t> _keyboard;
    public:
        void on(event::SDLEvent *event) override {
            auto bus = getDependence<core::EventBus>();
            auto e = event->getSDLEvent();
            auto key = event->getSDLEvent().key.keysym.sym;
            auto button = event->getSDLEvent().button.button;
            if(event->getSDLEvent().type==SDL_KEYDOWN){
                if(!_keyboard.contains(key)) {
                    _keyboard.insert({key, SDL_GetTicks()});
                }
            }
            if(event->getSDLEvent().type==SDL_KEYUP){
                auto delay = SDL_GetTicks() - _keyboard[key];
                _keyboard.erase(key);
                bus->emit(event::KeyEvent(event::KeyEvent::KEYUP,key,delay));
            }
            if(event->getSDLEvent().type==SDL_MOUSEBUTTONDOWN){
                bus->emit(event::MouseButtonEvent(button,event::MouseButtonEvent::DOWN,{e.button.x,e.button.y}));
            }
            if(event->getSDLEvent().type==SDL_MOUSEBUTTONUP){
                bus->emit(event::MouseButtonEvent(button,event::MouseButtonEvent::UP,{e.button.x,e.button.y}));
            }
            if(event->getSDLEvent().type==SDL_MOUSEMOTION){
                bus->emit(event::MouseMoveEvent({e.motion.x,e.motion.y}));
            }
        }

        void on(event::MainloopEvent *) override {
            auto bus = getDependence<core::EventBus>();
            for(auto& pair:_keyboard){
                auto key = pair.first;
                auto delay = SDL_GetTicks() - pair.second;
                bus->emit(event::KeyEvent(event::KeyEvent::KEYDOWN,key,delay));
            }
        }
        uint32_t getKey(int key) override{
            return _keyboard[key];
        }
    };
}
#endif //_H_LUX_SYSTEM_INPUT_
