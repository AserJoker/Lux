#include <iostream>
#include<SDL.h>

#include "core/Object.hpp"
#include "core/Container.hpp"
#include "core/EventEmitter.hpp"
#include "system/Application.hpp"
#include "system/Native.hpp"
#include "system/Graphic.hpp"
#include "system/Resource.hpp"
#include "system/Script.hpp"

#include "resource/Image.hpp"
#include "resource/Buffer.hpp"
using namespace lux;
int main(int argc, char* argv[]) {
    try {
        core::Container::provide<resource::Image>(resource::Image::TOKEN, core::Container::PROTOTYPE);
        core::Container::provide<resource::Buffer>(resource::Buffer::TOKEN, core::Container::PROTOTYPE);

        PROVIDE(system::Application);

        PROVIDE(system::Script);
        PROVIDE(system::Native);
        PROVIDE(system::Graphic);
        PROVIDE(system::Resource);

        INJECT(system::Script);
        INJECT(system::Native);
        INJECT(system::Graphic);
        INJECT(system::Resource);
        auto app = INJECT(system::Application);
        app->run();
        return 0;

    }
    catch (std::exception& exp) {
        std::cout << exp.what() << std::endl;
        return -1;
    }
}