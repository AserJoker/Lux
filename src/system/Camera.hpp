//
// Created by w30029682 on 2022/7/27.
//

#ifndef _H_LUX_SYSTEM_CAMERA_
#define _H_LUX_SYSTEM_CAMERA_
#include<SDL.h>
#include "interface/ICamera.hpp"

namespace lux::system{
    class Camera:public ICamera{
    private:
        SDL_Point _pPosition;
    public:
        Camera(): _pPosition({0,0}){}
        void move(int dx,int dy) override{
            _pPosition.x+=dx;
            _pPosition.y+=dy;
        }
        SDL_Point& getPosition() override {
            return _pPosition;
        }
    };
}
#endif //_H_LUX_SYSTEM_CAMERA_
