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
      Uint32 uColor = (Uint32)color.cast<core::RefValue<unsigned>>()->getValue();
      Uint8 a = uColor & 0xff;
      Uint8 b = uColor >> 8 & 0xff;
      Uint8 g = uColor >> 16 & 0xff;
      Uint8 r = uColor >> 24 & 0xff;
      _color = {r, g, b, a};
      _text = text.cast<core::RefValue<std::string>>()->getValue();

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
      SDL_SetTextureBlendMode(_pTexture,SDL_BLENDMODE_BLEND);
      _nWidth = sur->w;
      _nHeight = sur->h;
      _srcRect = {0,0,_nWidth,_nHeight};
      _dstRect = {0,0,_nWidth,_nHeight};
      _ptCenter = {_nWidth / 2,_nHeight / 2};
    }
  };
} // namespace lux::element

#endif