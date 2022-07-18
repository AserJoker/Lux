#ifndef _H_LUX_ELEMENT_TEXT_ELEMENT_
#define _H_LUX_ELEMENT_TEXT_ELEMENT_
#include "SpriteElement.hpp"
namespace lux::element {
  class TextElement : public SpriteElement {
  private:
    SDL_Color _color;
    std::string _text;
  protected:
    void setProps(Props props) override {
      auto text = props["text"];
      auto color = props["color"];
      if (text == nullptr || text->getClassName() != core::String::TOKEN) {
        throw RUNTIME_ERROR("Invalid text property");
      }
      if (color == nullptr || color->getClassName() != core::Integer::TOKEN) {
        throw RUNTIME_ERROR("Invalid color property");
      }
      Uint32 uColor = (Uint32)color.cast<core::Integer>()->getValue();
      Uint8 r = uColor & 0xff;
      Uint8 g = uColor >> 8 & 0xff;
      Uint8 b = uColor >> 16 & 0xff;
      Uint8 a = uColor >> 24 & 0xff;
      _color = {r, g, b, a};
      _text = text.cast<core::String>()->getValue();

      Element::setProps(props);
    }
  public:
    DEFINE_TOKEN(lux::element::TextElement);
    void onMounted() override {
      auto font = resource::Font::create("font::demo", 32);
      if (font == nullptr) {
        throw RUNTIME_ERROR("Could not get font");
      }
      auto img = font->createImage("hello world", _color);
      auto sur = img->getSurface();
      auto graphic = INJECT(system::IGraphic);
      _pTexture = SDL_CreateTextureFromSurface(graphic->getRenderer(), sur);
      _nWidth = sur->w;
      _nHeight = sur->h;
      _srcRect = {0,0,_nWidth,_nHeight};
      _dstRect = {0,0,_nWidth,_nHeight};
      _ptCenter = {_nWidth / 2,_nHeight / 2};
    }
  };
} // namespace lux::element

#endif