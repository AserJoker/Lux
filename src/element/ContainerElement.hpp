#ifndef _H_LUX_ELEMENT_CONTAINER_ELEMENT_
#define _H_LUX_ELEMENT_CONTAINER_ELEMENT_
#include "SpriteElement.hpp"
namespace lux::element {
  class ContainerElement : public SpriteElement {
  protected:
    void setProps(Props props) override {
      auto width = props["width"];
      auto height = props["height"];
      auto access = props["access"];
      if (access != nullptr) {
        throw RUNTIME_ERROR("ContainerElement cannot set access property");
      }
      if (width == nullptr || height == nullptr) {
        throw RUNTIME_ERROR("ContainerElement: width and height must not be nullptr");
      }
      _nWidth = width.cast<core::Integer>()->getValue();
      _nHeight = height.cast<core::Integer>()->getValue();
      _dstRect = {0,0,_nWidth, _nHeight};
      _srcRect = {0,0,_nWidth,_nHeight};
      _ptCenter = {_nWidth / 2,_nHeight / 2};
      _lfAngle = 0;
      auto graphic = INJECT(system::IGraphic);
      _pTexture = SDL_CreateTexture(graphic->getRenderer(), SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET, _nWidth, _nHeight);
      if (!_pTexture) {
        throw SDL_ERROR;
      }
      if (SDL_SetTextureBlendMode(_pTexture, SDL_BLENDMODE_BLEND) != 0) {
        throw SDL_ERROR;
      }
      Element::setProps(props);
    }
  public:
    DEFINE_TOKEN(lux::element::ContainerElement);
    void onUpdate() override {
      auto graphic = INJECT(system::IGraphic);
      SDL_SetRenderTarget(graphic->getRenderer(), _pTexture);
      Element::onUpdate();
      SDL_SetRenderTarget(graphic->getRenderer(), nullptr);
      SpriteElement::onUpdate();
    }
  };
} // namespace lux::element
#endif