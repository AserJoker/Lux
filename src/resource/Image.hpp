#ifndef _H_LUX_RESOURCE_IMAGE_
#define _H_LUX_RESOURCE_IMAGE_
#include <SDL.h>
#include "core/Context.hpp"
#include "core/Object.hpp"
#include "system/Resource.hpp"
#include "system/interface/IGraphic.hpp"
namespace lux::resource {
    class Image :public core::Object,public core::Dependence<system::IResource,system::IGraphic,core::Context> {
    private:
        SDL_Texture* _pTexture;
        int _nWidth;
        int _nHeight;
    public:
        DEFINE_TOKEN(lux::resource::Image);
        Image() {
            _pTexture = nullptr;
            _nWidth = 0;
            _nHeight = 0;
        }
        ~Image() override {
            if(_pTexture){
                SDL_DestroyTexture(_pTexture);
            }
        }
        SDL_Texture* getTexture(){
            return _pTexture;
        }
        void getSize(int *w,int *h){
            *w = _nWidth;
            *h = _nHeight;
        }
        static core::Pointer<Image> create(const std::string& token) {
            auto ctx = INJECT(core::Context);
            using ImageCache = std::map<std::string,core::Pointer<Image>>;
            if(ctx->getContext<ImageCache>("image#cache")==nullptr){
                ctx->setContext<ImageCache>("image#cache",{});
            }
            auto cache = ctx->getContext<ImageCache>("image#cache");
            if(cache->getValue().contains(token)){
                return cache->getValue().at(token);
            }
            auto R = INJECT(system::Resource);
            auto G = INJECT(system::IGraphic);
            auto buf = R->load(token);
            auto img = INJECT(Image);
             auto sur = IMG_Load_RW(SDL_RWFromConstMem(buf->getBuffer(), (int)buf->getSize()), 0);
            if (!sur) {
                throw SDL_ERROR;
            }
            img->_nWidth = sur->w;
            img->_nHeight = sur->h;
            img->_pTexture = SDL_CreateTextureFromSurface(G->getRenderer(),sur);
            SDL_FreeSurface(sur);
            if(!img->_pTexture){
                throw SDL_ERROR;
            }
            cache->getValue().insert({token,img});
            return img;
        }
        static core::Pointer<Image> create(SDL_Surface* surface) {
            auto G = INJECT(system::IGraphic);
            if (!surface) {
                throw RUNTIME_ERROR("failed to create image");
            }
            auto img = INJECT(Image);
            img->_nWidth = surface->w;
            img->_nHeight = surface->h;
            img->_pTexture = SDL_CreateTextureFromSurface(G->getRenderer(),surface);
            return img;
        }
        static core::Pointer<Image> create(SDL_Texture* tex,int w,int h) {
            auto img = INJECT(Image);
            img->_nWidth = w;
            img->_nHeight = h;
            img->_pTexture = tex;
            return img;
        }
    };
} // namespace lux::resource

#endif