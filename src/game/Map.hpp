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
              public core::EventBus::EventListener<event::MainloopEvent>,
              public core::Dependence<system::ICamera> {
    private:
        SDL_Rect _rc;
        std::vector<core::Pointer < graphic::TileGroup>> _chunks;
    public:
        DEFINE_TOKEN(lux::game::Map);

        Map() : _rc({-4 * 16, -4 * 16, 8 * 16, 8 * 16}), _chunks({}) {
            std::vector<core::Pointer < graphic::TileGroup>> _newChunks;
            for (int y = 0; y < _rc.h; y += 16) {
                for (int x = 0; x < _rc.w; x += 16) {
                    auto chunk = graphic::TileGroup::create(
                            graphic::Tile::create("texture::tile::grass-ground", 32, 32), 16, 16);
                    chunk->getDstRect().x = x * 32 + _rc.x;
                    chunk->getDstRect().y = y * 32 + _rc.y;
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

        void on(event::MainloopEvent *) override {
            auto camera = getDependence<system::ICamera>();
            auto cx = (camera->getPosition().x - camera->getPosition().x % (32 * 16))/32;
            auto cy = (camera->getPosition().y - camera->getPosition().y % (32 * 16))/32;
            _rc.x = cx - 4 * 16;
            _rc.y = cy - 4 * 16;
        }
    };
}
#endif //_H_LUX_GAME_MAP_
