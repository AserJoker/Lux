//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_GAME_OBJECT_
#define _H_LUX_GAME_OBJECT_

#include "core/Object.hpp"
#include <any>

namespace lux::game {
    class Object : public core::Object {
    private:
        std::map<std::string, std::any> _meta;
    public:
        std::any &meta(const std::string &key) {
            return _meta[key];
        }
    };
}
#endif //_H_LUX_GAME_OBJECT_
