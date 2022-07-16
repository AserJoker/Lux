#ifndef _H_LUX_SYSTEM_INATIVE_
#define _H_LUX_SYSTEM_INATIVE_
#include "IComponent.hpp"
#include "core/Object.hpp"
namespace lux::system {
  class INative : public IComponent {
  public:
    DEFINE_TOKEN(lux::system::INative);
  };
} // namespace lux::system

#endif