#ifndef _H_LUX_SYSTEM_NATIVE_
#define _H_LUX_SYSTEM_NATIVE_
#include <SDL.h>
#include "core/EventEmitter.hpp"
#include "Application.hpp"
#include "Script.hpp"
#define ADD_FUNC(obj, name) _ADD_FUNC(obj, name, Native)
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
			auto script = INJECT(Script);
			auto engine = script->getEngine();
			script::Object native;
			ADD_FUNC(native, setTitle);
			ADD_FUNC(native, getTitle);
			ADD_FUNC(native, setSize);
			ADD_FUNC(native, getSize);
			ADD_FUNC(native, setFullscreen);
			engine->setValue("native", &native);
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

	private:
		static duk_idx_t setTitle(duk_context *ctx)
		{
			CHECK_ARG_LEN(1,"setTitle need 1 argument");
			CHECK_ARG_STRING(0,"setTitle need 1 string argument");
			auto title = duk_get_string(ctx, 0);
			auto native = INJECT(Native);
			SDL_SetWindowTitle(native->_pWindow, title);
			return 0;
		}
		static duk_idx_t setSize(duk_context *ctx)
		{
			CHECK_ARG_LEN(2,"setSize need 2 argument");
			CHECK_ARG_NUMBER(0,"setSize need 2 number argument");
			CHECK_ARG_NUMBER(1,"setSize need 2 number argument");
			auto width = duk_get_int(ctx,0);
			auto height = duk_get_int(ctx,1);
			auto native = INJECT(Native);
			SDL_SetWindowSize(native->_pWindow,width,height);
			return 0;
		}
		static duk_idx_t getSize(duk_context *ctx)
		{
			int w;
			int h;
			auto native = INJECT(Native);
			SDL_GetWindowSize(native->_pWindow,&w,&h);
			auto top = duk_get_top(ctx);
			duk_push_array(ctx);
			duk_push_number(ctx,w);
			duk_put_prop_index(ctx,top,0);
			duk_push_number(ctx,h);
			duk_put_prop_index(ctx,top,1);
			return 1;
		}
		static duk_idx_t getTitle(duk_context *ctx)
		{
			auto native = INJECT(Native);
			auto title = SDL_GetWindowTitle(native->_pWindow);
			duk_push_string(ctx,title);
			return 1;
		}
		static duk_idx_t setFullscreen(duk_context *ctx)
		{
			CHECK_ARG_LEN(1,"setFullscreen need 1 argument");
			CHECK_ARG_NUMBER(0,"setFullscreen need 1 number argument");
			auto native = INJECT(Native);
			int flag = duk_get_int(ctx,0);
			if(flag<0||flag>2){
				duk_reference_error(ctx,"invalid argument flag");
			}
			if(flag==2){
				flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
			}
			SDL_SetWindowFullscreen(native->_pWindow,flag);
			return 0;
		}
	};
}
#undef ADD_FUNC
#endif //_H_LUX_SYSTEM_NATIVE_