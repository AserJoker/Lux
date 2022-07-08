#ifndef _H_LUX_SYSTEM_SCRIPT_
#define _H_LUX_SYSTEM_SCRIPT_
#include "Application.hpp"
#include "Resource.hpp"
#include "Graphic.hpp"
#include "resource/Sprite.hpp"
#include "script/Engine.hpp"
#define _ADD_FUNC(obj, name, host) \
	script::Function name;         \
	name.setValue(host::name);     \
	obj.setField(#name, &name);
#define ADD_FUNC(obj, name) _ADD_FUNC(obj, name, Script)

#define CHECK_ARG_LEN(len, msg)            \
	{                                      \
		auto length = duk_get_top(ctx);    \
		if (length < len)                  \
		{                                  \
			duk_reference_error(ctx, msg); \
		}                                  \
	}
#define CHECK_ARG_NUMBER(index, msg)    \
	{                                   \
		if (!duk_is_number(ctx, index)) \
		{                               \
			duk_type_error(ctx, msg);   \
		}                               \
	}
#define CHECK_ARG_BOOLEAN(index, msg)    \
	{                                    \
		if (!duk_is_boolean(ctx, index)) \
		{                                \
			duk_type_error(ctx, msg);    \
		}                                \
	}
#define CHECK_ARG_STRING(index, msg)    \
	{                                   \
		if (!duk_is_string(ctx, index)) \
		{                               \
			duk_type_error(ctx, msg);   \
		}                               \
	}
#define SET_FUNC(name)           \
	func.setValue(Script::name); \
	_engine.setValue(#name, &func);
namespace lux::system
{
	class Script : public core::EventEmitter
	{
	private:
		class _Runtime
		{
		public:
			static duk_idx_t exists(duk_context *ctx)
			{
				auto path = duk_get_string(ctx, 0);
				auto isExists = std::filesystem::exists(path);
				isExists &= std::filesystem::is_regular_file(path);
				duk_push_boolean(ctx, isExists);
				return 1;
			}
			static duk_idx_t loadModule(duk_context *ctx)
			{
				std::string name = duk_get_string(ctx, 0);
				duk_push_undefined(ctx);
				return 1;
			}
			static duk_idx_t load(duk_context *ctx)
			{
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
				while (!file.eof())
				{
					char c;
					file >> c;
					if (!file.eof())
					{
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
				if (duk_pcall(ctx, 0))
				{
					script->_engine.error();
				}
				duk_get_global_string(ctx, "module");
				return 1;
			}
		};

		static duk_idx_t asset(duk_context *ctx)
		{
			auto R = INJECT(Resource);
			CHECK_ARG_LEN(2, "asset need 2 argument");
			CHECK_ARG_STRING(0, "asset need 2 string argument");
			CHECK_ARG_STRING(1, "asset need 2 string argument");
			auto token = duk_get_string(ctx, 0);
			std::string type = duk_get_string(ctx, 1);
			try
			{
				auto buf = R->load(token);
				if (type == "string")
				{
					char *str = new char[buf->getBufferSize() + 1];
					str[buf->getBufferSize()] = 0;
					buf->read(str);
					duk_push_string(ctx, str);
					delete[] str;
				}
				else if (type == "buffer")
				{
					auto target = duk_push_buffer(ctx, buf->getBufferSize(), 0);
					buf->read(target);
				}
				else
				{
					duk_reference_error(ctx, "unknown resource Type");
				}
			}
			catch (std::exception &exp)
			{
				std::cout << exp.what() << std::endl;
				duk_push_undefined(ctx);
			}
			return 1;
		}
		static duk_idx_t println(duk_context *ctx)
		{
			auto msg = duk_get_string(ctx, 0);
			std::cout << msg << std::endl;
			return 0;
		}
		static duk_idx_t exit(duk_context *ctx)
		{
			auto app = INJECT(Application);
			app->exit();
			return 0;
		}

		static duk_idx_t Sprite_load(duk_context *ctx)
		{
			CHECK_ARG_LEN(1, "Sprite_load need 1 argument");
			CHECK_ARG_STRING(0, "Sprite_load need 1 string argument");
			auto token = duk_get_string(ctx, 0);
			auto R = INJECT(Resource);
			try
			{
				auto sprite = resource::Sprite::load(R->load(token));
				sprite._addRef();
				duk_push_number(ctx, sprite->getId());
			}
			catch (std::exception &exp)
			{
				duk_reference_error(ctx, exp.what());
			}
			return 1;
		}
		static duk_idx_t Sprite_dispose(duk_context *ctx)
		{
			CHECK_ARG_LEN(1, "Sprite_dispose need 1 argument");
			CHECK_ARG_NUMBER(0, "Sprite_dispose need 1 number argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				sprite->dispose();
				sprite._release();
			}
			return 0;
		}
		static duk_idx_t Sprite_draw(duk_context *ctx)
		{
			CHECK_ARG_LEN(1, "Sprite_draw need 1 argument");
			CHECK_ARG_NUMBER(0, "Sprite_draw need 1 number argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				try
				{
					sprite->draw();
				}
				catch (std::exception &expr)
				{
					duk_reference_error(ctx, expr.what());
				}
			}
			return 0;
		}
		static duk_idx_t Sprite_setSourceRect(duk_context *ctx)
		{
			CHECK_ARG_LEN(5, "Sprite_setSourceRect need 5 argument");
			CHECK_ARG_NUMBER(0, "Sprite_setSourceRect need 1 number argument");
			CHECK_ARG_NUMBER(1, "Sprite_setSourceRect need 2 number argument");
			CHECK_ARG_NUMBER(2, "Sprite_setSourceRect need 3 number argument");
			CHECK_ARG_NUMBER(3, "Sprite_setSourceRect need 4 number argument");
			CHECK_ARG_NUMBER(4, "Sprite_setSourceRect need 5 number argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				auto x = duk_get_int(ctx, 1);
				auto y = duk_get_int(ctx, 2);
				auto w = duk_get_int(ctx, 3);
				auto h = duk_get_int(ctx, 4);
				sprite->setSourceRect(x, y, w, h);
			}
			return 0;
		}
		static duk_idx_t Sprite_setTargetRect(duk_context *ctx)
		{
			CHECK_ARG_LEN(5, "Sprite_setTargetRect need 5 argument");
			CHECK_ARG_NUMBER(0, "Sprite_setTargetRect need 1 number argument");
			CHECK_ARG_NUMBER(1, "Sprite_setTargetRect need 2 number argument");
			CHECK_ARG_NUMBER(2, "Sprite_setTargetRect need 3 number argument");
			CHECK_ARG_NUMBER(3, "Sprite_setTargetRect need 4 number argument");
			CHECK_ARG_NUMBER(4, "Sprite_setTargetRect need 5 number argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				auto x = duk_get_int(ctx, 1);
				auto y = duk_get_int(ctx, 2);
				auto w = duk_get_int(ctx, 3);
				auto h = duk_get_int(ctx, 4);
				sprite->setTargetRect(x, y, w, h);
			}
			return 0;
		}
		static duk_idx_t Sprite_setRotation(duk_context *ctx)
		{
			CHECK_ARG_LEN(4, "Sprite_setRotation need 5 argument");
			CHECK_ARG_NUMBER(0, "Sprite_setRotation need 1 number argument");
			CHECK_ARG_NUMBER(1, "Sprite_setRotation need 2 number argument");
			CHECK_ARG_NUMBER(2, "Sprite_setRotation need 3 number argument");
			CHECK_ARG_NUMBER(3, "Sprite_setRotation need 4 number argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				auto x = duk_get_int(ctx, 1);
				auto y = duk_get_int(ctx, 2);
				auto angle = duk_get_number(ctx, 3);
				sprite->setRotation(x, y, angle);
			}
			return 0;
		}
		static duk_idx_t Sprite_setVisible(duk_context *ctx)
		{
			CHECK_ARG_LEN(2, "Sprite_setVisible need 2 argument");
			CHECK_ARG_NUMBER(0, "Sprite_setVisible need 1st number argument");
			CHECK_ARG_BOOLEAN(1, "Sprite_setVisible need 2nd boolean argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				auto visible = duk_get_boolean(ctx, 1);
				sprite->setVisible(visible);
			}
			return 0;
		}
		static duk_idx_t Sprite_getSourceRect(duk_context *ctx)
		{
			CHECK_ARG_LEN(1, "Sprite_getSourceRect need 1 argument");
			CHECK_ARG_NUMBER(0, "Sprite_getSourceRect need 1st number argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				int x, y, w, h;
				sprite->getSourceRect(&x, &y, &w, &h);
				auto arr = duk_get_top(ctx);
				duk_push_array(ctx);
				duk_push_number(ctx, x);
				duk_put_prop_index(ctx, arr, 0);
				duk_push_number(ctx, y);
				duk_put_prop_index(ctx, arr, 1);
				duk_push_number(ctx, w);
				duk_put_prop_index(ctx, arr, 2);
				duk_push_number(ctx, h);
				duk_put_prop_index(ctx, arr, 3);
			}
			return 1;
		}
		static duk_idx_t Sprite_getTargeteRect(duk_context *ctx)
		{
			CHECK_ARG_LEN(1, "Sprite_getTargeteRect need 1 argument");
			CHECK_ARG_NUMBER(0, "Sprite_getTargeteRect need 1st number argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				int x, y, w, h;
				sprite->getTargetRect(&x, &y, &w, &h);
				auto arr = duk_get_top(ctx);
				duk_push_array(ctx);
				duk_push_number(ctx, x);
				duk_put_prop_index(ctx, arr, 0);
				duk_push_number(ctx, y);
				duk_put_prop_index(ctx, arr, 1);
				duk_push_number(ctx, w);
				duk_put_prop_index(ctx, arr, 2);
				duk_push_number(ctx, h);
				duk_put_prop_index(ctx, arr, 3);
			}
			return 1;
		}
		static duk_idx_t Sprite_getRotation(duk_context *ctx)
		{
			CHECK_ARG_LEN(1, "Sprite_getRotation need 1 argument");
			CHECK_ARG_NUMBER(0, "Sprite_getRotation need 1st number argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				int x, y;
				double angle;
				sprite->getRotation(&x, &y, &angle);
				auto arr = duk_get_top(ctx);
				duk_push_array(ctx);
				duk_push_number(ctx, x);
				duk_put_prop_index(ctx, arr, 0);
				duk_push_number(ctx, y);
				duk_put_prop_index(ctx, arr, 1);
				duk_push_number(ctx, angle);
				duk_put_prop_index(ctx, arr, 2);
			}
			return 1;
		}
		static duk_idx_t Sprite_getVisible(duk_context *ctx)
		{
			CHECK_ARG_LEN(1, "Sprite_getVisible need 1 argument");
			CHECK_ARG_NUMBER(0, "Sprite_getVisible need 1st number argument");
			auto id = duk_get_int(ctx, 0);
			auto sprite = core::Object::select<resource::Sprite>(id);
			if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
			{
				duk_type_error(ctx, "not sprite object");
			}
			else
			{
				bool visible;
				sprite->getVisible(&visible);
				duk_push_boolean(ctx, visible);
			}
			return 1;
		}

		script::Engine _engine;

		void onReady()
		{
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
		void on(core::EventEmitter *emitter, const std::string &event)
		{
			if (event == Application::EVENT_READY)
			{
				onReady();
				script::String event;
				event.setValue(Application::EVENT_READY);
				_engine.call("_on_system_event", (script::Value *)&event);
			}
			else if (event == Graphic::EVENT_LOOP)
			{
				script::String event;
				event.setValue(Graphic::EVENT_LOOP);
				_engine.call("_on_system_event", (script::Value *)&event);
			}
		}

	public:
		DEFINE_TOKEN(lux::system::Script);
		Script()
		{
			auto app = INJECT(Application);
			app->addEventListener(Application::EVENT_READY, this);
			auto graphic = INJECT(Graphic);
			graphic->addEventListener(Graphic::EVENT_LOOP, this);

			script::Function func;
			func.setValue(Script::println);
			_engine.setValue("println", &func);
			func.setValue(Script::exit);
			_engine.setValue("exit", &func);
			func.setValue(Script::asset);
			_engine.setValue("asset", &func);
			SET_FUNC(Sprite_load);
			SET_FUNC(Sprite_dispose);
			SET_FUNC(Sprite_draw);
			SET_FUNC(Sprite_setSourceRect);
			SET_FUNC(Sprite_setTargetRect);
			SET_FUNC(Sprite_setVisible);
			SET_FUNC(Sprite_setRotation);
			SET_FUNC(Sprite_getSourceRect);
			SET_FUNC(Sprite_getTargeteRect);
			SET_FUNC(Sprite_getVisible);

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
		script::Engine *getEngine()
		{
			return &_engine;
		}
	};
}
#undef ADD_FUNC
#endif _H_LUX_SYSTEM_SCRIPT_