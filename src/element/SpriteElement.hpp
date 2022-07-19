#ifndef _H_LUX_ELEMENT_SPRITE_ELEMENT_
#define _H_LUX_ELEMENT_SPRITE_ELEMENT_
#include "ImageElement.hpp"
namespace lux::element {
  class SpriteElement : public ImageElement {
  protected:
    SDL_Rect _srcRect;
    SDL_Point _ptCenter;
    double _lfAngle;
    SDL_RendererFlip _rendererFlip;
    void setProps(Props props) override {
      ImageElement::setProps(props);
      _srcRect = {0,0,_nWidth,_nHeight};
      _ptCenter = {_nWidth / 2,_nHeight / 2};
    }
    void setStateValue(const std::string& name, core::Pointer<core::Value> value) override {
      if (name == "srcX") {
        auto srcX = value.cast<core::RefValue<int>>()->getValue();
        _srcRect.x = srcX;
        return;
      }
      if (name == "srcY") {
        auto srcY = value.cast<core::RefValue<int>>()->getValue();
        _srcRect.y = srcY;
        return;
      }
      if (name == "srcWidth") {
        auto srcWidth = value.cast<core::RefValue<int>>()->getValue();
        _srcRect.w = srcWidth;
        return;
      }
      if (name == "srcHeight") {
        auto srcHeight = value.cast<core::RefValue<int>>()->getValue();
        _srcRect.h = srcHeight;
        return;
      }
      if (name == "rotationX") {
        auto rotationX = value.cast<core::RefValue<int>>()->getValue();
        _ptCenter.x = rotationX;
        return;
      }
      if (name == "rotationY") {
        auto rotationY = value.cast<core::RefValue<int>>()->getValue();
        _ptCenter.y = rotationY;
        return;
      }
      if (name == "angle") {
        auto angle = value.cast<core::RefValue<int>>()->getValue();
        _lfAngle = angle;
        return;
      }
      if (name == "flip") {
        auto flip = value.cast<core::RefValue<int>>()->getValue();
        _rendererFlip = (SDL_RendererFlip)flip;
        return;
      }

      ImageElement::setStateValue(name, value);
    }
  public:
    DEFINE_TOKEN(lux::element::SpriteElement);
    SpriteElement() {
      _srcRect = {0,0,0,0};
      _ptCenter = {0,0};
      _lfAngle = 0;
      _rendererFlip = SDL_FLIP_NONE;
    }
    void onUpdate() override {
      auto graphic = getDependence<system::IGraphic>();
      if (_pTexture) {
        if (SDL_RenderCopyEx(graphic->getRenderer(), _pTexture, &_srcRect,
          &_dstRect, _lfAngle, &_ptCenter, _rendererFlip) != 0) {
          throw SDL_ERROR;
        }
      }
    }
  };
} // namespace lux::element
#endif