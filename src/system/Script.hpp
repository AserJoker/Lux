#ifndef _H_LUX_SYSTEM_SCRIPT_
#define _H_LUX_SYSTEM_SCRIPT_
#include "Application.hpp"
#include "script/Engine.hpp"
#define _ADD_FUNC(obj,name,host) script::Function name;\
	name.setValue(host::name);\
	obj.setField(#name,&name);
#define ADD_FUNC(obj,name) _ADD_FUNC(obj,name,Script)

#define CHECK_ARG_LEN(len,msg) {auto length = duk_get_top(ctx);if(length!=len){duk_reference_error(ctx,msg);}}
#define CHECK_ARG_NUMBER(index,msg) {if(!duk_is_number(ctx,index)){duk_type_error(ctx,msg);}}
#define CHECK_ARG_STRING(index,msg) {if(!duk_is_string(ctx,index)){duk_type_error(ctx,msg);}}
namespace lux::system {
	class Script :public core::EventEmitter {
	private:
		static duk_idx_t println(duk_context* ctx) {
			auto msg = duk_get_string(ctx, 0);
			std::string str(msg);
			std::cout<<str;
			return 0;
		}
		static duk_idx_t exists(duk_context* ctx) {
			auto path = duk_get_string(ctx, 0);
			auto isExists = std::filesystem::exists(path);
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
			duk_get_global_string(ctx, "module");
			return 1;
		}

		static duk_idx_t exit(duk_context *ctx){
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
			}
		}
	public:
		DEFINE_TOKEN(lux::system::Script);
		Script() {
			auto app = INJECT(Application);
			app->addEventListener(Application::EVENT_READY, this);
			script::Object runtime;
			ADD_FUNC(runtime, exists);
			ADD_FUNC(runtime, loadModule);
			ADD_FUNC(runtime, load);
			_engine.setValue("runtime", &runtime);
			_engine.execFile("script/require.js");
			_engine.setValue("runtime",script::Undefined::singleton());
			script::Function println;
			println.setValue(Script::println);
			_engine.setValue("println",&println);
			script::Function exit;
			exit.setValue(Script::exit);
			_engine.setValue("exit",&exit);
		}
		script::Engine* getEngine(){
			return &_engine;
		}
	};
}
#undef ADD_FUNC
#endif _H_LUX_SYSTEM_SCRIPT_