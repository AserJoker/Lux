#ifndef _H_LUX_GRAPHIC_SPRITE_
#define _H_LUX_GRAPHIC_SPRITE_

#include<any>

#include "core/Object.hpp"
#include "core/Dependence.hpp"
#include "resource/Image.hpp"
#include "system/interface/IGraphic.hpp"
#include "system/interface/ICamera.hpp"
#include "Image.hpp"

namespace lux::graphic {
    class Sprite : public Image, public core::Dependence<system::IGraphic,system::ICamera> {
    public:
        DEFINE_TOKEN(lux::graphic::Sprite);

        void render() override {
            auto graphic = getDependence<system::IGraphic>();
            auto texture = getImage()->getTexture();
            SDL_Rect dst = getDstRect();
            SDL_Rect rc = {dst.x,dst.y,dst.w,dst.h};
            if(!IsAbsolute()){
                auto camera = getDependence<system::ICamera>();
                auto camera_pos = camera->getPosition();
                rc.x-=camera_pos.x;
                rc.y-=camera_pos.y;
            }
            if (SDL_RenderCopyEx(graphic->getRenderer(), texture, &getSrcRect(),&rc, getAngle(),
                                 &getCenter(), getFlip()) <
                0) {
                throw SDL_ERROR;
            }
        }

        virtual bool setField(const std::string &name, std::any value) {
            if (name == "x") {
                getDstRect().x = std::any_cast<int>(value);
                return true;
            }
            if (name == "y") {
                getDstRect().y = std::any_cast<int>(value);
                return true;
            }
            if (name == "width") {
                getDstRect().w = std::any_cast<int>(value);
                return true;
            }
            if (name == "height") {
                getDstRect().h = std::any_cast<int>(value);
                return true;
            }
            if (name == "sourceX") {
                getSrcRect().x = std::any_cast<int>(value);
                return true;
            }
            if (name == "sourceY") {
                getSrcRect().y = std::any_cast<int>(value);
                return true;
            }
            if (name == "sourceWidth") {
                getSrcRect().w = std::any_cast<int>(value);
                return true;
            }
            if (name == "sourceHeight") {
                getSrcRect().h = std::any_cast<int>(value);
                return true;
            }
            if (name == "centerX") {
                getCenter().x = std::any_cast<int>(value);
                return true;
            }
            if (name == "centerY") {
                getCenter().y = std::any_cast<int>(value);
                return true;
            }
            if (name == "angle") {
                getAngle() = std::any_cast<double>(value);
                return true;
            }
            if (name == "flip") {
                getFlip() = std::any_cast<SDL_RendererFlip>(value);
                return true;
            }
            if (name == "image") {
                setImage(resource::Image::create(std::any_cast<std::string>(value)));
                return true;
            }
            return false;
        }

        static core::Pointer<Sprite> create(const std::string &token, core::Pointer<Sprite> raw = nullptr) {
            auto sprite = raw != nullptr ? raw : INJECT(Sprite);
            sprite->setImage(resource::Image::create(token));
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