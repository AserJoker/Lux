#ifndef _H_LUX_SYSTEM_RESOURCE_
#define _H_LUX_SYSTEM_RESOURCE_
#include <SDL_image.h>
#include "core/EventEmitter.hpp"
#include "Native.hpp"
namespace lux::system {
	class Resource :public core::EventEmitter {
	private:
		void onInit() {
			IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
		}
		void onQuit() {
			IMG_Quit();
		}
	protected:
		void on(core::EventEmitter* emitter, const std::string& event) override {
			if (event == Native::EVENT_INIT) {
				onInit();
			}
			else if (event == Native::EVENT_QUIT) {
				onQuit();
			}
		}
	public:
		DEFINE_TOKEN(lux::system::Resource);
		Resource() {
			auto native = INJECT(Native);
			native->addEventListener(Native::EVENT_INIT, this);
			native->addEventListener(Native::EVENT_QUIT, this);
		}
	};
}
#endif