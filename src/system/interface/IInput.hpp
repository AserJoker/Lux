//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_SYSTEM_IINPUT_
#define _H_LUX_SYSTEM_IINPUT_
#include "IComponent.hpp"
#include <SDL.h>
namespace lux::system{
    class IInput:public IComponent{
    public:
        DEFINE_TOKEN(lux::system::IInput);
        virtual uint32_t getKey(int key) = 0;
    };
}
#endif //_H_LUX_SYSTEM_IINPUT_
