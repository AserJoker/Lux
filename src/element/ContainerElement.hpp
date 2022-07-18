#ifndef _H_LUX_ELEMENT_CONTAINER_ELEMENT_
#define _H_LUX_ELEMENT_CONTAINER_ELEMENT_
#include "SpriteElement.hpp"
namespace lux::element {
class ContainerElement : public SpriteElement {
protected:
  void setProp(const std::string &name, Element::StateType value) override {
    if (name == "asset") {
      Element::setProp(name, value);
      return;
    }
    if(name=="width"){
        CHECK_PROP(name,value,NUMBER);
        _nWidth = (int)value.toNumber();
        _srcRect.w = _nWidth;
        _dstRect.w = _nWidth;
        _ptCenter.x = _nWidth/2;
        return;
    }
    if(name=="height"){
        CHECK_PROP(name,value,NUMBER);
        _nHeight = (int)value.toNumber();
        _srcRect.h = _nHeight;
        _dstRect.h = _nHeight;
        _ptCenter.y = _nHeight/2;
        return;
    }
  }

public:
  DEFINE_TOKEN(lux::element::ContainerElement);
  void onUpdate() override {
    auto graphic = getDependence<system::IGraphic>();
    if (!_pTexture) {
      _pTexture =
          SDL_CreateTexture(graphic->getRenderer(), SDL_PIXELFORMAT_ABGR32,
                            SDL_TEXTUREACCESS_TARGET, _nWidth, _nHeight);
      if (!_pTexture) {
        throw SDL_ERROR;
      }
    }
    if(SDL_SetRenderTarget(graphic->getRenderer(), _pTexture)!=0){
        throw SDL_ERROR;
    }
    SDL_RenderClear(graphic->getRenderer());
    Element::onUpdate();
    SDL_SetRenderTarget(graphic->getRenderer(), nullptr);
    SpriteElement::onUpdate();
  }
};
} // namespace lux::element

#endif