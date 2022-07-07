#ifndef _H_LUX_SYSTEM_NATIVE_
#define _H_LUX_SYSTEM_NATIVE_
#include <SDL.h>
#include "core/EventEmitter.hpp"
#include "Application.hpp"
namespace lux::system
{
	class Native : public core::EventEmitter
	{

	private:
		SDL_Window *_pWindow;
		SDL_Event *_pEvent;
		void onInit()
		{
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			{
				throw RUNTIME_ERROR(SDL_GetError());
			}
			_pWindow = SDL_CreateWindow("Lux Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
			if (!_pWindow)
			{
				throw RUNTIME_ERROR(SDL_GetError());
			}
			emit(EVENT_INIT);
		}
		void onLoop()
		{
			SDL_Event event;
			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					auto app = INJECT(Application);
					app->exit();
				}
				else
				{
					_pEvent = &event;
					emit(EVENT_EVENT);
					_pEvent = nullptr;
				}
			}
			emit(EVENT_LOOP);
		}
		void onQuit()
		{
			emit(EVENT_QUIT);
			SDL_DestroyWindow(_pWindow);
			_pWindow = nullptr;
			SDL_Quit();
		}

	public:
		DEFINE_TOKEN(lux::system::Native);
		constexpr static const char *EVENT_INIT = "lux::system::Native.init";
		constexpr static const char *EVENT_QUIT = "lux::system::Native.quit";
		constexpr static const char *EVENT_EVENT = "lux::system::Native.event";
		constexpr static const char *EVENT_LOOP = "lux::system::Native.loop";
		Native() : _pWindow(nullptr), _pEvent(nullptr)
		{
			auto app = INJECT(Application);
			app->addEventListener(Application::EVENT_INIT, this);
			app->addEventListener(Application::EVENT_QUIT, this);
			app->addEventListener(Application::EVENT_LOOP, this);
		}

		SDL_Event *getEvent()
		{
			return _pEvent;
		}

		SDL_Window *getWindow()
		{
			return _pWindow;
		}

	protected:
		void on(core::EventEmitter *emitter, const std::string &event) override
		{
			if (event == Application::EVENT_INIT)
			{
				onInit();
			}
			else if (event == Application::EVENT_LOOP)
			{
				onLoop();
			}
			else if (event == Application::EVENT_QUIT)
			{
				onQuit();
			}
		}
	};
}
#endif //_H_LUX_SYSTEM_NATIVE_