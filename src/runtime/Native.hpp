#ifndef _H_LUX_RUNTIME_NATIVE_
#define _H_LUX_RUNTIME_NATIVE_
#include <duktape.h>
#include "util.hpp"
#include "system/Native.hpp"
namespace lux::runtime
{
    class Native{
        public:
        static duk_idx_t getWindowSize(duk_context *ctx){
            CHECK_ARG_LEN(0);
            auto native = INJECT(system::Native);
            auto win = native->getWindow();
            int w,h;
            SDL_GetWindowSize(win,&w,&h);
            auto arr  =duk_get_top(ctx);
            duk_push_array(ctx);
            duk_push_number(ctx,w);
            duk_put_prop_index(ctx,arr,0);
            duk_push_number(ctx,h);
            duk_put_prop_index(ctx,arr,1);
            return 1;
        }
    };
} // namespace lux::runtime
#endif