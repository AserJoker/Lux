//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_GAME_BLOCK_
#define _H_LUX_GAME_BLOCK_

#include "Object.hpp"

namespace lux::game {
    class Block : public Object {
    public:
        DEFINE_TOKEN(lux::game::Block);
    };
}
#endif //_H_LUX_GAME_BLOCK_
