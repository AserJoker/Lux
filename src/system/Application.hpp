#ifndef _H_LUX_SYSTEM_APPLICATION_
#define _H_LUX_SYSTEM_APPLICATION_
#include "core/Object.hpp"
#include "event/MainloopEvent.hpp"
#include "core/EventBus.hpp"
#include <SDL.h>
#include <vector>
namespace lux::system {
  class Application : public core::Object {
  private:
    bool _isExit;
    core::Pointer<core::EventBus> _pEventBus;

  public:
    DEFINE_TOKEN(lux::system::Application);
    Application() : _isExit(false) {
      _pEventBus = INJECT(core::EventBus);
      if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw SDL_ERROR;
      }
    }
    ~Application() override {
      SDL_Quit();
    }
    void run() {
      try {
        while (!_isExit) {
          _pEventBus->emit(event::MainloopEvent());
        }
      }
      catch (std::exception& expr) {
        throw expr;
      }
    }
    void exit() { this->_isExit = true; }
  };
} // namespace lux::system

#endif