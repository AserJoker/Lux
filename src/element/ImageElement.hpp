#ifndef _H_LUX_ELEMENT_IMAGE_ELEMENT_
#define _H_LUX_ELEMENT_IMAGE_ELEMENT_
#include <SDL.h>
#include "Element.hpp"
#include "core/Dependence.hpp"
#include "resource/Image.hpp"
#include "system/interface/IGraphic.hpp"
namespace lux::element {
    class ImageElement : public Element, public core::Dependence<system::IGraphic> {
    protected:
        SDL_Texture* _pTexture;
        SDL_Rect _srcRect;
        SDL_Rect _dstRect;
        SDL_RendererFlip _rendererFlip;
        SDL_Point _ptCenter;
        double _lfAngle;
        bool _isVisible;
    public:
        DEFINE_TOKEN(lux::element::ImageElement);
        ImageElement() {
            _pTexture = nullptr;
        }
        ~ImageElement() override {
            if (_pTexture != nullptr) {
                SDL_DestroyTexture(_pTexture);
            }
        }
        void onUpdate() override {
            if (_pTexture != nullptr && _isVisible) {
                auto graphic = getDependence<system::IGraphic>();
                auto renderer = graphic->getRenderer();
                SDL_RenderCopyEx(renderer, _pTexture, &_srcRect, &_dstRect, _lfAngle, &_ptCenter, _rendererFlip);
            }
        }
        static core::Pointer<ImageElement> create(core::Pointer<system::IGraphic> pGraphic, const std::string& token) {
            auto img = resource::Image::create(token);
            auto ele = INJECT(ImageElement);
            auto surface = img->getSurface();
            ele->_pTexture = SDL_CreateTextureFromSurface(pGraphic->getRenderer(), surface);
            if (!ele->_pTexture) {
                throw SDL_ERROR;
            }
            ele->_srcRect = {0,0,surface->w,surface->h};
            ele->_dstRect = {0,0,surface->w,surface->h};
            ele->_rendererFlip = SDL_FLIP_NONE;
            ele->_isVisible = true;
            ele->_ptCenter = {surface->w / 2,surface->h / 2};
            ele->_lfAngle = 0;
            return ele;
        }
    };
} // namespace lux::element
#endif