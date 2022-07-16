#ifndef _H_LUX_EVENT_MAINLOOPEVENT_
#define _H_LUX_EVENT_MAINLOOPEVENT_
#include "../EventBus.hpp"
namespace lux::event {
    using MainloopEvent = system::EventBus::BaseEvent<"mainloop">;
} // namespace lux::event

#endif