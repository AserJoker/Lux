#ifndef _H_LUX_RESOURCE_FONT_
#define _H_LUX_RESOURCE_FONT_
#include <SDL_ttf.h>
#include "system/Graphic.hpp"
#include "Buffer.hpp"
#include "Sprite.hpp"
namespace lux::resource {
    class Font :public core::EventEmitter {
    private:
        TTF_Font* _pFont;
        void onQuit() {
            dispose();
        }
    protected:
        void on(core::EventEmitter* emitter, const std::string& event) override {
            if (event == system::Graphic::EVENT_QUIT) {
                onQuit();
            }
        }
    public:
        DEFINE_TOKEN(lux::resource::Font);
        Font() :_pFont(nullptr) {
            auto graphic = INJECT(system::Graphic);
            graphic->addEventListener(system::Graphic::EVENT_QUIT, this);
        }
        ~Font() override {
            dispose();
        }
        void dispose() {
            if (_pFont) {
                TTF_CloseFont(_pFont);
                _pFont = 0;
            }
        }
        core::Pointer<Sprite> drawText(const char* text, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            auto graphic = INJECT(system::Graphic);
            SDL_Surface* sur = nullptr;
            SDL_Texture* tex = nullptr;
            sur = TTF_RenderUTF8_Solid(_pFont, text, {r,g,b,a});
            if (!sur) {
                throw RUNTIME_ERROR(SDL_GetError());
            }
            auto sprite = Sprite::create(sur);
            SDL_FreeSurface(sur);
            return sprite;
        }
        static core::Pointer<Font> load(core::Pointer<Buffer> buf, int size) {
            auto font = INJECT(Font);
            font->_pFont = TTF_OpenFontRW(SDL_RWFromConstMem(buf->getBufferData(), (int)buf->getBufferSize()), 0, size);
            if (!font->_pFont) {
                throw RUNTIME_ERROR(SDL_GetError());
            }
            return font;
        }
        static core::Pointer<Font> load(core::Pointer<Buffer> buf, int size, int index) {
            auto font = INJECT(Font);
            font->_pFont = TTF_OpenFontIndexRW(SDL_RWFromConstMem(buf->getBufferData(), (int)buf->getBufferSize()), 0, size, index);
            if (!font->_pFont) {
                throw RUNTIME_ERROR(SDL_GetError());
            }
            return font;
        }
    };
} // namespace lux::resource

#endif