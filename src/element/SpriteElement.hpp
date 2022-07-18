#ifndef _H_LUX_ELEMENT_SPRITE_ELEMENT_
#define _H_LUX_ELEMENT_SPRITE_ELEMENT_
#include "ImageElement.hpp"
namespace lux::element {
class SpriteElement : public ImageElement {
protected:

public:
  DEFINE_TOKEN(lux::element::SpriteElement);

};
} // namespace lux::element
#endif