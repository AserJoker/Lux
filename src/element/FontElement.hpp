#ifndef _H_LUX_ELEMENT_FONT_ELEMENT_
#define _H_LUX_ELEMENT_FONT_ELEMENT_
#include "Element.hpp"
#include "resource/Font.hpp"
namespace lux::element {
class FontElement : public Element {
public:
  DEFINE_TOKEN(lux::element::FontElement);

};
} // namespace lux::element

#endif