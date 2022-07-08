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

#define CHECK_ARG_LEN(len)                                \
	{                                                     \
		auto length = duk_get_top(ctx);                   \
		if (length < len)                                 \
		{                                                 \
			duk_reference_error(ctx, "INVALID ARGUMENT"); \
		}                                                 \
	}
#define CHECK_ARG_NUMBER(index)                      \
	{                                                \
		if (!duk_is_number(ctx, index))              \
		{                                            \
			duk_type_error(ctx, "INVALID ARGUMENT"); \
		}                                            \
	}
#define CHECK_ARG_BOOLEAN(index)                     \
	{                                                \
		if (!duk_is_boolean(ctx, index))             \
		{                                            \
			duk_type_error(ctx, "INVALID ARGUMENT"); \
		}                                            \
	}
#define CHECK_ARG_STRING(index)                      \
	{                                                \
		if (!duk_is_string(ctx, index))              \
		{                                            \
			duk_type_error(ctx, "INVALID ARGUMENT"); \
		}                                            \
	}
#define CHECK_ARG_OBJECT(index)                      \
	{                                                \
		if (!duk_is_object(ctx, index))              \
		{                                            \
			duk_type_error(ctx, "INVALID ARGUMENT"); \
		}                                            \
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
				duk_get_global_string(ctx, "exports");
				return 1;
			}
		};

		static duk_idx_t asset(duk_context *ctx)
		{
			auto R = INJECT(Resource);
			CHECK_ARG_LEN(2);
			CHECK_ARG_STRING(0);
			CHECK_ARG_STRING(1);
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
			CHECK_ARG_LEN(1);
			CHECK_ARG_STRING(0);
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

		class _Sprite
		{
		public:
			static duk_idx_t Sprite_dispose(duk_context *ctx)
			{
				CHECK_ARG_LEN(0);
				auto top = duk_get_top(ctx);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
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
				duk_set_top(ctx, top);
				return 0;
			}
			static duk_idx_t Sprite_draw(duk_context *ctx)
			{
				CHECK_ARG_LEN(0);
				auto top = duk_get_top(ctx);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
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
				duk_set_top(ctx, top);
				return 0;
			}
			static duk_idx_t Sprite_setSourceRect(duk_context *ctx)
			{
				CHECK_ARG_LEN(4);
				CHECK_ARG_NUMBER(0);
				CHECK_ARG_NUMBER(1);
				CHECK_ARG_NUMBER(2);
				CHECK_ARG_NUMBER(3);
				auto top = duk_get_top(ctx);
				auto x = duk_get_int(ctx, 0);
				auto y = duk_get_int(ctx, 1);
				auto w = duk_get_int(ctx, 2);
				auto h = duk_get_int(ctx, 3);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else
				{
					sprite->setSourceRect(x, y, w, h);
				}
				duk_set_top(ctx, top);
				return 0;
			}
			static duk_idx_t Sprite_setTargetRect(duk_context *ctx)
			{
				CHECK_ARG_LEN(4);
				CHECK_ARG_NUMBER(0);
				CHECK_ARG_NUMBER(1);
				CHECK_ARG_NUMBER(2);
				CHECK_ARG_NUMBER(3);
				auto top = duk_get_top(ctx);
				auto x = duk_get_int(ctx, 0);
				auto y = duk_get_int(ctx, 1);
				auto w = duk_get_int(ctx, 2);
				auto h = duk_get_int(ctx, 3);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else
				{
					sprite->setTargetRect(x, y, w, h);
				}
				duk_set_top(ctx, top);
				return 0;
			}
			static duk_idx_t Sprite_setRotation(duk_context *ctx)
			{
				CHECK_ARG_LEN(3);
				CHECK_ARG_NUMBER(0);
				CHECK_ARG_NUMBER(1);
				CHECK_ARG_NUMBER(2);
				auto top = duk_get_top(ctx);
				auto x = duk_get_int(ctx, 0);
				auto y = duk_get_int(ctx, 1);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else
				{
					auto angle = duk_get_number(ctx, 3);
					sprite->setRotation(x, y, angle);
				}
				duk_set_top(ctx, top);
				return 0;
			}
			static duk_idx_t Sprite_setVisible(duk_context *ctx)
			{
				CHECK_ARG_LEN(1);
				CHECK_ARG_BOOLEAN(0);
				auto top = duk_get_top(ctx);
				auto visible = duk_get_boolean(ctx, 0);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else
				{
					sprite->setVisible(visible);
				}
				duk_set_top(ctx, top);
				return 0;
			}
			static duk_idx_t Sprite_setOpacity(duk_context *ctx)
			{
				CHECK_ARG_LEN(1);
				CHECK_ARG_NUMBER(0);
				auto top = duk_get_top(ctx);
				auto opacity = duk_get_int(ctx, 0);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else
				{
					sprite->setOpacity(opacity);
				}
				duk_set_top(ctx, top);
				return 0;
			}
			static duk_idx_t Sprite_getSourceRect(duk_context *ctx)
			{
				CHECK_ARG_LEN(0);
				auto top = duk_get_top(ctx);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else
				{
					int x, y, w, h;
					sprite->getSourceRect(&x, &y, &w, &h);
					duk_set_top(ctx, top);
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
			static duk_idx_t Sprite_getTargetRect(duk_context *ctx)
			{
				CHECK_ARG_LEN(0);
				auto top = duk_get_top(ctx);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else
				{
					int x, y, w, h;
					sprite->getTargetRect(&x, &y, &w, &h);
					duk_set_top(ctx, top);
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
				CHECK_ARG_LEN(0);
				auto top = duk_get_top(ctx);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
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
					duk_set_top(ctx, top);
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
			static duk_idx_t Sprite_getVisible(duk_context *ctx){
				CHECK_ARG_LEN(0);
				auto top = duk_get_top(ctx);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else{
					bool visible;
					sprite->getVisible(&visible);
					duk_push_boolean(ctx,visible);
				}
				return 1;
			}
			static duk_idx_t Sprite_getOpacity(duk_context *ctx){
				CHECK_ARG_LEN(0);
				auto top = duk_get_top(ctx);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else{
					Uint8 opacity;
					sprite->getOpacity(&opacity);
					duk_push_number(ctx,opacity);
				}
				return 1;
			}
			static duk_idx_t Sprite_getSize(duk_context *ctx){
				CHECK_ARG_LEN(0);
				auto top = duk_get_top(ctx);
				auto _this = duk_get_top(ctx);
				duk_push_this(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, _this, "handle");
				auto id = duk_get_int(ctx, _handle);
				auto sprite = core::Object::select<resource::Sprite>(id);
				if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN)
				{
					duk_type_error(ctx, "not sprite object");
				}
				else{
					int width,height;
					sprite->getSize(&width,&height);
					auto arr = duk_get_top(ctx);
					duk_push_array(ctx);
					duk_push_number(ctx,width);
					duk_put_prop_index(ctx,arr,0);
					duk_push_number(ctx,height);
					duk_put_prop_index(ctx,arr,1);
				}
				return 1;
			}
			
			static void initSprite(core::Pointer<resource::Sprite> sprite, duk_context *ctx)
			{
				auto obj = duk_get_top(ctx);
				duk_push_object(ctx);
				duk_push_number(ctx, sprite->getId());
				duk_put_prop_string(ctx, obj, "handle");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_dispose, 0);
				duk_put_prop_string(ctx, obj, "dispose");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_draw, 0);
				duk_put_prop_string(ctx, obj, "draw");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_getRotation, 0);
				duk_put_prop_string(ctx, obj, "getRotation");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_getSourceRect, 0);
				duk_put_prop_string(ctx, obj, "getSourceRect");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_getTargetRect, 0);
				duk_put_prop_string(ctx, obj, "getTargetRect");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_getVisible,0);
				duk_put_prop_string(ctx, obj, "getVisible");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_getOpacity,0);
				duk_put_prop_string(ctx, obj, "getOpacity");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_getSize,0);
				duk_put_prop_string(ctx, obj, "getSize");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_setRotation, 3);
				duk_put_prop_string(ctx, obj, "setRotation");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_setSourceRect, 4);
				duk_put_prop_string(ctx, obj, "setSourceRect");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_setTargetRect, 4);
				duk_put_prop_string(ctx, obj, "setTargetRect");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_setVisible, 1);
				duk_put_prop_string(ctx, obj, "setVisible");
				duk_push_c_function(ctx, Script::_Sprite::Sprite_setOpacity, 1);
				duk_put_prop_string(ctx, obj, "setOpacity");
			}
		};

		static duk_idx_t Sprite_load(duk_context *ctx)
		{
			CHECK_ARG_LEN(1);
			CHECK_ARG_STRING(0);
			auto token = duk_get_string(ctx, 0);
			auto R = INJECT(Resource);
			try
			{
				auto sprite = resource::Sprite::load(R->load(token));
				sprite._addRef();
				_Sprite::initSprite(sprite, ctx);
			}
			catch (std::exception &exp)
			{
				duk_reference_error(ctx, exp.what());
			}
			return 1;
		}

		static duk_idx_t Sprite_create(duk_context *ctx)
		{
			CHECK_ARG_LEN(3);
			CHECK_ARG_NUMBER(0);
			CHECK_ARG_NUMBER(1);
			CHECK_ARG_NUMBER(2);
			auto width = duk_get_int(ctx, 0);
			auto height = duk_get_int(ctx, 1);
			auto access = duk_get_int(ctx, 2);
			auto R = INJECT(Resource);
			try
			{
				auto sprite = resource::Sprite::create(width, height, access);
				sprite._addRef();
				_Sprite::initSprite(sprite, ctx);
			}
			catch (std::exception &exp)
			{
				duk_reference_error(ctx, exp.what());
			}
			return 1;
		}

		static duk_idx_t Sprite_setRenderTarget(duk_context *ctx)
		{
			CHECK_ARG_LEN(1);
			if (duk_is_object(ctx, 0))
			{
				auto top = duk_get_top(ctx);
				auto _handle = duk_get_top(ctx);
				duk_get_prop_string(ctx, 0, "handle");
				auto id = duk_get_int(ctx, _handle);
				duk_set_top(ctx, top);
				auto sprite = core::Object::select<resource::Sprite>(id);
				resource::Sprite::setTarget(sprite);
			}else if(duk_is_undefined(ctx,0)){
				resource::Sprite::setTarget();
			}else{
				duk_reference_error(ctx,"INVALID ARGUMENT");
			}
			return 0;
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
			SET_FUNC(println);
			SET_FUNC(exit);
			SET_FUNC(asset);
			SET_FUNC(Sprite_load);
			SET_FUNC(Sprite_create);
			SET_FUNC(Sprite_setRenderTarget);

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