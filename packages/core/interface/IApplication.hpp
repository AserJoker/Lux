#pragma once
#include "core/include/define.hpp"
#include "core/interface/IModule.hpp"
namespace Lux::Runtime {
interface IApplication {
public:
  virtual int Initialize(int argc, char *argv[]) = 0;
  virtual void Finalize() = 0;
  virtual bool isRunning() = 0;
  virtual void Tick() = 0;
};
} // namespace Lux::Runtime
namespace Lux {
extern Runtime::IApplication *g_theApp;
}