#ifndef _H_LUX_SYSTEM_EVENTBUS_
#define _H_LUX_SYSTEM_EVENTBUS_
#include "core/Object.hpp"
#include <map>
#include <string>
#include <vector>
namespace lux::system {
  class EventBus : public core::Object {
  public:
    class BaseEventListener {};

  private:
    std::map<std::string, std::vector<BaseEventListener*>> _listeners;

  public:
    DEFINE_TOKEN(lux::system::EventBus);
    template <c_string type> class BaseEvent {
    public:
      BaseEvent() {};
      virtual ~BaseEvent() {}
      static const char* getType() { return type.value; }
    };
    template <class T> class EventListener : public BaseEventListener {
    public:
      virtual void on(T* event) = 0;
      EventListener() {
        auto bus = EventBus::getEventBus();
        bus._addRef();
        bus->addEventListener(T::getType(), this);
      }
      virtual ~EventListener() {
        auto bus = EventBus::getEventBus();
        bus->removeEventListener(T::getType(), this);
        bus._release();
      }
    };
    template <class T> void emit(T* event) {
      auto listeners = _listeners[T::getType()];
      for (auto& _lis : listeners) {
        auto lis = (EventListener<T> *)_lis;
        lis->on(event);
      }
    }
    void addEventListener(const std::string& event, BaseEventListener* lis) {
      auto list = _listeners[event];
      for (auto& it : list) {
        if (it == lis) {
          return;
        }
      }
      list.push_back(lis);
      _listeners[event] = list;
    }
    void removeEventListener(const std::string& event, BaseEventListener* lis) {
      auto list = _listeners[event];
      std::erase(list, lis);
      _listeners[event] = list;
    }
    static core::Pointer<EventBus> getEventBus() {
      static core::Pointer<EventBus> bus = INJECT(EventBus);
      return bus;
    }
  };
} // namespace lux::system

#endif