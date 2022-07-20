#ifndef _H_LUX_SYSTEM_ICOMPONENT_
#define _H_LUX_SYSTEM_ICOMPONENT_

#include "core/Object.hpp"
#include "core/Container.hpp"
#include "core/EventBus.hpp"

namespace lux::system {
    class IComponent : public core::Object {
    protected:
        core::Pointer <core::EventBus> _pEventBus;
    public:
        IComponent() {
            _pEventBus = INJECT(core::EventBus);
        }
    };
} // namespace lux::system

#endif