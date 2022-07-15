#ifndef _H_LUX_SYSTEM_NATIVE_
#define _H_LUX_SYSTEM_NATIVE_
#include "Application.hpp"
#include "EventBus.hpp"
#include "interface/INative.hpp"
namespace lux::system {
class Native : public INative,
               public EventBus::EventEmitter<EventBus::BaseEvent<"mainloop">>,
               public EventBus::EventEmitter<EventBus::BaseEvent<"quit">> {
private:
  SDL_Window *_pWindow;

public:
  Native() : _pWindow(nullptr) {}
  void onPreInitialize(){};
  void onInitialize() {
    _pWindow = SDL_CreateWindow("Lux Demo", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!_pWindow) {
      throw SDL_ERROR;
    }
    auto bus = INJECT(EventBus);
  };
  void onPostInitialize(){};
  void on(EventBus::BaseEvent<"mainloop"> *) override {
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){
            auto app = INJECT(Application);
            app->exit();
        }
    }
  }
  void on(EventBus::BaseEvent<"quit">  *)override{
    std::cout<<"quit"<<std::endl;
  }
};
} // namespace lux::system

#endif