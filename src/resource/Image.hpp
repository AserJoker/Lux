#ifndef _H_LUX_RESOURCE_IMAGE_
#define _H_LUX_RESOURCE_IMAGE_
#include "core/EventEmitter.hpp"
#include "system/Graphic.hpp"
#include "system/Resource.hpp"
namespace lux::resource {
	class Image :public core::EventEmitter {
	private:
		SDL_Texture* _pTexture;
		void onQuit() {
			dispose();
		}
	protected:
		void on(core::EventEmitter* emitter, const std::string& event) {
			if (event == system::Graphic::EVENT_QUIT) {
				onQuit();
			}
		}
	public:
		DEFINE_TOKEN(lux::resource::Image);
		Image():_pTexture(nullptr) {
			auto graphic = INJECT(system::Graphic);
			graphic->addEventListener(system::Graphic::EVENT_QUIT, this);
		}

		void draw(SDL_Rect* source, SDL_Rect* target) {
			if (_pTexture) {
				auto graphic = INJECT(system::Graphic);
				if (SDL_RenderCopy(graphic->getRenderer(), _pTexture, source, target) != 0) {
					throw RUNTIME_ERROR(SDL_GetError());
				}
			}
		}

		void dispose() {
			if (_pTexture) {
				SDL_DestroyTexture(_pTexture);
				_pTexture = nullptr;
			}
		}

		static core::Pointer<Image> create(int width, int height, int access = SDL_TEXTUREACCESS_STATIC) {
			auto image = INJECT(Image);
			auto graphic = INJECT(system::Graphic);
			image->_pTexture = SDL_CreateTexture(graphic->getRenderer(), SDL_PIXELFORMAT_ARGB32, access, width, height);
			if (!image->_pTexture) {
				throw RUNTIME_ERROR(SDL_GetError());
			}
			return image;
		}

		static core::Pointer<Image> create(const std::string& token){
			auto R = INJECT(system::Resource);
			auto graphic = INJECT(system::Graphic);
			try{
				auto image = INJECT(Image);
				auto buf = R->load(token);
				image->_pTexture = IMG_LoadTexture_RW(graphic->getRenderer(),SDL_RWFromConstMem(buf->getBufferData(),(int)buf->getBufferSize()),0);
				if(!image->_pTexture){
					throw RUNTIME_ERROR(SDL_GetError());
				}
				return image;
			}catch(std::exception& exp){
				std::cout<<exp.what()<<std::endl;
				return Image::create(2,2);
			}
		}
	};
}
#endif