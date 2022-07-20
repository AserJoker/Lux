#ifndef _H_LUX_SYSTEM_INATIVE_
#define _H_LUX_SYSTEM_INATIVE_

#include<SDL.h>
#include "IComponent.hpp"
#include "core/Object.hpp"

namespace lux::system {
    class INative : public IComponent {
    public:
        DEFINE_TOKEN(lux::system::INative);

        virtual SDL_Window *getGameWindow() = 0;
    };
} // namespace lux::system

#endif