#ifndef _H_LUX_CORE_EVENTBUS_
#define _H_LUX_CORE_EVENTBUS_

#include "Object.hpp"
#include <map>
#include <string>
#include <vector>

namespace lux::core {
    class EventBus : public Object {
    public:
        class BaseEventListener {
        };

    private:
        std::map<std::string, std::vector<BaseEventListener *>> _listeners;

    public:
        DEFINE_TOKEN(lux::core::EventBus);

        template<c_string type>
        class BaseEvent {
        public:
            BaseEvent() = default;;

            virtual ~BaseEvent() = default;

            static const char *getType() { return type.value; }
        };

        template<class T>
        class EventListener : public BaseEventListener {
        private:
            core::Pointer<EventBus> _pEventRef_EventBus;
        public:
            virtual void on(T *event) = 0;

            EventListener() {
                _pEventRef_EventBus = INJECT(EventBus);
                _pEventRef_EventBus->addEventListener(T::getType(), this);
            }

            virtual ~EventListener() {
                _pEventRef_EventBus->removeEventListener(T::getType(), this);
            }
        };

        template<class T>
        void emit(T event) {
            auto listeners = _listeners[T::getType()];
            for (auto &_lis: listeners) {
                auto lis = (EventListener<T> *) _lis;
                lis->on(&event);
            }
        }

        void addEventListener(const std::string &event, BaseEventListener *lis) {
            auto list = _listeners[event];
            for (auto &it: list) {
                if (it == lis) {
                    return;
                }
            }
            list.push_back(lis);
            _listeners[event] = list;
        }

        void removeEventListener(const std::string &event, BaseEventListener *lis) {
            auto list = _listeners[event];
            std::erase(list, lis);
            _listeners[event] = list;
        }
    };
} // namespace lux::system

#endif
