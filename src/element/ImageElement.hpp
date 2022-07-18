#ifndef _H_LUX_ELEMENT_IMAGE_ELEMENT_
#define _H_LUX_ELEMENT_IMAGE_ELEMENT_
#include "Element.hpp"
#include "core/Dependence.hpp"
#include "resource/Image.hpp"
#include "system/interface/IGraphic.hpp"
#include <SDL.h>
namespace lux::element {
class ImageElement : public Element, public core::Dependence<system::IGraphic> {
protected:
  SDL_Texture *_pTexture;
  SDL_Rect _dstRect;
  int _nWidth;
  int _nHeight;
  bool _isVisible;
  void setProp(const std::string &name, StateType value) override {
    if (name == "asset") {
      CHECK_PROP(name, value, STRING);
      auto asset = value.toString();
      auto image = resource::Image::create(asset);
      auto surface = image->getSurface();
      auto graphic = getDependence<system::IGraphic>();
      _pTexture = SDL_CreateTextureFromSurface(graphic->getRenderer(), surface);
      if (!_pTexture) {
        throw SDL_ERROR;
      }
      _nWidth = surface->w;
      _nHeight = surface->h;
      _dstRect = {0,0,_nWidth,_nHeight};
      return;
    }
    Element::setProp(name, value);
  }

public:
  DEFINE_TOKEN(lux::element::ImageElement);
  ImageElement() {
    _pTexture = nullptr;
    _dstRect = {0, 0, -1, -1};
    _isVisible = false;
    _nWidth = 0;
    _nHeight = 0;
  }
  ~ImageElement() override {
    if (_pTexture != nullptr) {
      SDL_DestroyTexture(_pTexture);
    }
  }
  void onUpdate() override {
    if (_pTexture != nullptr && _isVisible) {
      auto graphic = getDependence<system::IGraphic>();
      auto renderer = graphic->getRenderer();
      if (SDL_RenderCopy(renderer, _pTexture, nullptr, &_dstRect) != 0) {
        throw SDL_ERROR;
      }
    }
  }
  void setState(const std::string &name, StateType value) override {
    if (name == "x") {
      CHECK_PROP(name, value, NUMBER);
      _dstRect.x = (int)value.toNumber();
      return;
    }
    if (name == "y") {
      CHECK_PROP(name, value, NUMBER);
      _dstRect.y = (int)value.toNumber();
      return;
    }
    if (name == "width") {
      CHECK_PROP(name, value, NUMBER);
      _dstRect.w = (int)value.toNumber();
      return;
    }
    if (name == "height") {
      CHECK_PROP(name, value, NUMBER);
      _dstRect.h = (int)value.toNumber();
      return;
    }
    if (name == "visible") {
      CHECK_PROP(name, value, BOOLEAN);
      _isVisible = value.toBoolean();
      return;
    }
    Element::setState(name, value);
  }
};
} // namespace lux::element
#endif