//
// Created by w30029682 on 2022/7/27.
//

#ifndef _H_LUX_SYSTEM_ICAMERA_
#define _H_LUX_SYSTEM_ICAMERA_
#include <SDL.h>
#include "IComponent.hpp"
namespace lux::system{
    class ICamera:public IComponent{
    public:
        DEFINE_TOKEN(lux::system::ICamera);
        virtual void move(int dx,int dy) = 0;
        virtual SDL_Point& getPosition() = 0;
    };
}
#endif //_H_LUX_SYSTEM_ICAMERA_
