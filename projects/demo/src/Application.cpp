#include "../include/Application.hpp"
#include <fmt/format.h>
using namespace Lux::Demo;
Application::Application() : m_window(nullptr) {}
Application::~Application() { m_window = nullptr; }
int Application::Initialize(int argc, char **argv) {
  auto error = Runtime::Application::Initialize(argc, argv);
  if (error != 0) {
    return error;
  }
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fmt::print("failed to init SDL,error is {}", SDL_GetError());
    return -1;
  }
  m_window = SDL_CreateWindow("LuxDemo", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1024, 768,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
  if (!m_window) {
    fmt::print("failed to init window,error is {}", SDL_GetError());
    return -2;
  }
  return 0;
}
void Application::Tick() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      m_isRunning = false;
    }
  }
  SDL_GL_SwapWindow(m_window);
  Runtime::Application::Tick();
}
void Application::Finalize() {
  SDL_Quit();
  Runtime::Application::Finalize();
}