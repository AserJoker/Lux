#ifndef _H_LUX_SYSTEM_INPUT_
#define _H_LUX_SYSTEM_INPUT_
#include "Native.hpp"
namespace lux::system
{
    class Input : public core::EventEmitter
    {
    protected:
        void on(core::EventEmitter *emitter, const std::string &event) override
        {
            if (event == Native::EVENT_EVENT)
            {
                auto native = (Native *)emitter;
                auto event = native->getEvent();
                switch (event->type)
                {
                case SDL_KEYDOWN:
                    emit(EVENT_KEYDOWN);
                    break;
                case SDL_KEYUP:
                    emit(EVENT_KEYUP);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                case SDL_MOUSEBUTTONUP:
                    break;
                case SDL_MOUSEMOTION:
                    break;
                case SDL_MOUSEWHEEL:
                    break;
                default:
                    return;
                }
            }
        }

    public:
        DEFINE_TOKEN(lux::system::Input);
        Input()
        {
            auto native = INJECT(Native);
            native->addEventListener(Native::EVENT_EVENT, this);
        }
        static constexpr const char *EVENT_KEYDOWN = "lux::system::Input.keydown";
        static constexpr const char *EVENT_KEYUP = "lux::system::Input.keyup";
    };
} // namespace lux::system

#endif