//
// Created by w30029682 on 2022/7/28.
//

#ifndef _H_LUX_GAME_MAP_
#define _H_LUX_GAME_MAP_

#include "core/Object.hpp"
#include "graphic/TileGroup.hpp"
#include "core/EventBus.hpp"
#include "event/MainloopEvent.hpp"

namespace lux::game {
    class Map
            : public core::Object,
              public core::Dependence<system::ICamera> {
    private:
        SDL_Rect _rc;
        std::vector<core::Pointer < graphic::TileGroup>> _chunks;
    public:
        DEFINE_TOKEN(lux::game::Map);

        Map() : _rc({-2*16, -2*16, 4* 16,  4*16}), _chunks({}) {
            std::vector<core::Pointer < graphic::TileGroup>> _newChunks;
            for (int y = 0; y < _rc.h; y += 16) {
                for (int x = 0; x < _rc.w; x += 16) {
                    auto chunk = graphic::TileGroup::create(
                            graphic::Tile::create("texture::tile::grass-ground", 32, 32), 16, 16);
                    chunk->IsAbsolute() = false;
                    chunk->getDstRect().x = x * 32 + _rc.x*32;
                    chunk->getDstRect().y = y * 32 + _rc.y*32;
                    _newChunks.push_back(chunk);
                }
            }
            _chunks = _newChunks;
        }

        void render() {
            for (auto &chunk: _chunks) {
                chunk->render();
            }
        }
    };
}
#endif //_H_LUX_GAME_MAP_
