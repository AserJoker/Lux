#ifndef _LUX_RESOURCE_FONT_
#define _LUX_RESOURCE_FONT_
#include <SDL_ttf.h>
#include "core/Object.hpp"
#include "core/Dependence.hpp"
#include "system/Resource.hpp"
#include "Image.hpp"
namespace lux::resource {
    class Font : public core::Object,public core::Dependence<system::Resource> {
    private:
        TTF_Font* _pFont;
    public:
        DEFINE_TOKEN(lux::resource::Font);
        Font() {
            _pFont = nullptr;
        }
        ~Font() override {
            if (_pFont != nullptr) {
                TTF_CloseFont(_pFont);
                _pFont = nullptr;
            }
        }
        TTF_Font* getFont() { return _pFont; }
        static core::Pointer<Font> create(const char* szToken, int nSize) {
            auto R = INJECT(system::Resource);
            auto buf = R->load(szToken);
            auto font = INJECT(Font);
            font->_pFont = TTF_OpenFontRW(SDL_RWFromConstMem(buf->getBuffer<void>(),(int)buf->getSize()), 0, nSize);
            if (!font->_pFont) {
                throw SDL_ERROR;
            }
            return font;
        }
        core::Pointer<Image> createImage(const char* szStr, SDL_Color color) {
            SDL_Surface* sur = TTF_RenderText_Solid(_pFont, szStr, color);
            if (!sur) {
                throw SDL_ERROR;
            }
            return Image::create(sur);
        }
    };
} // namespace lux::res

#endif