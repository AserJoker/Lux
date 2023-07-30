#include "runtime/include/Application_SDL.hpp"
#include <fmt/format.h>
using namespace Lux::Runtime;
Application_SDL::Application_SDL() : m_window(nullptr) {}
Application_SDL::~Application_SDL() { m_window = nullptr; }
int Application_SDL::Initialize(int argc, char **argv) {
  auto error = Core::Application::Initialize(argc, argv);
  if (error != 0) {
    return error;
  }
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fmt::print("failed to initialize SDL error:{}", SDL_GetError());
    return -1;
  }
  m_window =
      SDL_CreateWindow("Lux", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
  if (!m_window) {
    fmt::print("failed to create window error:{}", SDL_GetError());
    return -2;
  }
  return 0;
}
void Application_SDL::Tick() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      m_isRunning = false;
    }
  }
}
void Application_SDL::Finalize() { SDL_Quit(); }