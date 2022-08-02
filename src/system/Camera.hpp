//
// Created by w30029682 on 2022/7/27.
//

#ifndef _H_LUX_SYSTEM_CAMERA_
#define _H_LUX_SYSTEM_CAMERA_
#include "SDL_video.h"
#include "core/Dependence.hpp"
#include "interface/ICamera.hpp"
#include "interface/INative.hpp"
#include <SDL.h>

namespace lux::system {
class Camera : public ICamera, public core::Dependence<INative> {
private:
  SDL_Point _pPosition;

public:
  Camera() : _pPosition({0, 0}) {
    auto native = getDependence<INative>();
    auto window = native->getGameWindow();
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    _pPosition = {-w / 2, -h / 2};
  }
  void move(int dx, int dy) override {
    _pPosition.x += dx;
    _pPosition.y += dy;
  }
  SDL_Point &getPosition() override { return _pPosition; }
};
} // namespace lux::system
#endif //_H_LUX_SYSTEM_CAMERA_
