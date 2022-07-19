#ifndef _LUX_SYSTEM_DOCUMENT_
#define _LUX_SYSTEM_DOCUMENT_
#include <tinyxml2.h>
#include "core/Dependence.hpp"
#include "interface/IDocument.hpp"
#include "interface/IGraphic.hpp"
#include "interface/INative.hpp"
#include "interface/IResource.hpp"
#include "core/EventBus.hpp"
#include "event/RenderEvent.hpp"
#include "element/Root.hpp"
namespace lux::system {
    class Document :public IDocument,
        public core::Dependence<IGraphic, INative, IResource>,
        public core::EventBus::EventListener<event::RenderEvent> {
    private:
        core::Pointer<element::Element> _pRoot;
        element::Props resolveProps(tinyxml2::XMLElement *element){
            element::Props props = {};
            auto attr = element->FirstAttribute();
            while(attr){
                auto name = attr->Name();
                auto value = attr->Value();
                props.insert({name,value});
                attr = attr->Next();
            }
            return props;
        }
        void resolveElement(tinyxml2::XMLElement *element,core::Pointer<element::Element> pParent,std::vector<std::string> path){
            std::string name = element->Name();
            if(name[0]>='a'&&name[0]<='z'){
                name[0] = name[0] + 'A'-'a';
                auto token = std::string("lux::element::")+name;
                auto node = element::Element::create(token,resolveProps(element));
                if(node==nullptr){
                    throw RUNTIME_ERROR(fmt::format("cannot find resolve node: {}",element->Name()));
                }
                auto child = element->FirstChildElement();
                path.push_back(element->Name());
                while(child){
                    resolveElement(child,node,path);
                    child = child->NextSiblingElement();
                }
                pParent->append(node);
            }
        }
    public:
        Document() {
            _pRoot = INJECT(element::Root).cast<element::Element>();
            auto R = getDependence<IResource>();
            auto buf = R->load("document");
            tinyxml2::XMLDocument doc;
            auto err = doc.Parse(buf->toString().c_str());
            if(err){
                throw RUNTIME_ERROR(fmt::format("document parser error:{}",err));
            }
            auto root = doc.FirstChildElement("root");
            auto text = root->Name();
            if(!root){
                throw RUNTIME_ERROR(fmt::format("cannot found root element in document"));
            }
            auto child = root->FirstChildElement();
            while(child){
                resolveElement(child,_pRoot,{"root"});
                child= child->NextSiblingElement();
            }
            auto ele = element::Element::select("group1");
            ele->setState("x",200);
            ele->setState("y",200);
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