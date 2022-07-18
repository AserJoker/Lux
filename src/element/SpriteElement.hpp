#ifndef _H_LUX_ELEMENT_SPRITE_ELEMENT_
#define _H_LUX_ELEMENT_SPRITE_ELEMENT_
#include "ImageElement.hpp"
namespace lux::element {
class SpriteElement : public ImageElement {
protected:
  SDL_Rect _srcRect;
  SDL_Point _ptCenter;
  double _lfAngle;
  SDL_RendererFlip _flip;
  void setProp(const std::string &name, StateType value) override {
    if (name == "asset") {
      ImageElement::setProp(name, value);
      if (_srcRect.w == -1) {
        _srcRect.w = _nWidth;
      }
      if (_srcRect.h == -1) {
        _srcRect.h = _nHeight;
      }
      if (_ptCenter.x == -1) {
        _ptCenter.x = _nWidth / 2;
      }
      if (_ptCenter.y == -1) {
        _ptCenter.y = _nHeight / 2;
      }
      return;
    }

    ImageElement::setProp(name, value);
  }

public:
  SpriteElement() {
    _srcRect = {0, 0, -1, -1};
    _ptCenter = {-1, -1};
    _lfAngle = 0;
    _flip = SDL_FLIP_NONE;
  }
  DEFINE_TOKEN(lux::element::SpriteElement);

  void onUpdate() override {
    if (_pTexture != nullptr && _isVisible) {
      auto graphic = getDependence<system::IGraphic>();
      auto renderer = graphic->getRenderer();
      if (SDL_RenderCopyEx(renderer, _pTexture, &_srcRect, &_dstRect, _lfAngle,
                           &_ptCenter, _flip) != 0) {
        throw SDL_ERROR;
      }
    }
  }
  void setState(const std::string &name, StateType value) override {
    if (name == "clipX") {
      CHECK_PROP(name, value, NUMBER);
      _srcRect.x = (int)value.toNumber();
      return;
    }
    if (name == "clipY") {
      CHECK_PROP(name, value, NUMBER);
      _srcRect.y = (int)value.toNumber();
      return;
    }
    if (name == "clipWidth") {
      CHECK_PROP(name, value, NUMBER);
      _srcRect.w = (int)value.toNumber();
      return;
    }
    if (name == "clipHeight") {
      CHECK_PROP(name, value, NUMBER);
      _srcRect.h = (int)value.toNumber();
      return;
    }
    if (name == "angle") {
      CHECK_PROP(name, value, NUMBER);
      _lfAngle = value.toNumber();
      return;
    }
    if (name == "rotationX") {
      CHECK_PROP(name, value, NUMBER);
      _ptCenter.x = (int)value.toNumber();
      return;
    }
    if (name == "rotationY") {
      CHECK_PROP(name, value, NUMBER);
      _ptCenter.y = (int)value.toNumber();
      return;
    }
    if (name == "flip") {
      CHECK_PROP(name, value, NUMBER);
      _flip = (SDL_RendererFlip)(int)value.toNumber();
      return;
    }
    ImageElement::setState(name, value);
  }
};
} // namespace lux::element
#endif