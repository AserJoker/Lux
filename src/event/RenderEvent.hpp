#ifndef _H_LUX_EVENT_RENDEREVENT_
#define _H_LUX_EVENT_RENDEREVENT_
#include"core/EventBus.hpp"
namespace lux::event {
    using RenderEvent = core::EventBus::BaseEvent<"render">;
} // namespace lux::event

#endif