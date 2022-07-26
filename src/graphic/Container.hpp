//
// Created by w30029682 on 2022/7/20.
//

#ifndef _H_LUX_GRAPHIC_CONTAINER_
#define _H_LUX_GRAPHIC_CONTAINER_
#include "core/Object.hpp"
#include "Sprite.hpp"
namespace lux::graphic{
class Container:public Sprite{
public:
    DEFINE_TOKEN(lux::graphic::Container);
    static core::Pointer<Container> create(int width,int height,core::Pointer<Container> raw = nullptr){
        auto container =raw!=nullptr?raw:INJECT(Container);
        auto graphic = INJECT(system::IGraphic);
        SDL_Texture *texture = SDL_CreateTexture(graphic->getRenderer(),SDL_PIXELFORMAT_ARGB32,SDL_TEXTUREACCESS_TARGET,width,height);
        if(!texture){
            throw SDL_ERROR;
        }
        container->setImage( resource::Image::create(texture,width,height));
        container->getDstRect().w = width;
        container->getDstRect().h = height;
        container->getSrcRect().w = width;
        container->getSrcRect().h = height;
        container->getCenter().x = width/2;
        container->getCenter().y = height/2;
        return container;
    }
    void begin(){
        auto graphic = INJECT(system::IGraphic);
        if(SDL_SetRenderTarget(graphic->getRenderer(),getImage()->getTexture())!=0){
            throw SDL_ERROR;
        }
    }
    void end(){
        auto graphic = INJECT(system::IGraphic);
        SDL_SetRenderTarget(graphic->getRenderer(),nullptr);
    }
};
}
#endif //_H_LUX_GRAPHIC_CONTAINER_
