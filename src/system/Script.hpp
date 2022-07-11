#ifndef _H_LUX_SYSTEM_SCRIPT_
#define _H_LUX_SYSTEM_SCRIPT_
#include "Application.hpp"
#include "Resource.hpp"
#include "Graphic.hpp"
#include "Input.hpp"
#include "resource/Sprite.hpp"
#include "resource/Font.hpp"
#include "script/Engine.hpp"
#include "runtime/util.hpp"
#include "runtime/Font.hpp"
#include "runtime/Sprite.hpp"
#define _ADD_FUNC(obj, name, host) \
	script::Function name;         \
	name.setValue(host::name);     \
	obj.setField(#name, &name);
#define ADD_FUNC(obj, name) _ADD_FUNC(obj, name, Script)

#define _SET_FUNC(name,ns)           \
	func.setValue(ns::name); \
	_engine.setValue(#name, &func);
#define SET_FUNC(name) _SET_FUNC(name,Script)

namespace lux::system {
	class Script : public core::EventEmitter {
	private:


		class _Runtime {
		public:
			static duk_idx_t exists(duk_context* ctx) {
				auto path = duk_get_string(ctx, 0);
				auto isExists = std::filesystem::exists(path);
				isExists &= std::filesystem::is_regular_file(path);
				duk_push_boolean(ctx, isExists);
				return 1;
			}
			static duk_idx_t loadModule(duk_context* ctx) {
				std::string name = duk_get_string(ctx, 0);
				duk_push_undefined(ctx);
				return 1;
			}
			static duk_idx_t load(duk_context* ctx) {
				auto path = duk_get_string(ctx, 0);
				auto mod = duk_get_top(ctx);
				duk_push_object(ctx);
				duk_push_object(ctx);
				duk_put_prop_string(ctx, mod, "exports");
				duk_put_global_string(ctx, "module");
				mod = duk_get_top(ctx);
				duk_get_global_string(ctx, "module");
				duk_get_prop_string(ctx, mod, "exports");
				duk_put_global_string(ctx, "exports");
				std::ifstream file;
				file.open(path);
				std::string source;
				file >> std::noskipws;
				while (!file.eof()) {
					char c;
					file >> c;
					if (!file.eof()) {
						source += c;
					}
				}
				file.close();
				script::String __dirname;
				script::String __filename;
				auto fullpath = std::filesystem::absolute(path);
				__dirname.setValue(fullpath.parent_path().string());
				__filename.setValue(fullpath.filename().string());
				auto script = INJECT(Script);
				script->_engine.setValue("__dirname", &__dirname);
				script->_engine.setValue("__filename", &__filename);
				duk_push_string(ctx, path);
				duk_compile_string_filename(ctx, 0, source.c_str());
				if (duk_pcall(ctx, 0)) {
					script->_engine.error();
				}
				duk_get_global_string(ctx, "exports");
				return 1;
			}
		};

		static duk_idx_t asset(duk_context* ctx) {
			auto R = INJECT(Resource);
			CHECK_ARG_LEN(2);
			CHECK_ARG_STRING(0);
			CHECK_ARG_STRING(1);
			auto token = duk_get_string(ctx, 0);
			std::string type = duk_get_string(ctx, 1);
			try {
				auto buf = R->load(token);
				if (type == "string") {
					char* str = new char[buf->getBufferSize() + 1];
					str[buf->getBufferSize()] = 0;
					buf->read(str);
					duk_push_string(ctx, str);
					delete[] str;
				}
				else if (type == "buffer") {
					auto target = duk_push_buffer(ctx, buf->getBufferSize(), 0);
					buf->read(target);
				}
				else {
					duk_reference_error(ctx, "unknown resource Type");
				}
			}
			catch (std::exception& exp) {
				std::cout << exp.what() << std::endl;
				duk_push_undefined(ctx);
			}
			return 1;
		}
		static duk_idx_t println(duk_context* ctx) {
			CHECK_ARG_LEN(1);
			CHECK_ARG_STRING(0);
			auto msg = duk_get_string(ctx, 0);
			std::cout << msg << std::endl;
			return 0;
		}
		static duk_idx_t exit(duk_context* ctx) {
			auto app = INJECT(Application);
			app->exit();
			return 0;
		}

		script::Engine _engine;

		void onReady() {
			script::String __dirname;
			script::String __filename;
			auto fullpath = std::filesystem::absolute("script/main.js");
			__dirname.setValue(fullpath.parent_path().string());
			__filename.setValue(fullpath.filename().string());
			_engine.setValue("__dirname", &__dirname);
			_engine.setValue("__filename", &__filename);
			_engine.execFile("script/main.js");
		}

	protected:
		void on(core::EventEmitter* emitter, const std::string& event) {
			if (event == Application::EVENT_READY) {
				onReady();
				script::String event;
				event.setValue(Application::EVENT_READY);
				_engine.call("_on_system_event", (script::Value*)&event);
			}
			else if (event == Graphic::EVENT_LOOP) {
				script::String event;
				event.setValue(Graphic::EVENT_LOOP);
				_engine.call("_on_system_event", (script::Value*)&event);
			}
			else if(event == Input::EVENT_KEYDOWN){
				auto native = INJECT(Native);
				auto e = native->getEvent();
				script::String event;
				event.setValue(Input::EVENT_KEYDOWN);
				script::Number keycode;
				keycode.setValue(e->key.keysym.scancode);
				_engine.call("_on_system_event", (script::Value*)&event,(script::Value *)&keycode);
			}
			else if(event == Input::EVENT_KEYUP){
				auto native = INJECT(Native);
				auto e = native->getEvent();
				script::String event;
				event.setValue(Input::EVENT_KEYUP);
				script::Number keycode;
				keycode.setValue(e->key.keysym.scancode);
				_engine.call("_on_system_event", (script::Value*)&event,(script::Value *)&keycode);
			}
		}

	public:
		DEFINE_TOKEN(lux::system::Script);
		Script() {
			auto app = INJECT(Application);
			app->addEventListener(Application::EVENT_READY, this);
			app->addEventListener(Application::EVENT_LOOP, this);
			auto graphic = INJECT(Graphic);
			graphic->addEventListener(Graphic::EVENT_LOOP, this);
			auto input = INJECT(Input);
			input->addEventListener(Input::EVENT_KEYDOWN,this);
			input->addEventListener(Input::EVENT_KEYUP,this);

			script::Function func;
			SET_FUNC(println);
			SET_FUNC(exit);
			SET_FUNC(asset);
			_SET_FUNC(Sprite_load, runtime);
			_SET_FUNC(Sprite_create, runtime);
			_SET_FUNC(Sprite_begin, runtime);
			_SET_FUNC(Sprite_end, runtime);
			_SET_FUNC(Font_load, runtime);

			script::Object runtime;
			_ADD_FUNC(runtime, exists, _Runtime);
			_ADD_FUNC(runtime, loadModule, _Runtime);
			_ADD_FUNC(runtime, load, _Runtime);
			_engine.setValue("runtime", &runtime);

			_engine.execFile("script/base/require.js");
			_engine.setValue("runtime", script::Undefined::singleton());

			_engine.execFile("script/runtime/console.js");
			_engine.execFile("script/runtime/event.js");
		}
		script::Engine* getEngine() {
			return &_engine;
		}
	};
}
#undef ADD_FUNC
#endif _H_LUX_SYSTEM_SCRIPT_