#include <SDL.h>
#include <iostream>

#if defined(_WIN32)

#include <Windows.h>

#endif

#include "core/Container.hpp"
#include "core/EventBus.hpp"
#include "core/Context.hpp"

#include "system/Application.hpp"
#include "system/Graphic.hpp"
#include "system/Native.hpp"
#include "system/Resource.hpp"
#include "system/Script.hpp"

#include "game/Main.hpp"
#include "game/Map.hpp"
#include "game/map/Chunk.hpp"

#include "resource/Buffer.hpp"
#include "resource/Font.hpp"
#include "resource/Image.hpp"

#include "graphic/Sprite.hpp"
#include "graphic/Container.hpp"
#include "graphic/Tile.hpp"


using namespace lux;

int main(int argc, char *argv[]) {
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
    PROVIDE(system::Script);

    PROVIDE(game::Main);
    PROVIDE(game::Map);

    PROVIDE_PROTOTYPE(game::map::Chunk);

    PROVIDE_PROTOTYPE(resource::Buffer);
    PROVIDE_PROTOTYPE(resource::Image);
    PROVIDE_PROTOTYPE(resource::Font);

    PROVIDE_PROTOTYPE(graphic::Sprite);
    PROVIDE_PROTOTYPE(graphic::Container);
    PROVIDE_PROTOTYPE(graphic::Tile);

    try {
        INJECT(system::INative);
        INJECT(system::IGraphic);
        INJECT(system::IResource);
        INJECT(system::IScript);

        INJECT(game::Main);

        auto app = INJECT(system::Application);
        app->run();
        return 0;
    }
    catch (std::exception &exp) {
        std::cout << exp.what() << std::endl;
        return -1;
    }
}