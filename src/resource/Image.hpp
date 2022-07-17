#ifndef _H_LUX_RESOURCE_IMAGE_
#define _H_LUX_RESOURCE_IMAGE_
#include <SDL.h>
#include "core/Object.hpp"
#include "system/Resource.hpp"
namespace lux::resource {
    class Image :public core::Object {
    private:
        SDL_Surface* _pSurface;
    public:
        DEFINE_TOKEN(lux::resource::Image);
        Image() {
            _pSurface = nullptr;
        }
        ~Image() override {
            if (_pSurface) {
                SDL_FreeSurface(_pSurface);
            }
        }
        SDL_Surface* getSurface() {
            return _pSurface;
        }
        static core::Pointer<Image> create(const std::string& token) {
            auto R = INJECT(system::Resource);
            auto buf = R->load(token);
            auto img = INJECT(Image);
            img->_pSurface = IMG_Load_RW(SDL_RWFromConstMem(buf->getBuffer(), (int)buf->getSize()), 0);
            if (!img->_pSurface) {
                throw SDL_ERROR;
            }
            return img;
        }
        static core::Pointer<Image> create(SDL_Surface* surface) {
            if (!surface) {
                throw RUNTIME_ERROR("failed to create image");
            }
            auto img = INJECT(Image);
            img->_pSurface = surface;
            return img;
        }
    };
} // namespace lux::resource

#endif