#pragma once
#include "../include/define.hpp"
namespace Lux::Core {
interface IModule {
public:
  virtual int Initialize() = 0;
  virtual void Finalize() = 0;
  virtual void Tick() = 0;
};
} // namespace Lux::Core