#ifndef _H_LUX_ELEMENT_IMAGE_ELEMENT_
#define _H_LUX_ELEMENT_IMAGE_ELEMENT_
#include "Element.hpp"
#include "core/Dependence.hpp"
#include "resource/Image.hpp"
#include "system/interface/IGraphic.hpp"
#include <SDL.h>
namespace lux::element {
    class ImageElement : public Element, public core::Dependence<system::IGraphic> {
    protected:
        SDL_Texture* _pTexture;
        SDL_Rect _dstRect;
        int _nWidth;
        int _nHeight;
        Uint8 _uOpacity;
        void setProps(Props props) {
            auto asset = props["asset"];
            if (asset == nullptr && asset->getClassName() != core::String::TOKEN) {
                throw RUNTIME_ERROR("prop 'asset' must be string");
            }
            auto assetToken = asset.cast<core::String>()->getValue();
            auto image = resource::Image::create(assetToken);
            auto surface = image->getSurface();
            auto graphic = getDependence<system::IGraphic>();
            _pTexture = SDL_CreateTextureFromSurface(graphic->getRenderer(), surface);
            if (!_pTexture) {
                throw SDL_ERROR;
            }
            _nWidth = surface->w;
            _nHeight = surface->h;
            _dstRect = {0, 0, _nWidth, _nHeight};
            Element::setProps(props);
        }

        void setStateValue(const std::string& name,
            core::Pointer<core::Value> value) override {
            if (name == "x") {
                if (value->getClassName() != core::Integer::TOKEN) {
                    throw RUNTIME_ERROR("state 'x' must be integer");
                }
                _dstRect.x = value.cast<core::Integer>()->getValue();
                return;
            }
            if (name == "y") {
                if (value->getClassName() != core::Integer::TOKEN) {
                    throw RUNTIME_ERROR("state 'y' must be integer");
                }
                _dstRect.y = value.cast<core::Integer>()->getValue();
                return;
            }
            if (name == "width") {
                if (value->getClassName() != core::Integer::TOKEN) {
                    throw RUNTIME_ERROR("state 'width' must be integer");
                }
                _dstRect.w = value.cast<core::Integer>()->getValue();
                return;
            }
            if (name == "height") {
                if (value->getClassName() != core::Integer::TOKEN) {
                    throw RUNTIME_ERROR("state 'height' must be integer");
                }
                _dstRect.h = value.cast<core::Integer>()->getValue();
                return;
            }
            if (name == "opacity") {
                if (value->getClassName() != core::Integer::TOKEN) {
                    throw RUNTIME_ERROR("state 'opacity' must be integer");
                }
                _uOpacity = (Uint8)value.cast<core::Integer>()->getValue();
                return;
            }
            Element::setStateValue(name, value);
        }

    public:
        DEFINE_TOKEN(lux::element::ImageElement);
        ImageElement()
            : _pTexture(nullptr), _dstRect({0, 0, 0, 0}), _nWidth(0), _nHeight(0),
            _uOpacity(255) {
        }
        ~ImageElement() override {
            if (_pTexture) {
                SDL_DestroyTexture(_pTexture);
            }
        }
        void onUpdate() override {
            auto graphic = getDependence<system::IGraphic>();
            if (_pTexture) {
                if (SDL_RenderCopy(graphic->getRenderer(), _pTexture, nullptr,
                    &_dstRect) != 0) {
                    throw SDL_ERROR;
                }
            }
        }
    };
} // namespace lux::element
#endif