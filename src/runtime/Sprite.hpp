#ifndef _H_LUX_RUNTIME_SPRITE_
#define _H_LUX_RUNTIME_SPRITE_
#include "resource/Sprite.hpp"
#include "system/Resource.hpp"
#include "util.hpp"
namespace lux::runtime {
    class Sprite {
    public:
        static duk_idx_t Sprite_dispose(duk_context* ctx) {
            CHECK_ARG_LEN(0);
            auto top = duk_get_top(ctx);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                sprite._release();
            }
            duk_set_top(ctx, top);
            return 0;
        }
        static duk_idx_t Sprite_draw(duk_context* ctx) {
            CHECK_ARG_LEN(0);
            auto top = duk_get_top(ctx);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                try {
                    sprite->draw();
                }
                catch (std::exception& expr) {
                    duk_reference_error(ctx, expr.what());
                }
            }
            duk_set_top(ctx, top);
            return 0;
        }
        static duk_idx_t Sprite_setSourceRect(duk_context* ctx) {
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
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                sprite->setSourceRect(x, y, w, h);
            }
            duk_set_top(ctx, top);
            return 0;
        }
        static duk_idx_t Sprite_setTargetRect(duk_context* ctx) {
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
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                sprite->setTargetRect(x, y, w, h);
            }
            duk_set_top(ctx, top);
            return 0;
        }
        static duk_idx_t Sprite_setRotation(duk_context* ctx) {
            CHECK_ARG_LEN(3);
            CHECK_ARG_NUMBER(0);
            CHECK_ARG_NUMBER(1);
            CHECK_ARG_NUMBER(2);
            auto top = duk_get_top(ctx);
            auto x = duk_get_int(ctx, 0);
            auto y = duk_get_int(ctx, 1);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                auto angle = duk_get_number(ctx, 3);
                sprite->setRotation(x, y, angle);
            }
            duk_set_top(ctx, top);
            return 0;
        }
        static duk_idx_t Sprite_setVisible(duk_context* ctx) {
            CHECK_ARG_LEN(1);
            CHECK_ARG_BOOLEAN(0);
            auto top = duk_get_top(ctx);
            auto visible = duk_get_boolean(ctx, 0);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                sprite->setVisible(visible);
            }
            duk_set_top(ctx, top);
            return 0;
        }
        static duk_idx_t Sprite_setOpacity(duk_context* ctx) {
            CHECK_ARG_LEN(1);
            CHECK_ARG_NUMBER(0);
            auto top = duk_get_top(ctx);
            auto opacity = duk_get_int(ctx, 0);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                sprite->setOpacity(opacity);
            }
            duk_set_top(ctx, top);
            return 0;
        }
        static duk_idx_t Sprite_getSourceRect(duk_context* ctx) {
            CHECK_ARG_LEN(0);
            auto top = duk_get_top(ctx);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
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
        static duk_idx_t Sprite_getTargetRect(duk_context* ctx) {
            CHECK_ARG_LEN(0);
            auto top = duk_get_top(ctx);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
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
        static duk_idx_t Sprite_getRotation(duk_context* ctx) {
            CHECK_ARG_LEN(0);
            auto top = duk_get_top(ctx);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
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
        static duk_idx_t Sprite_getVisible(duk_context* ctx) {
            CHECK_ARG_LEN(0);
            auto top = duk_get_top(ctx);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                bool visible;
                sprite->getVisible(&visible);
                duk_push_boolean(ctx, visible);
            }
            return 1;
        }
        static duk_idx_t Sprite_getOpacity(duk_context* ctx) {
            CHECK_ARG_LEN(0);
            auto top = duk_get_top(ctx);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                Uint8 opacity;
                sprite->getOpacity(&opacity);
                duk_push_number(ctx, opacity);
            }
            return 1;
        }
        static duk_idx_t Sprite_getSize(duk_context* ctx) {
            CHECK_ARG_LEN(0);
            auto top = duk_get_top(ctx);
            auto sprite = runtime::getObject<resource::Sprite>(ctx);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                int width, height;
                sprite->getSize(&width, &height);
                auto arr = duk_get_top(ctx);
                duk_push_array(ctx);
                duk_push_number(ctx, width);
                duk_put_prop_index(ctx, arr, 0);
                duk_push_number(ctx, height);
                duk_put_prop_index(ctx, arr, 1);
            }
            return 1;
        }

        static void initSprite(core::Pointer<resource::Sprite> sprite, duk_context* ctx) {
            auto obj = duk_get_top(ctx);
            duk_push_object(ctx);
            duk_push_number(ctx, sprite->getId());
            duk_put_prop_string(ctx, obj, "handle");
            duk_push_c_function(ctx, Sprite::Sprite_dispose, 0);
            duk_put_prop_string(ctx, obj, "dispose");
            duk_push_c_function(ctx, Sprite::Sprite_draw, 0);
            duk_put_prop_string(ctx, obj, "draw");
            duk_push_c_function(ctx, Sprite::Sprite_getRotation, 0);
            duk_put_prop_string(ctx, obj, "getRotation");
            duk_push_c_function(ctx, Sprite::Sprite_getSourceRect, 0);
            duk_put_prop_string(ctx, obj, "getSourceRect");
            duk_push_c_function(ctx, Sprite::Sprite_getTargetRect, 0);
            duk_put_prop_string(ctx, obj, "getTargetRect");
            duk_push_c_function(ctx, Sprite::Sprite_getVisible, 0);
            duk_put_prop_string(ctx, obj, "getVisible");
            duk_push_c_function(ctx, Sprite::Sprite_getOpacity, 0);
            duk_put_prop_string(ctx, obj, "getOpacity");
            duk_push_c_function(ctx, Sprite::Sprite_getSize, 0);
            duk_put_prop_string(ctx, obj, "getSize");
            duk_push_c_function(ctx, Sprite::Sprite_setRotation, 3);
            duk_put_prop_string(ctx, obj, "setRotation");
            duk_push_c_function(ctx, Sprite::Sprite_setSourceRect, 4);
            duk_put_prop_string(ctx, obj, "setSourceRect");
            duk_push_c_function(ctx, Sprite::Sprite_setTargetRect, 4);
            duk_put_prop_string(ctx, obj, "setTargetRect");
            duk_push_c_function(ctx, Sprite::Sprite_setVisible, 1);
            duk_put_prop_string(ctx, obj, "setVisible");
            duk_push_c_function(ctx, Sprite::Sprite_setOpacity, 1);
            duk_put_prop_string(ctx, obj, "setOpacity");
        }
    };

    static duk_idx_t Sprite_load(duk_context* ctx) {
        CHECK_ARG_LEN(1);
        CHECK_ARG_STRING(0);
        auto token = duk_get_string(ctx, 0);
        auto R = INJECT(system::Resource);
        try {
            auto sprite = resource::Sprite::load(R->load(token));
            sprite._addRef();
            Sprite::initSprite(sprite, ctx);
        }
        catch (std::exception& exp) {
            duk_reference_error(ctx, exp.what());
        }
        return 1;
    }

    static duk_idx_t Sprite_create(duk_context* ctx) {
        CHECK_ARG_LEN(3);
        CHECK_ARG_NUMBER(0);
        CHECK_ARG_NUMBER(1);
        CHECK_ARG_NUMBER(2);
        auto width = duk_get_int(ctx, 0);
        auto height = duk_get_int(ctx, 1);
        auto access = duk_get_int(ctx, 2);
        auto R = INJECT(system::Resource);
        try {
            auto sprite = resource::Sprite::create(width, height, access);
            sprite._addRef();
            Sprite::initSprite(sprite, ctx);
        }
        catch (std::exception& exp) {
            duk_reference_error(ctx, exp.what());
        }
        return 1;
    }

    static duk_idx_t Sprite_begin(duk_context* ctx) {
        CHECK_ARG_LEN(1);
        auto top = duk_get_top(ctx);
        if (duk_is_object(ctx, 0)) {
            auto _handle = duk_get_top(ctx);
            duk_get_prop_string(ctx, 0, "handle");
            auto id = duk_get_int(ctx, _handle);
            auto sprite = core::Object::select<resource::Sprite>(id);
            if (sprite == nullptr || sprite->getClassName() != resource::Sprite::TOKEN) {
                duk_type_error(ctx, "not sprite object");
            }
            else {
                resource::Sprite::begin(sprite);
            }
        }
        else if (duk_is_undefined(ctx, 0)) {
            try {
                resource::Sprite::begin();
            }
            catch (std::exception& expr) {
                duk_reference_error(ctx, expr.what());
            }
        }
        else {
            duk_reference_error(ctx, "INVALID ARGUMENT");
        }
        duk_set_top(ctx, top);
        return 0;
    }

    static duk_idx_t Sprite_end(duk_context* ctx) {
        CHECK_ARG_LEN(0);
        resource::Sprite::end();
        return 0;
    }
} // namespace lux::resource

#endif