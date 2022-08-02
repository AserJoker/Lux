#ifndef _H_LUX_SYSTEM_GRAPHIC_
#define _H_LUX_SYSTEM_GRAPHIC_

#include "Application.hpp"
#include "SDL_render.h"
#include "core/Dependence.hpp"
#include "event/MainloopEvent.hpp"
#include "event/RenderEvent.hpp"
#include "interface/IGraphic.hpp"
#include "interface/INative.hpp"

namespace lux::system {
class Graphic : public IGraphic,
                public core::Dependence<INative>,
                public core::EventBus::EventListener<event::MainloopEvent> {
private:
  SDL_Renderer *_pRenderer;

public:
  Graphic() {
    auto native = getDependence<INative>();
    _pRenderer = SDL_CreateRenderer(native->getGameWindow(), -1, 0);
    if (!_pRenderer) {
      throw SDL_ERROR;
    }
    SDL_SetRenderDrawBlendMode(_pRenderer, SDL_BLENDMODE_BLEND);
  }

  ~Graphic() override {
    if (_pRenderer) {
      SDL_DestroyRenderer(_pRenderer);
    }
  }

  void on(event::MainloopEvent *) override {
    SDL_RenderClear(_pRenderer);
    _pEventBus->emit(event::RenderEvent());
    SDL_RenderPresent(_pRenderer);
  }
  void clear() override { SDL_RenderClear(_pRenderer); }

  SDL_Renderer *getRenderer() override { return _pRenderer; }
};
} // namespace lux::system

#endif