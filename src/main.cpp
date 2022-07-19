#include <SDL.h>
#include <iostream>
#if defined(_WIN32)
#include <Windows.h>
#endif

#include "core/Container.hpp"
#include "core/EventBus.hpp"
#include "core/Object.hpp"
#include "core/Value.hpp"

#include "system/Application.hpp"
#include "system/Document.hpp"
#include "system/Graphic.hpp"
#include "system/Native.hpp"
#include "system/Resource.hpp"

#include "resource/Buffer.hpp"
#include "resource/Font.hpp"
#include "resource/Image.hpp"

#include "element/Element.hpp"
#include "element/ImageElement.hpp"
#include "element/RootElement.hpp"
#include "element/SpriteElement.hpp"
#include "element/ContainerElement.hpp"
#include "element/FontElement.hpp"
#include "element/TextElement.hpp"
using namespace lux;
int main(int argc, char* argv[]) {
#if defined(_WIN32)
  // Set console code page to UTF-8 so console known how to interpret string
  // data
  SetConsoleOutputCP(CP_UTF8);
  // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
  setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
  PROVIDE(core::EventBus);
  PROVIDE(system::Native);
  PROVIDE(system::Application);
  PROVIDE(system::Graphic);
  PROVIDE(system::Resource);
  PROVIDE(system::Document);

  core::Container::provide<resource::Buffer>(resource::Buffer::TOKEN,
    core::Container::PROTOTYPE);
  core::Container::provide<resource::Image>(resource::Image::TOKEN,
    core::Container::PROTOTYPE);
  core::Container::provide<resource::Font>(resource::Font::TOKEN,
    core::Container::PROTOTYPE);

  PROVIDE(element::RootElement);
  core::Container::provide<element::ImageElement>(element::ImageElement::TOKEN,
    core::Container::PROTOTYPE);
  core::Container::provide<element::SpriteElement>(
    element::SpriteElement::TOKEN, core::Container::PROTOTYPE);
  core::Container::provide<element::ContainerElement>(
    element::ContainerElement::TOKEN, core::Container::PROTOTYPE);
  core::Container::provide<element::FontElement>(
    element::FontElement::TOKEN, core::Container::PROTOTYPE);
  core::Container::provide<element::TextElement>(
    element::TextElement::TOKEN, core::Container::PROTOTYPE);

  try {
    INJECT(system::INative);
    INJECT(system::IGraphic);
    INJECT(system::IResource);
    auto doc = INJECT(system::IDocument);
    auto app = INJECT(system::Application);
    auto root = doc->getRoot();
    auto container = element::Element::create<element::ContainerElement>({
      std::pair<std::string,core::Pointer<core::Value>>({"width", core::value(100)}),
      std::pair<std::string,core::Pointer<core::Value>>({"height", core::value(100)}),
      });
    auto img = element::Element::create<element::SpriteElement>({
      {"asset",core::value(std::string("texture::demo"))}
      });
    auto font = element::Element::create<element::FontElement>({
      {"asset",core::value("font::demo")},
      {"size",core::value(32)}
      });
    auto text = element::Element::create<element::TextElement>({
      {"text",core::value("hello world")},
        {"color",core::value(0xff000077)},
      });
    font->append(text);
    container->append(img);
    container->append(font);
    root->append(container);
    app->run();
    return 0;
  }
  catch (std::exception& exp) {
    std::cout << exp.what() << std::endl;
    return -1;
  }
}