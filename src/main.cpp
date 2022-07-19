#include <SDL.h>
#include <iostream>
#if defined(_WIN32)
#include <Windows.h>
#endif

#include "core/Container.hpp"
#include "core/EventBus.hpp"
#include "core/Object.hpp"
#include "core/Value.hpp"
#include "core/Context.hpp"

#include "system/Application.hpp"
#include "system/Document.hpp"
#include "system/Graphic.hpp"
#include "system/Native.hpp"
#include "system/Resource.hpp"
#include "system/Script.hpp"

#include "resource/Buffer.hpp"
#include "resource/Font.hpp"
#include "resource/Image.hpp"

#include "element/Element.hpp"
#include "element/Image.hpp"
#include "element/Root.hpp"
#include "element/Sprite.hpp"
#include "element/Container.hpp"
#include "element/Font.hpp"
#include "element/Text.hpp"
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
  PROVIDE(core::Context);

  PROVIDE(system::Native);
  PROVIDE(system::Application);
  PROVIDE(system::Graphic);
  PROVIDE(system::Resource);
  PROVIDE(system::Document);
  PROVIDE(system::Script);

  core::Container::provide<resource::Buffer>(resource::Buffer::TOKEN,
    core::Container::PROTOTYPE);
  core::Container::provide<resource::Image>(resource::Image::TOKEN,
    core::Container::PROTOTYPE);
  core::Container::provide<resource::Font>(resource::Font::TOKEN,
    core::Container::PROTOTYPE);

  PROVIDE(element::Root);
  core::Container::provide<element::Element>(element::Element::TOKEN,
    core::Container::PROTOTYPE);
  core::Container::provide<element::Image>(element::Image::TOKEN,
    core::Container::PROTOTYPE);
  core::Container::provide<element::Sprite>(
    element::Sprite::TOKEN, core::Container::PROTOTYPE);
  core::Container::provide<element::Container>(
    element::Container::TOKEN, core::Container::PROTOTYPE);
  core::Container::provide<element::Font>(
    element::Font::TOKEN, core::Container::PROTOTYPE);
  core::Container::provide<element::Text>(
    element::Text::TOKEN, core::Container::PROTOTYPE);

  try {
    INJECT(system::INative);
    INJECT(system::IGraphic);
    INJECT(system::IResource);
    INJECT(system::IScript);
    INJECT(system::IDocument);
    auto app = INJECT(system::Application);
    app->run();
    return 0;
  }
  catch (std::exception& exp) {
    std::cout << exp.what() << std::endl;
    return -1;
  }
}