#ifndef _H_LUX_RUNTIME_CHECK_
#define _H_LUX_RUNTIME_CHECK_
#include "core/Object.hpp"
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
namespace lux::runtime {
	template<class T> static core::Pointer<T> getObject(duk_context* ctx) {
		auto _this = duk_get_top(ctx);
		duk_push_this(ctx);
		auto _handle = duk_get_top(ctx);
		duk_get_prop_string(ctx, _this, "handle");
		auto id = duk_get_int(ctx, _handle);
		auto object = core::Object::select<T>(id);
		duk_set_top(ctx, _this);
		return object;
	}

} // namespace lux::runtime

#endif