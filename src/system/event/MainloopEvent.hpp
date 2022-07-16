#ifndef _H_LUX_EVENT_MAINLOOPEVENT_
#define _H_LUX_EVENT_MAINLOOPEVENT_
#include "core/EventBus.hpp"
namespace lux::event {
    using MainloopEvent = core::EventBus::BaseEvent<"mainloop">;
} // namespace lux::event

#endif