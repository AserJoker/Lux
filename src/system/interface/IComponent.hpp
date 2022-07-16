#ifndef _H_LUX_SYSTEM_ICOMPONENT_
#define _H_LUX_SYSTEM_ICOMPONENT_
#include "core/Object.hpp"
#include "core/Container.hpp"
namespace lux::system {
  class IComponent : public core::Object {
  public:
    template< class ...Deps>
    class Dependence {
    private:
      std::map<std::string, core::Pointer<IComponent>> _dependences;
      template<class ...Tokens>
      void dependence(const std::string& token, Tokens... tokens) {
        _dependences[token] = core::Container::inject<IComponent>(token);
        dependence(tokens...);
      }
      void dependence(const std::string& token) {
        _dependences[token] = core::Container::inject<IComponent>(token);
      }

    public:
      Dependence() {
        dependence(Deps::TOKEN...);
      }
      template<class T> core::Pointer<T> getDependence() {
        return _dependences[T::TOKEN].cast<T>();
      }
    };
  };
} // namespace lux::system

#endif