//
// Created by w30029682 on 2022/7/27.
//

#ifndef _H_LUX_EVENT_KEY_EVENT_
#define _H_LUX_EVENT_KEY_EVENT_

#include "core/EventBus.hpp"

namespace lux::event {
    class KeyEvent : public core::EventBus::BaseEvent<"key"> {
    public:
        enum ACTION {
            KEYUP, KEYDOWN
        };
    private:
        ACTION _action;
        int _nKey;
        Uint32 _uDelay;
    public:
        KeyEvent(ACTION action, int key,Uint32 delay) : _action(action), _nKey(key),_uDelay(delay) {

        }

        [[nodiscard]] int getKey() const {
            return _nKey;
        }

        [[nodiscard]] ACTION getAction() const {
            return _action;
        }
        [[nodiscard]] Uint32 getDelay() const{
            return _uDelay;
        }
    };
}
#endif //_H_LUX_EVENT_KEY_EVENT_
