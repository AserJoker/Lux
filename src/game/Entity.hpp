//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_GAME_ENTITY_
#define _H_LUX_GAME_ENTITY_

#include "Object.hpp"

namespace lux::game {
    class Entity : public Object {
    public:
        DEFINE_TOKEN(lux::game::Entity);
    };
}
#endif //_H_LUX_GAME_ENTITY_
