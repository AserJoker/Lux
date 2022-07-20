#ifndef _H_LUX_ELEMENT_CONTAINER_ELEMENT_
#define _H_LUX_ELEMENT_CONTAINER_ELEMENT_
#include "Sprite.hpp"
namespace lux::element {
  class Container : public Sprite {
  protected:
    void setProps(Props props) override {
      auto width = props["width"];
      auto height = props["height"];
      auto access = props["access"];
      if (!access.empty()) {
        throw RUNTIME_ERROR("Container cannot set access property");
      }
      if (width.empty() || height.empty()) {
        throw RUNTIME_ERROR("Container: width and height must not be nullptr");
      }
      _nWidth = std::stoi(width);
      _nHeight = std::stoi(height);
      _dstRect = {0,0,_nWidth, _nHeight};
      _srcRect = {0,0,_nWidth,_nHeight};
      _ptCenter = {_nWidth / 2,_nHeight / 2};
      _lfAngle = 0;
      auto graphic = INJECT(system::IGraphic);
      SDL_Texture *pTexture = SDL_CreateTexture(graphic->getRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, _nWidth, _nHeight);
      if (!pTexture) {
        throw SDL_ERROR;
      }
      if (SDL_SetTextureBlendMode(pTexture, SDL_BLENDMODE_BLEND) != 0) {
        throw SDL_ERROR;
      }
      _pImage = resource::Image::create(pTexture,_nWidth,_nHeight);
      Element::setProps(props);
    }
  public:
    DEFINE_TOKEN(lux::element::Container);
    void onUpdate() override {
      auto graphic = INJECT(system::IGraphic);
      SDL_SetRenderTarget(graphic->getRenderer(), _pImage->getTexture());
      Element::onUpdate();
      SDL_SetRenderTarget(graphic->getRenderer(), nullptr);
      Sprite::onUpdate();
    }
  };
} // namespace lux::element
#endif