#ifndef _H_LUX_SYSTEM_NATIVE_
#define _H_LUX_SYSTEM_NATIVE_
#include "Application.hpp"
#include "EventBus.hpp"
#include "interface/INative.hpp"
#include "event/MainloopEvent.hpp"
namespace lux::system {
  class Native : public INative,
    public IComponent::Dependence<Application>,
    public EventBus::EventListener<event::MainloopEvent> {
  private:
    SDL_Window* _pWindow;

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
    void on(event::MainloopEvent*) override {
      SDL_Event event;
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          auto app = getDependence<Application>();
          app->exit();
        }
      }
    }
    SDL_Window* getGameWindow() {
      return _pWindow;
    }
  };
} // namespace lux::system

#endif