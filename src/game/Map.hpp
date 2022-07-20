//
// Created by w30029682 on 2022/7/20.
//

#ifndef _LUX_GAME_MAP_
#define _LUX_GAME_MAP_

#include "core/Object.hpp"
#include "graphic/Tile.hpp"
#include "map/Chunk.hpp"

namespace lux::game {
    class Map : public core::Object {
    protected:
        core::Pointer<graphic::Tile> _tile;
        std::vector<core::Pointer<map::Chunk>> _chunks;
    public:
        DEFINE_TOKEN(lux::game::Map);
        Map(){
            _tile = graphic::Tile::create("texture::tile::grass-ground",32,32);
            _chunks.push_back(INJECT(map::Chunk));
            for(int x=0;x<16;x++){
                for(int y=0;y<16;y++){
                    _chunks[0]->setCell(x,y,1);
                }
            }
        }
        void setTile(const core::Pointer<graphic::Tile>& tile){
            _tile = tile;
        }

        void render() {
            for (auto &chunk: _chunks) {
                for (int x = 0; x < 16; x++) {
                    for (int y = 0; y < 16; y++) {
                        auto data = chunk->getCell(x, y);
                        SDL_Point position = chunk->getPosition();
                        SDL_Rect rc = {
                                (position.x+x) * _tile->getTileWidth(), (position.y+y) * _tile->getTileHeight(),
                                _tile->getTileWidth(), _tile->getTileWidth()
                        };
                        _tile->render(data, rc);
                    }
                }
            }
        }
    };
}
#endif //_LUX_GAME_MAP_
