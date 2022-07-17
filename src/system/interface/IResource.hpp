#ifndef _H_LUX_SYSTEM_IRESOURCE_
#define _H_LUX_SYSTEM_IRESOURCE_
#include "./IComponent.hpp"
#include "resource/Buffer.hpp"
namespace lux::system {
    class IResource :public IComponent {
    public:
        DEFINE_TOKEN(lux::system::IResource);

        virtual core::Pointer<resource::Buffer> load(const std::string& token) = 0;
    };
} // namespace lux::system

#endif