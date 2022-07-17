#ifndef _LUX_SYSTEM_IDOCUMENT_
#define _LUX_SYSTEM_IDOCUMENT_
#include "IComponent.hpp"
#include "element/Element.hpp"
namespace lux::system {
    class IDocument :public IComponent {
    public:
        DEFINE_TOKEN(lux::system::IDocument);
        virtual core::Pointer<element::Element> getRoot() = 0;
    };
} // namespace lux::system

#endif