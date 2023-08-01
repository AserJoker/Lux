#pragma once
#include "core/include/define.hpp"
#include "core/interface/IModule.hpp"
#include <string>
namespace Lux::Core {
interface IApplication {
public:
  virtual void initialize(int argc, char *argv[]) = 0;
  virtual void finalize() = 0;
  virtual bool isRunning() = 0;
  virtual void tick() = 0;
  virtual std::string &config(const std::string &config) = 0;

public:
  static constexpr auto CONFIG_NAME_CORE_WINDOW_TITLE = "core.window.title";
  static constexpr auto CONFIG_NAME_CORE_WINDOW_SIZE = "core.window.size";
};
} // namespace Lux::Core
namespace Lux {
extern Core::IApplication *g_theApp;
}