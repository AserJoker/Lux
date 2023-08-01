#include "../include/Application.hpp"
#include "util/include/Size.hpp"
#include "util/include/Strings.hpp"
#include "util/include/Version.hpp"
#include <fmt/format.h>
#include <stdexcept>
using namespace Lux::Core;

Application::Application() : m_isRunning(false) {}
Application::~Application() {}
void Application::initialize(int argc, char **argv) {
  for (int index = 0; index < argc; index++) {
    m_args.emplace_back(argv[index]);
  }
  setupConfig();
  setupSystem();

  for (auto &module : m_modules) {
    module->preInitialize();
  }
  createWindowAndContext();
  for (auto &module : m_modules) {
    module->initialize();
  }
  for (auto &module : m_modules) {
    module->postInitialize();
  }
  m_isRunning = true;
}
void Application::tick() {
  processEvent();
  for (auto &module : m_modules) {
    module->tick();
  }
}
bool Application::isRunning() { return m_isRunning; }
void Application::finalize() {
  for (auto it = m_modules.rbegin(); it != m_modules.rend(); it++) {
    (*it)->finalize();
  }
  m_modules.clear();
  cleanupSystem();
}

void Application::registerModule(IModule *module) {
  m_modules.push_back(module);
}

std::string &Application::config(const std::string &config) {
  return m_configs[config];
}

void Application::setupConfig() {
  config(CONFIG_NAME_CORE_WINDOW_TITLE) = "Lux";
  config(CONFIG_NAME_CORE_WINDOW_SIZE) = "1024x768b";
  config(CONFIG_NAME_CORE_OPENGL_VERSION) = "4.6";
}

void Application::setupSystem() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    throw std::runtime_error(fmt::format(
        "failed to initialize SDL.\n\tcaused by {}", SDL_GetError()));
  }
}

void Application::cleanupSystem() {
  SDL_GL_DeleteContext(m_glContext);
  SDL_Quit();
}

void Application::createWindowAndContext() {
  std::string title = config(CONFIG_NAME_CORE_WINDOW_TITLE);
  Util::Size size;
  try {
    size = Util::Strings::to<Util::Size>(config(CONFIG_NAME_CORE_WINDOW_SIZE));
  } catch (std::exception &e) {
    fmt::print("failed to read window size from config, run window with "
               "default size.\n\tcaused by {}",
               e.what());
    size.width() = 1024;
    size.height() = 768;
  }

  Util::Version version;
  try {
    version = Util::Strings::to<Util::Version>(
        config(CONFIG_NAME_CORE_OPENGL_VERSION));
  } catch (std::exception &e) {
    fmt::print("failed to read opengl version from config, run opengl with "
               "default version.\n\tcaused by {}",
               e.what());
    version.major() = 4;
    version.minor() = 6;
  }

  m_window =
      SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, size.width(), size.height(),
                       SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
  if (!m_window) {
    throw std::runtime_error(
        fmt::format("failed to create window '{}'.\n\tcaused by {}", title,
                    SDL_GetError()));
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version.major());
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version.minor());
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  m_glContext = SDL_GL_CreateContext(m_window);
  if (!m_glContext) {
    throw std::runtime_error(
        fmt::format("failed to create window '{}'.\n\tcaused by {}", title,
                    SDL_GetError()));
  }
}
void Application::processEvent() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      m_isRunning = false;
    }
  }
  SDL_GL_SwapWindow(m_window);
}