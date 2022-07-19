#ifndef _LUX_ELEMENT_ROOT_ELEMENT_
#define _LUX_ELEMENT_ROOT_ELEMENT_
#include "Element.hpp"
namespace lux::element {
    class Root : public Element {
    public:
        DEFINE_TOKEN(lux::element::Root);
    };
} // namespace lux::element

#endif