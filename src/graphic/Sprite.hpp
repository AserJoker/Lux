#ifndef _H_LUX_GRAPHIC_SPRITE_
#define _H_LUX_GRAPHIC_SPRITE_

#include "core/Object.hpp"
#include "core/Dependence.hpp"
#include "resource/Image.hpp"
#include "system/interface/IGraphic.hpp"
#include "Image.hpp"

namespace lux::graphic {
    class Sprite : public Image, public core::Dependence<system::IGraphic> {
    public:
        DEFINE_TOKEN(lux::graphic::Sprite);

        void render() override {
            auto graphic = getDependence<system::IGraphic>();
            auto texture = getImage()->getTexture();
            if (SDL_RenderCopyEx(graphic->getRenderer(), texture, &getSrcRect(), &getDstRect(), getAngle(), &getCenter(), getFlip()) <
                0) {
                throw SDL_ERROR;
            }
        }
        static core::Pointer<Sprite> create(const std::string& token){
            auto sprite = INJECT(Sprite);
            sprite->setImage( resource::Image::create(token));
            int w, h;
            sprite->getImage()->getSize(&w, &h);
            sprite->getSrcRect().w = w;
            sprite->getSrcRect().h = h;
            sprite->getDstRect().w = w;
            sprite->getDstRect().h = h;
            sprite->getCenter().x = w / 2;
            sprite->getCenter().y = h / 2;
            return sprite;
        }
    };
} // namespace lux::Graphic

#endif