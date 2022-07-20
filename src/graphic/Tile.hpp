//
// Created by w30029682 on 2022/7/20.
//

#ifndef _H_LUX_GRAPHIC_TILE_
#define _H_LUX_GRAPHIC_TILE_

#include "Image.hpp"
#include "Sprite.hpp"

namespace lux::graphic {
    class Tile : public core::Object {
    private:
        core::Pointer<Sprite> _pImage;
        int _nTileWidth;
        int _nTileHeight;
        int _nWidthCount;
        int _nHeightCount;
    public:
        DEFINE_TOKEN(lux::graphic::Tile);
        Tile(): _pImage(nullptr),_nTileWidth(0),_nTileHeight(0),_nWidthCount(0),_nHeightCount(0){}
        void render(int index,SDL_Rect& dstRect){
            auto dx = index%_nWidthCount;
            auto dy = index/_nHeightCount;
            _pImage->getSrcRect() = {dx*_nTileWidth,dy*_nTileHeight,_nTileWidth,_nTileHeight};
            _pImage->getDstRect() = {dstRect.x,dstRect.y,dstRect.w,dstRect.h};
            _pImage->render();
        }
        int& getTileWidth(){
            return _nTileWidth;
        }
        int& getTileHeight(){
            return _nTileHeight;
        }
        static core::Pointer<Tile> create(const std::string& token,int nTileWidth,int nTileHeight){
            auto img = Sprite::create(token);
            auto tile = INJECT(Tile);
            tile->_pImage = img;
            tile->_nTileWidth = nTileWidth;
            tile->_nTileHeight = nTileHeight;
            int w,h;
            img->getImage()->getSize(&w,&h);
            tile->_nWidthCount = w/nTileWidth;
            tile->_nHeightCount = h/nTileHeight;
            return tile;
        }
    };
}
#endif //_H_LUX_GRAPHIC_TILE_
