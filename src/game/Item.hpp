//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_GAME_ITEM_
#define _H_LUX_GAME_ITEM_

#include "Object.hpp"

namespace lux::game {
    class Item : public Object {
    public:
        DEFINE_TOKEN(lux::game::Item);
    };
}
#endif //_H_LUX_GAME_ITEM_
