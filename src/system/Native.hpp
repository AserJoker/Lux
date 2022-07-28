#ifndef _H_LUX_SYSTEM_NATIVE_
#define _H_LUX_SYSTEM_NATIVE_

#include "core/Dependence.hpp"
#include "core/EventBus.hpp"
#include "Application.hpp"
#include "interface/INative.hpp"
#include "event/MainloopEvent.hpp"
#include "event/SDLEvent.hpp"
#include "event/KeyEvent.hpp"

namespace lux::system {
    class Native : public INative,
                   public core::Dependence<Application,core::EventBus>,
                   public core::EventBus::EventListener<event::MainloopEvent> {
    private:
        SDL_Window *_pWindow;

    public:
        Native() : _pWindow(nullptr) {
            _pWindow = SDL_CreateWindow("Lux Demo", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, 800, 600, 0);
            if (!_pWindow) {
                throw SDL_ERROR;
            }
        }

        ~Native() override {
            if (_pWindow) {
                SDL_DestroyWindow(_pWindow);
                _pWindow = nullptr;
            }
        }

        void on(event::MainloopEvent *) override {
            SDL_Event event;
            if (SDL_PollEvent(&event)) {
                auto bus = getDependence<core::EventBus>();
                bus->emit(event::SDLEvent(event));
            }
        }

        SDL_Window *getGameWindow() override {
            return _pWindow;
        }
    };
} // namespace lux::system

#endif