#pragma once
#include "../include/define.hpp"
namespace Lux::Core {
interface IModule {
public:
  virtual void preInitialize() = 0;
  virtual void initialize() = 0;
  virtual void postInitialize() = 0;
  virtual void finalize() = 0;
  virtual void tick() = 0;
};
} // namespace Lux::Core