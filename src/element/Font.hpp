#ifndef _H_LUX_ELEMENT_FONT_ELEMENT_
#define _H_LUX_ELEMENT_FONT_ELEMENT_
#include "Element.hpp"
#include "resource/Font.hpp"
namespace lux::element {
  class Font : public Element {
  private:
    core::Pointer<resource::Font> _pFont;
  protected:
    void setProps(Props props) override {
      auto asset = props["asset"];
      auto size = props["size"];
      if (size.empty()|| asset.empty()) {
        throw RUNTIME_ERROR("Invalid property");
      }
      _pFont = resource::Font::create(asset.c_str(), std::stoi(size));
      provide("$font", _pFont);
      Element::setProps(props);
    }
  public:
    DEFINE_TOKEN(lux::element::Font);
  };
} // namespace lux::element

#endif