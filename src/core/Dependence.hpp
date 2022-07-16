#ifndef _H_LUX_CORE_DEPENDENCE_
#define _H_LUX_CORE_DEPENDENCE_
#include "Object.hpp"
namespace lux::core {
    template< class ...Deps>
    class Dependence {
    private:
        std::map<std::string, core::Pointer<Object>> _dependences;
        template<class ...Tokens>
        void dependence(const std::string& token, Tokens... tokens) {
            _dependences[token] = core::Container::inject<Object>(token);
            dependence(tokens...);
        }
        void dependence(const std::string& token) {
            _dependences[token] = core::Container::inject<Object>(token);
        }

    public:
        Dependence() {
            dependence(Deps::TOKEN...);
        }
        template<class T> core::Pointer<T> getDependence() {
            return _dependences[T::TOKEN].cast<T>();
        }
    };
} // namespace lux::core

#endif