#include <SDL.h>
#include <iostream>

#if defined(_WIN32)

#include <Windows.h>

#endif

#include "core/Container.hpp"
#include "core/Context.hpp"
#include "core/EventBus.hpp"

#include "system/Application.hpp"
#include "system/Camera.hpp"
#include "system/Graphic.hpp"
#include "system/Input.hpp"
#include "system/Native.hpp"
#include "system/Resource.hpp"
#include "system/Script.hpp"

#include "resource/Buffer.hpp"
#include "resource/Font.hpp"
#include "resource/Image.hpp"

#include "graphic/Sprite.hpp"
#include "graphic/Tile.hpp"
#include "graphic/TileGroup.hpp"

#include "game/Background.hpp"
#include "game/EntityPool.hpp"
#include "game/Main.hpp"

using namespace lux;

int main(int argc, char *argv[]) {
#if defined(_WIN32)
  SetConsoleOutputCP(CP_UTF8);
  setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
  PROVIDE(core::EventBus);
  PROVIDE(core::Context);

  PROVIDE(system::Native);
  PROVIDE(system::Application);
  PROVIDE(system::Graphic);
  PROVIDE(system::Resource);
  PROVIDE(system::Script);
  PROVIDE(system::Camera);
  PROVIDE(system::Input);

  PROVIDE(game::Main);
  PROVIDE(game::Background);
  PROVIDE(game::EntityPool);

  PROVIDE_PROTOTYPE(resource::Buffer);
  PROVIDE_PROTOTYPE(resource::Image);
  PROVIDE_PROTOTYPE(resource::Font);

  PROVIDE_PROTOTYPE(graphic::Sprite);
  PROVIDE_PROTOTYPE(graphic::Tile);
  PROVIDE_PROTOTYPE(graphic::TileGroup);

  try {
    INJECT(system::INative);
    INJECT(system::IGraphic);
    INJECT(system::IResource);
    INJECT(system::IScript);
    INJECT(system::ICamera);
    INJECT(system::IInput);
    INJECT(game::Main);

    auto app = INJECT(system::Application);
    app->run();
    return 0;
  } catch (std::exception &exp) {
    std::cout << exp.what() << std::endl;
    return -1;
  }
}