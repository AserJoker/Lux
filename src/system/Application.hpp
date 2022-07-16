#ifndef _H_LUX_SYSTEM_APPLICATION_
#define _H_LUX_SYSTEM_APPLICATION_
#include "./interface/IComponent.hpp"
#include "EventBus.hpp"
#include "core/Object.hpp"
#include <SDL.h>
#include <vector>
namespace lux::system {
  class Application : public core::Object {
  private:
    bool _isExit;
    std::vector<core::Pointer<IComponent>> _components;
    void onPreInitialize() {
      for (auto& comp : _components) {
        comp->onPreInitialize();
      }
    }
    void onInitialize() {
      for (auto& comp : _components) {
        comp->onInitialize();
      }
    }
    void onPostInitialize() {
      for (auto& comp : _components) {
        comp->onPostInitialize();
      }
    }

  public:
    DEFINE_TOKEN(lux::system::Application);
    Application() : _isExit(false) {
      if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw SDL_ERROR;
      }
    }
    ~Application() override {
      auto event = EventBus::getEventBus();
      EventBus::BaseEvent<"quit"> e;
      event->emit(&e);
      SDL_Quit();
    }
    void run() {
      auto event = EventBus::getEventBus();
      try {
        onPreInitialize();
        onInitialize();
        onPostInitialize();
        while (!_isExit) {
          EventBus::BaseEvent<"mainloop"> e;
          event->emit(&e);
        }
      }
      catch (std::exception& expr) {
        throw expr;
      }
    }
    void exit() { this->_isExit = true; }
    template <class T> void install() {
      auto comp = INJECT(T).cast<IComponent>();
      _components.push_back(comp);
    }
  };
} // namespace lux::system

#endif