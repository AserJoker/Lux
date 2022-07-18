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
        SDL_Rect _dstRect;
        bool _isVisible;
    public:
        DEFINE_TOKEN(lux::element::ImageElement);
        ImageElement() {
            _pTexture = nullptr;
            _dstRect = {0,0,0,0};
            _isVisible = false;
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
                if(SDL_RenderCopy(renderer, _pTexture, nullptr, &_dstRect)!=0){
                    throw SDL_ERROR;
                }
            }
        }
        void setProp(const std::string& name,PropType value,const std::map<std::string,PropType>& props) override{
            if(name=="asset"){
                CHECK_PROP(name,value,STRING);
                auto asset = value.toString();
                auto image = resource::Image::create(asset);
                auto surface = image->getSurface();
                auto graphic = getDependence<system::IGraphic>();
                if(_pTexture){
                    SDL_DestroyTexture(_pTexture);
                }
                _pTexture = SDL_CreateTextureFromSurface(graphic->getRenderer(),surface);
                if(!_pTexture){
                    throw SDL_ERROR;
                }
                if(!props.contains("width")){
                    _dstRect.w = surface->w;
                }
                if(!props.contains("height")){
                    _dstRect.h = surface->h;
                }
                return;
            }
            if(name=="x"){
                CHECK_PROP(name,value,NUMBER);
                _dstRect.x = (int)value.toNumber();
                return;
            }
            if(name=="y"){
                CHECK_PROP(name,value,NUMBER);
                _dstRect.y = (int)value.toNumber();
                return;
            }
            if(name=="width"){
                CHECK_PROP(name,value,NUMBER);
                _dstRect.w = (int)value.toNumber();
                return;
            }
            if(name=="height"){
                CHECK_PROP(name,value,NUMBER);
                _dstRect.h = (int)value.toNumber();
                return;
            }
            if(name=="visible"){
                CHECK_PROP(name,value,BOOLEAN);
                _isVisible = value.toBoolean();
                return;
            }
            Element::setProp(name,value,props);
        }
        static core::Pointer<ImageElement> create(core::Pointer<system::IGraphic> pGraphic, std::map<std::string,PropType> props) {
            auto ele = INJECT(ImageElement);
            for(auto& pair:props){
                ele->setProp(pair.first,pair.second,props);
            }
            return ele;
        }
    };
} // namespace lux::element
#endif