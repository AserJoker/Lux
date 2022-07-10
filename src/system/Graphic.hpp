#ifndef _H_LUX_SYSTEM_GRAPHIC_
#define _H_LUX_SYSTEM_GRAPHIC_
#include<SDL_ttf.h>
#include <map>
#include "core/EventEmitter.hpp"
#include "Native.hpp"
namespace lux::system {
	class Graphic : public core::EventEmitter {
	private:
		std::map<std::string, TTF_Font*> _fonts;
		SDL_Renderer* _pRenderer;
		Uint64 _delay = 0;
		void onInit(Native* native) {
			auto window = native->getWindow();
			_pRenderer = SDL_CreateRenderer(window, -1, 0);
			if (!_pRenderer) {
				throw RUNTIME_ERROR(SDL_GetError());
			}
			SDL_SetRenderDrawColor(_pRenderer, 51, 76, 76, 255);
			SDL_SetRenderDrawBlendMode(_pRenderer, SDL_BLENDMODE_BLEND);
			emit(EVENT_INIT);
		}
		void onLoop() {
			static Uint64 last = SDL_GetTicks64();
			auto now = SDL_GetTicks64();
			if (now - last >= _delay) {
				SDL_RenderClear(_pRenderer);
				emit(EVENT_LOOP);
				last = now;
			}
			SDL_RenderPresent(_pRenderer);
		}
		void onQuit() {
			emit(EVENT_QUIT);
			SDL_DestroyRenderer(_pRenderer);
			_pRenderer = nullptr;
		}

	protected:
		void on(core::EventEmitter* emitter, const std::string& event) {
			if (event == Native::EVENT_INIT) {
				onInit((Native*)emitter);
			}
			else if (event == Native::EVENT_LOOP) {
				onLoop();
			}
			else if (event == Native::EVENT_QUIT) {
				onQuit();
			}
		}

	public:
		DEFINE_TOKEN(lux::system::Graphic);
		constexpr static const char* EVENT_INIT = "lux::system::Graphic.init";
		constexpr static const char* EVENT_LOOP = "lux::system::Graphic.loop";
		constexpr static const char* EVENT_QUIT = "lux::system::Graphic.quit";
		Graphic() : _pRenderer(nullptr) {
			auto native = INJECT(Native);
			native->addEventListener(Native::EVENT_INIT, this);
			native->addEventListener(Native::EVENT_LOOP, this);
			native->addEventListener(Native::EVENT_QUIT, this);
			setFPS(60);
		}
		SDL_Renderer* getRenderer() {
			return _pRenderer;
		}
		void setFPS(Uint64 fps) {
			_delay = 1000 / fps;
		}
		Uint64 getFPS() {
			return 1000 / _delay;
		}
	};
}
#endif //_H_LUX_SYSTEM_GRAPHIC_
