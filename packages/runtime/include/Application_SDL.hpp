#pragma once
#include "core/include/Application.hpp"
#include <SDL2/SDL.h>
namespace Lux::Runtime {
class Application_SDL : public Core::Application {
public:
  int Initialize(int argc, char **argv) override;
  void Tick() override;
  void Finalize() override;
  Application_SDL();
  ~Application_SDL() override;

private:
  SDL_Window *m_window;
};
} // namespace Lux::Runtime