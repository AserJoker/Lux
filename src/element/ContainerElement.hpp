#ifndef _H_LUX_ELEMENT_CONTAINER_ELEMENT_
#define _H_LUX_ELEMENT_CONTAINER_ELEMENT_
#include "SpriteElement.hpp"
namespace lux::element {
class ContainerElement : public SpriteElement {
protected:

public:
  DEFINE_TOKEN(lux::element::ContainerElement);
};
} // namespace lux::element

#endif