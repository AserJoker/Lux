#pragma once
#include "core/include/Application.hpp"
#include <SDL2/SDL.h>
namespace Lux::Demo {
class Application extends Runtime::Application {
public:
  int Initialize(int argc, char **argv) override;
  void Tick() override;
  void Finalize() override;
  Application();
  virtual ~Application();

private:
  SDL_Window *m_window;
};
} // namespace Lux::Demo