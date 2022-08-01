#ifndef _H_LUX_GRAPHIC_SPRITE_
#define _H_LUX_GRAPHIC_SPRITE_

#include <any>

#include "Image.hpp"
#include "SDL_render.h"
#include "core/Dependence.hpp"
#include "core/Object.hpp"
#include "resource/Image.hpp"
#include "system/interface/ICamera.hpp"
#include "system/interface/IGraphic.hpp"

namespace lux::graphic {
class Sprite : public Image,
               public core::Dependence<system::IGraphic, system::ICamera> {
private:
  struct Task {
    core::Pointer<Sprite> _src;
    SDL_Rect _target;
    SDL_Rect _source;
    SDL_Point _center;
    double _angle;
    SDL_RendererFlip _flip;
  };
  std::vector<Task> _tasks;

  core::Pointer<Sprite> _stackTarget;
  static core::Pointer<Sprite> _target;

public:
  DEFINE_TOKEN(lux::graphic::Sprite);
  Sprite() : _tasks({}), _stackTarget(nullptr) {}

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
    auto target = Sprite::_target;
    if (target == nullptr) {
      if (SDL_RenderCopyEx(graphic->getRenderer(), texture, &getSrcRect(), &rc,
                           getAngle(), &getCenter(), getFlip()) < 0) {
        throw SDL_ERROR;
      }
    } else {
      auto &tasks = Sprite::_target->_tasks;
      auto src = getSrcRect();
      tasks.push_back({this,
                       {rc.x, rc.y, rc.w, rc.h},
                       {src.x, src.y, src.w, src.h},
                       {getCenter().x, getCenter().y},
                       getAngle(),
                       getFlip()});
    }
  }

  virtual bool setField(const std::string &name, std::any value) {
    if (name == "x") {
      getDstRect().x = std::any_cast<int>(value);
      return true;
    }
    if (name == "y") {
      getDstRect().y = std::any_cast<int>(value);
      return true;
    }
    if (name == "width") {
      getDstRect().w = std::any_cast<int>(value);
      return true;
    }
    if (name == "height") {
      getDstRect().h = std::any_cast<int>(value);
      return true;
    }
    if (name == "sourceX") {
      getSrcRect().x = std::any_cast<int>(value);
      return true;
    }
    if (name == "sourceY") {
      getSrcRect().y = std::any_cast<int>(value);
      return true;
    }
    if (name == "sourceWidth") {
      getSrcRect().w = std::any_cast<int>(value);
      return true;
    }
    if (name == "sourceHeight") {
      getSrcRect().h = std::any_cast<int>(value);
      return true;
    }
    if (name == "centerX") {
      getCenter().x = std::any_cast<int>(value);
      return true;
    }
    if (name == "centerY") {
      getCenter().y = std::any_cast<int>(value);
      return true;
    }
    if (name == "angle") {
      getAngle() = std::any_cast<double>(value);
      return true;
    }
    if (name == "flip") {
      getFlip() = std::any_cast<SDL_RendererFlip>(value);
      return true;
    }
    if (name == "image") {
      setImage(resource::Image::create(std::any_cast<std::string>(value)));
      return true;
    }
    return false;
  }
  void begin() {
    _stackTarget = Sprite::_target;
    Sprite::_target = this;
  }
  void end() {
    auto graphic = INJECT(system::IGraphic);
    if (SDL_SetRenderTarget(graphic->getRenderer(), getImage()->getTexture()) !=
        0) {
      throw SDL_ERROR;
    }
    for (auto &task : _tasks) {
      SDL_RenderCopyEx(graphic->getRenderer(),
                       task._src->getImage()->getTexture(), &task._source,
                       &task._target, task._angle, &task._center, task._flip);
    }
    SDL_SetRenderTarget(graphic->getRenderer(), nullptr);
    Sprite::_target = _stackTarget;
    _tasks.clear();
    _stackTarget = nullptr;
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
};
core::Pointer<Sprite> Sprite::_target = nullptr;
} // namespace lux::graphic

#endif