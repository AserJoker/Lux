#pragma once
#include "../interface/IApplication.hpp"
namespace Lux::Runtime {
class Application implements IApplication {
public:
  Application();
  virtual ~Application();
  int Initialize(int argc, char **argv) override;
  void Tick() override;
  bool isRunning() override;
  void Finalize() override;

protected:
  bool m_isRunning;
};
} // namespace Lux::Runtime