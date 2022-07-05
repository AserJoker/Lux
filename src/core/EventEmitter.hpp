#ifndef _LUX_CORE_EVENT_EMITTER_
#define _LUX_CORE_EVENT_EMITTER_
#include"Object.hpp"
#include<vector>
namespace lux::core {
    class EventEmitter :public Object {
    private:
        struct EventListener {
            std::string event;
            EventEmitter* listener;
        };

        struct AutoRelease {
            std::string event;
            Pointer<EventEmitter> _emitter;
        };

        std::vector<EventListener> _eventListeners;

        std::vector<AutoRelease> _autoReleases;

    protected:
        virtual void on(EventEmitter* emitter, const std::string& event) {}

    public:
        void emit(std::string event) {
            for (auto& listener : _eventListeners) {
                if (listener.event == event) {
                    listener.listener->on(this, event);
                }
            }
        }

        void addEventListener(const std::string& event, EventEmitter* listener) {
            for (auto it = _eventListeners.begin();it != _eventListeners.end();it++) {
                if (it->event == event && it->listener == listener) {
                    return;
                }
            }
            _eventListeners.push_back({event,listener});
            Pointer<EventEmitter> self(this);
            listener->_autoReleases.push_back({event,self});
        }

        void removeEventListener(const std::string& event, EventEmitter* listener) {
            for (auto it = _eventListeners.begin();it != _eventListeners.end();it++) {
                if (it->event == event && it->listener == listener) {
                    _eventListeners.erase(it);
                    return;
                }
            }
        }

        ~EventEmitter() override {
            for (auto& it : _autoReleases) {
                it._emitter->removeEventListener(it.event, this);
            }
        }
    };
} // namespace lux::core

#endif