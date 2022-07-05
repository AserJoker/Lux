#ifndef _H_LUX_SYSTEM_SCRIPT_
#define _H_LUX_SYSTEM_SCRIPT_
#include "Application.hpp"
#include "Graphic.hpp"
#include "resource/Image.hpp"
#include "script/Engine.hpp"
#define ADD_FUNC(obj,name) script::Function name;\
	name.setValue(Script::name);\
	obj.setField(#name,&name);
const char* requireJS = "function resolve(root, reactive) {\n"
"root = root.replace(/\\\\/g, '/');\n"
"reactive = reactive.replace(/\\\\/g, '/');\n"
"const rootPath = root.split('/');\n"
"const reactivePath = reactive.split('/');\n"
"reactivePath.forEach(function(p) {\n"
"	if (p === '.') {\n"
"		return;\n"
"	}\n"
"	if (p === '..') {\n"
"		rootPath.length--;\n"
"		return;\n"
"	}\n"
"	rootPath.push(p);\n"
"})\n"
"return rootPath.join('/');\n"
"}\n"
"function require(name) {\n"
"	var result;\n"
"	var absolute = resolve(__dirname, name);\n"
"	var current = module;\n"
"	if (native.exists(absolute)) {\n"
"		if (require.cache[absolute]) {\n"
"			return require.cache[absolute];\n"
"		}\n"
"		result = native.load(absolute);\n"
"	}\n"
"	else if (native.exists(absolute + \".js\")) {\n"
"		absolute += \".js\";\n"
"		if (require.cache[absolute]) {\n"
"			return require.cache[absolute];\n"
"		}\n"
"		result = native.load(absolute);\n"
"	}\n"
"	else if (native.exists(resolve(absolute, \"index.js\"))) {\n"
"		absolute = resolve(absolute, \"index.js\");\n"
"		if (require.cache[absolute]) {\n"
"			return require.cache[absolute];\n"
"		}\n"
"		result = native.load(absolute);\n"
"	}\n"
"	else {\n"
"		if (require.cache[name]) {\n"
"			return require.cache[name];\n"
"		}\n"
"		else {\n"
"			result = native.loadModule(name);\n"
"			absolute = name;\n"
"		}\n"
"	}\n"
"	if (result === undefined) {\n"
"		throw new ReferenceError(\"cannot load module:\" + name);\n"
"	}\n"
"	require.cache[absolute] = result;\n"
"	module = current;\n"
"	exports = module.exports;\n"
"	return result;\n"
"}\n"
"require.cache = {};\n"
"module={exports:{}};\n"
"exports=module.exports;\n";
namespace lux::system {
	class Script :public core::EventEmitter {
	private:
		static duk_idx_t println(duk_context* ctx) {
			auto msg = duk_get_string(ctx, 0);
			std::cout << msg << std::endl;
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
			auto script = INJECT(Script);
			if (name == "system") {
				script::Object system;
				script->_engine.pushValue(&system);
			}
			else {
				duk_push_undefined(ctx);
			}
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

		script::Engine _engine;
		core::Pointer<resource::Image> _pImage;
		void onReady() {
			//_pImage = resource::Image::create(100, 100, SDL_TEXTUREACCESS_STATIC);
			script::Object native;
			ADD_FUNC(native, println);
			ADD_FUNC(native, exists);
			ADD_FUNC(native, loadModule);
			ADD_FUNC(native, load);
			_engine.setValue("native", &native);
			script::String __dirname;
			script::String __filename;
			auto fullpath = std::filesystem::absolute("script/main.js");
			__dirname.setValue(fullpath.parent_path().string());
			__filename.setValue(fullpath.filename().string());
			_engine.setValue("__dirname", &__dirname);
			_engine.setValue("__filename", &__filename);
			_engine.execFile("require.js", requireJS);
			_engine.execFile("script/main.js");
		}
		void onLoop() {
			// SDL_Rect source = {0,0,100,100};
			// SDL_Rect target = {100,100,100,100};
			// _pImage->draw(&source, &target);
		}
	protected:
		void on(core::EventEmitter* emitter, const std::string& event) {
			if (event == Application::EVENT_READY) {
				onReady();
			}
			else if (event == Graphic::EVENT_LOOP) {
				onLoop();
			}
		}
	public:
		DEFINE_TOKEN(lux::system::Script);
		Script() {
			auto app = INJECT(Application);
			auto graphic = INJECT(Graphic);
			app->addEventListener(Application::EVENT_READY, this);
			graphic->addEventListener(Graphic::EVENT_LOOP, this);
		}
	};
}
#endif _H_LUX_SYSTEM_SCRIPT_