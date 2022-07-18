#ifndef _H_LUX_ELEMENT_TEXT_ELEMENT_
#define _H_LUX_ELEMENT_TEXT_ELEMENT_
#include "SpriteElement.hpp"
namespace lux::element {
class TextElement : public SpriteElement {
protected:

public:
  DEFINE_TOKEN(lux::element::TextElement);
};
} // namespace lux::element

#endif