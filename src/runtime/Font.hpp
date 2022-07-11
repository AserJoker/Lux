#ifndef _H_LUX_RUNTIME_FONT_
#define _H_LUX_RUNTIME_FONT_
#include "resource/Font.hpp"
#include "system/Resource.hpp"
#include "Sprite.hpp"
#include "util.hpp"
namespace lux::runtime
{
    class Font
    {
    public:
        static duk_idx_t Font_dispose(duk_context *ctx)
        {
            CHECK_ARG_LEN(0);
            auto top = duk_get_top(ctx);
            auto font = getObject<resource::Font>(ctx);
            if (font == nullptr || font->getClassName() != resource::Font::TOKEN)
            {
                duk_type_error(ctx, "not font object");
            }
            else
            {
                font._release();
            }
            duk_set_top(ctx, top);
            return 0;
        }
        static duk_idx_t Font_drawText(duk_context *ctx)
        {
            CHECK_ARG_LEN(8);
            CHECK_ARG_OBJECT(0);
            CHECK_ARG_STRING(1);
            CHECK_ARG_NUMBER(2);
            CHECK_ARG_NUMBER(3);
            CHECK_ARG_NUMBER(4);
            CHECK_ARG_NUMBER(5);
            CHECK_ARG_NUMBER(6);
            CHECK_ARG_NUMBER(7);
            auto top = duk_get_top(ctx);
            auto target = getObject<resource::Sprite>(ctx, 0);
            auto text = duk_get_string(ctx, 1);
            auto x = duk_get_int(ctx, 2);
            auto y = duk_get_int(ctx, 3);
            auto r = duk_get_int(ctx, 4);
            auto g = duk_get_int(ctx, 5);
            auto b = duk_get_int(ctx, 6);
            auto a = duk_get_int(ctx, 7);
            auto font = getObject<resource::Font>(ctx);
            if (target == nullptr || target->getClassName() != resource::Sprite::TOKEN)
            {
                duk_type_error(ctx, "not sprite object");
            }
            else if (font == nullptr || font->getClassName() != resource::Font::TOKEN)
            {
                duk_type_error(ctx, "not font object");
            }
            else
            {
                try
                {
                    font->drawText(target, text, x, y, r, g, b, a);
                }
                catch (std::exception &expr)
                {
                    duk_reference_error(ctx, expr.what());
                }
            }
            return 0;
        }
        static void initFont(core::Pointer<resource::Font> font, duk_context *ctx)
        {
            auto obj = duk_get_top(ctx);
            duk_push_object(ctx);
            duk_push_number(ctx, font->getId());
            duk_put_prop_string(ctx, obj, "handle");
            duk_push_c_function(ctx, Font::Font_drawText, 8);
            duk_put_prop_string(ctx, obj, "drawText");
            duk_push_c_function(ctx, Font::Font_dispose, 0);
            duk_put_prop_string(ctx, obj, "dispose");
        }
    };

    static duk_idx_t Font_load(duk_context *ctx)
    {
        CHECK_ARG_LEN(2);
        CHECK_ARG_STRING(0);
        CHECK_ARG_NUMBER(1);
        auto token = duk_get_string(ctx, 0);
        auto size = duk_get_int(ctx, 1);
        auto R = INJECT(system::Resource);
        try
        {
            auto font = resource::Font::load(R->load(token), size);
            font._addRef();
            Font::initFont(font, ctx);
        }
        catch (std::exception &exp)
        {
            duk_reference_error(ctx, exp.what());
        }
        return 1;
    }
} // namespace lux::runtime

#endif