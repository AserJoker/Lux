#ifndef _H_LUX_SYSTEM_APPLICATION_
#define _H_LUX_SYSTEM_APPLICATION_
#include "core/EventEmitter.hpp"
namespace lux::system {
    class Application :public core::EventEmitter {
    private:
        bool _isRunning = false;
    public:
        DEFINE_TOKEN(lux::system::Application);
        constexpr static const char* EVENT_INIT = "lux:system::Application.init";
        constexpr static const char* EVENT_READY = "lux:system::Application.ready";
        constexpr static const char* EVENT_QUIT = "lux:system::Application.quit";
        constexpr static const char* EVENT_LOOP = "lux:system::Application.loop";
        void run() {
            _isRunning = true;
            emit(EVENT_INIT);
            emit(EVENT_READY);
            while (_isRunning) {
                emit(EVENT_LOOP);
            }
            emit(EVENT_QUIT);
        }
        void exit() {
            _isRunning = false;
        }
    };
} // namespace lux::system

#endif //_H_LUX_SYSTEM_APPLICATION_