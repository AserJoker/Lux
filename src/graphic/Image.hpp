//
// Created by w30029682 on 2022/7/20.
//

#ifndef _H_LUX_GRAPHIC_IMAGE_
#define _H_LUX_GRAPHIC_IMAGE_

#include "core/Object.hpp"
#include "resource/Image.hpp"

namespace lux::graphic {
    class Image : public core::Object {
    private:
        core::Pointer <resource::Image> _pImage;
        SDL_Rect _srcRect;
        SDL_Rect _dstRect;
        SDL_Point _ptCenter;
        double _lfAngle;
        SDL_RendererFlip _flip;
        bool _blAbsolute;
    protected:
        Image() : _pImage(nullptr), _srcRect({0, 0, 0, 0}), _dstRect({0, 0, 0, 0}), _ptCenter({0, 0}), _lfAngle(0),
                  _flip(SDL_FLIP_NONE),_blAbsolute(true) {}
    public:
        core::Pointer<resource::Image> getImage(){
            return _pImage;
        }
        void setImage(const core::Pointer<resource::Image>& image){
            _pImage = image;
        }
        SDL_Rect& getSrcRect(){
            return _srcRect;
        }
        SDL_Rect& getDstRect(){
            return _dstRect;
        }
        SDL_Point& getCenter(){
            return _ptCenter;
        }
        double& getAngle(){
            return _lfAngle;
        }
        bool& IsAbsolute(){
            return _blAbsolute;
        }
        SDL_RendererFlip&  getFlip(){
            return _flip;
        }
        virtual void render() = 0;
    };
}
#endif //_H_LUX_GRAPHIC_IMAGE_
