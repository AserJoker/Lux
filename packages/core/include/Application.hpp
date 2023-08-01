#pragma once
#include "../interface/IApplication.hpp"
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>
namespace Lux::Core {
class Application implements IApplication {
public:
  Application();
  virtual ~Application();
  void initialize(int argc, char **argv) override;
  void tick() override;
  bool isRunning() override;
  void finalize() override;
  std::string &config(const std::string &config) override;

private:
  void setupConfig();
  void setupSystem();
  void createWindowAndContext();
  void processEvent();
  void cleanupSystem();

protected:
  void registerModule(IModule *module);

  bool m_isRunning;
  std::vector<std::string> m_args;

  SDL_Window *m_window;
  SDL_GLContext m_glContext;

private:
  std::vector<IModule *> m_modules;
  std::map<std::string, std::string> m_configs;
};
} // namespace Lux::Core