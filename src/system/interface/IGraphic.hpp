#ifndef _H_LUX_SYSTEM_IGRAPHIC_
#define _H_LUX_SYSTEM_IGRAPHIC_

#include "IComponent.hpp"
#include <SDL.h>
namespace lux::system {
class IGraphic : public IComponent {
public:
  DEFINE_TOKEN(lux::system::IGraphic);

  virtual SDL_Renderer *getRenderer() = 0;
  virtual void clear() = 0;
};
} // namespace lux::system

#endif