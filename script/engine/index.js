"use strict";
exports.__esModule = true;
exports.start = void 0;
var image = 0;
var start = function () {
    _system_event_bus.listen("lux::system::Application.ready", function () {
        image = createImage("texture::demo");
    });
    _system_event_bus.listen("lux::system::Graphic.loop", function () {
        drawImage(image, 100, 100, 0, 0, 32, 32);
    });
};
exports.start = start;
