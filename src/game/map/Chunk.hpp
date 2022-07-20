//
// Created by w30029682 on 2022/7/20.
//

#ifndef _LUX_GAME_MAP_CHUNK_
#define _LUX_GAME_MAP_CHUNK_

#include "core/Object.hpp"

namespace lux::game::map {
    class Chunk : public core::Object {
    private:
        int _cells[16][16]{};
        SDL_Point _position;
    public:
        DEFINE_TOKEN(lux::game::Chunk);
        Chunk():_position({0,0}){
            for(auto & _cell : _cells){
                for(int & y : _cell){
                    y = 0;
                }
            }
        }
        int getCell(int x,int y){
            return _cells[x][y];
        }
        void setCell(int x,int y,int cell){
            _cells[x][y] = cell;
        }
        SDL_Point& getPosition(){
            return _position;
        }
    };
}
#endif //_LUX_GAME_MAP_CHUNK_
