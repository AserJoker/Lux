#ifndef _LUX_SYSTEM_DOCUMENT_
#define _LUX_SYSTEM_DOCUMENT_
#include "core/Dependence.hpp"
#include "interface/IDocument.hpp"
#include "interface/IGraphic.hpp"
#include "interface/INative.hpp"
#include "interface/IResource.hpp"
#include "core/EventBus.hpp"
#include "event/RenderEvent.hpp"
#include "element/RootElement.hpp"
namespace lux::system {
    class Document :public IDocument,
        public core::Dependence<IGraphic, INative, IResource>,
        public core::EventBus::EventListener<event::RenderEvent> {
    private:
        core::Pointer<element::Element> _pRoot;
    public:
        Document() {
            _pRoot = INJECT(element::RootElement).cast<element::Element>();
        }
        ~Document() override {
        }
        void on(event::RenderEvent*) override {
            _pRoot->onUpdate();
        }
        virtual core::Pointer<element::Element> getRoot() {
            return _pRoot;
        }
    };
}
#endif