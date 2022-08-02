#ifndef _H_LUX_GRAPHIC_SPRITE_
#define _H_LUX_GRAPHIC_SPRITE_

#include <algorithm>
#include <any>

#include "Image.hpp"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "core/Dependence.hpp"
#include "core/Object.hpp"
#include "resource/Image.hpp"
#include "system/interface/ICamera.hpp"
#include "system/interface/IGraphic.hpp"
#include "util.hpp"

namespace lux::graphic {
class Sprite : public Image,
               public core::Dependence<system::IGraphic, system::ICamera> {
private:
public:
  DEFINE_TOKEN(lux::graphic::Sprite);

  void render() override {
    auto graphic = getDependence<system::IGraphic>();
    auto texture = getImage()->getTexture();
    SDL_Rect dst = getDstRect();
    SDL_Rect rc = {dst.x, dst.y, dst.w, dst.h};
    if (!IsAbsolute()) {
      auto camera = getDependence<system::ICamera>();
      auto camera_pos = camera->getPosition();
      rc.x -= camera_pos.x;
      rc.y -= camera_pos.y;
    }
    if (SDL_RenderCopyEx(graphic->getRenderer(), texture, &getSrcRect(), &rc,
                         getAngle(), &getCenter(), getFlip()) < 0) {
      throw SDL_ERROR;
    }
  }

  static core::Pointer<Sprite> create(const std::string &token,
                                      core::Pointer<Sprite> raw = nullptr) {
    auto sprite = raw != nullptr ? raw : INJECT(Sprite);
    sprite->setImage(resource::Image::create(token));
    int w, h;
    sprite->getImage()->getSize(&w, &h);
    sprite->getSrcRect().w = w;
    sprite->getSrcRect().h = h;
    sprite->getDstRect().w = w;
    sprite->getDstRect().h = h;
    sprite->getCenter().x = w / 2;
    sprite->getCenter().y = h / 2;
    return sprite;
  }
  static core::Pointer<Sprite> create(int width, int height,
                                      core::Pointer<Sprite> raw = nullptr) {
    auto container = raw != nullptr ? raw : INJECT(Sprite);
    auto graphic = INJECT(system::IGraphic);
    SDL_Texture *texture =
        SDL_CreateTexture(graphic->getRenderer(), SDL_PIXELFORMAT_ARGB32,
                          SDL_TEXTUREACCESS_TARGET, width, height);
    if (!texture) {
      throw SDL_ERROR;
    }
    container->setImage(resource::Image::create(texture, width, height));
    container->getDstRect().w = width;
    container->getDstRect().h = height;
    container->getSrcRect().w = width;
    container->getSrcRect().h = height;
    container->getCenter().x = width / 2;
    container->getCenter().y = height / 2;
    return container;
  }
  static core::Pointer<Sprite> setTarget(core::Pointer<Sprite> target) {
    static core::Pointer<Sprite> current = nullptr;
    auto result = current;
    current = target;
    auto graphic = INJECT(system::IGraphic);
    if (SDL_SetRenderTarget(graphic->getRenderer(),
                            current != nullptr
                                ? current->getImage()->getTexture()
                                : nullptr) < 0) {
      throw SDL_ERROR;
    }
    return result;
  }
};
} // namespace lux::graphic

#endif