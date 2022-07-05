#ifndef _H_LUX_CORE_CONTAINER_
#define _H_LUX_CORE_CONTAINER_
#include<map>
#include"Object.hpp"
namespace lux::core {
    class Container {
    public:
        enum TYPE {
            PROTOTYPE, SINGLETON
        };

    private:
        typedef Pointer<Object>(*GENERATOR)();

        typedef struct Provider {
            TYPE type = SINGLETON;
            GENERATOR funcGenerator = nullptr;
            Pointer<Object> pSingleton;
        }Provider;

        static std::map<std::string, Provider> _providers;

    public:
        template<class T> static void provide(std::string token = T::TOKEN, TYPE type = SINGLETON) {
            _providers[token] = {
                type,
                []()->Pointer<Object> {
                    return Pointer<Object>((Object*)new T());
                },
                Pointer<Object>(nullptr)
            };
        }

        template<class T> static Pointer<T> inject(std::string token = T::TOKEN) {
            auto pair = _providers.find(token);
            if (pair != _providers.end()) {
                auto& provider = pair->second;
                if (provider.type == PROTOTYPE) {
                    auto pObject = provider.funcGenerator();
                    pObject->_szType = token;
                    return pObject.template cast<T>();
                }
                else {
                    if (provider.pSingleton == nullptr) {
                        provider.pSingleton = provider.funcGenerator();
                        _providers[token] = provider;
                    }
                    provider.pSingleton->_szType = token;
                    return provider.pSingleton.template cast<T>();
                }
            }
            return Pointer<T>(nullptr);
        }
    };
    std::map<std::string, Container::Provider> Container::_providers;
} // namespace lux::core
#define PROVIDE(provider) lux::core::Container::provide<provider>()
#define INJECT(provider) lux::core::Container::inject<provider>()
#define PROVIDE_AND_INJECT(provider) PROVIDE(provider);INJECT(provider);
#endif