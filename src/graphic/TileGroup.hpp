
#ifndef _H_LUX_GROUP_TILE_GROUP_
#define _H_LUX_GROUP_TILE_GROUP_
#include "Container.hpp"
#include "Tile.hpp"
namespace lux::graphic{
    class TileGroup:public Container{
    private:
        int *_pData;
        int **_ppData;
        core::Pointer<Tile> _pTile;
        bool _isLock;
    public:
        DEFINE_TOKEN(lux::graphic::TileGroup);
        TileGroup():_pData(nullptr),_ppData(nullptr) ,_pTile(nullptr),_isLock(false){}
        ~TileGroup() override{
            if(_pData){
                delete[] _pData;
                _pData = nullptr;
            }
        }
        bool lock(int **data){
            if(_isLock){
                return false;
            }
            *data = _pData;
            _ppData = data;
            _isLock = true;
            return true;
        }
        bool unlock(){
            if(_isLock){
                _ppData = nullptr;
                int width,height;
                int tileWidth,tileHeight;
                getImage()->getSize(&width,&height);
                tileWidth = _pTile->getTileWidth();
                tileHeight = _pTile->getTileHeight();
                int widthCount = width/tileWidth;
                int heightCount = height/tileHeight;
                begin();
                for(int y=0;y<heightCount;y++){
                    for(int x=0;x<widthCount;x++){
                        SDL_Rect rc = {x*tileWidth,y*tileHeight,tileWidth,tileHeight};
                        _pTile->render(_pData[y*widthCount+x],rc);
                    }
                }
                end();
                _isLock = false;
            }
            return false;
        }
        void setCell(int x,int y,int value){
            int width,height;
            int tileWidth,tileHeight;
            getImage()->getSize(&width,&height);
            tileWidth = _pTile->getTileWidth();
            tileHeight = _pTile->getTileHeight();
            int widthCount = width/tileWidth;
            int heightCount = height/tileHeight;
            if(x<0&&x>=widthCount){
                return;
            }
            if(y<0&&y>=heightCount){
                return;
            }
            _pData[y*widthCount+x] = value;
            begin();
            SDL_Rect rc = {x*tileWidth,y*tileHeight,tileWidth,tileHeight};
            _pTile->render(value,rc);
            end();
        }
        unsigned getCell(int x,int y){
            int width,height;
            int tileWidth,tileHeight;
            getImage()->getSize(&width,&height);
            tileWidth = _pTile->getTileWidth();
            tileHeight = _pTile->getTileHeight();
            int widthCount = width/tileWidth;
            int heightCount = height/tileHeight;
            if(x<0&&x>=widthCount){
                return -1;
            }
            if(y<0&&y>=heightCount){
                return -1;
            }
            return _pData[y*widthCount+x];
        }
        void render() override{
            if(_isLock){
                return;
            }
            Sprite::render();
        }
        static core::Pointer<TileGroup> create(core::Pointer<Tile> tile,int width,int height,const int *data = nullptr){
            auto group = INJECT(TileGroup);
            Container::create(width*tile->getTileWidth(),height*tile->getTileHeight(),group.cast<Container>());
            group->_pTile = tile;
            group->_pData = new int[width*height];
            int *buf = nullptr;
            group->lock(&buf);
            if(data){
                for(int y=0;y<height;y++){
                    for(int x=0;x<width;x++){
                        auto val = data[y*width+x];
                        buf[y*width+x] = val;
                    }
                }
            }else{
                for(int y=0;y<height;y++){
                    for(int x=0;x<width;x++){
                        buf[y*width+x] = 0;
                    }
                }
            }
            group->unlock();
            return group;
        }
    };
}
#endif //_H_LUX_GROUP_TILE_GROUP_
