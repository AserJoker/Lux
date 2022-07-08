"use strict";
exports.__esModule = true;
exports.start = void 0;
var sprite = 0;
var angle = 0;
var start = function () {
    _system_event_bus.listen("lux::system::Application.ready", function () {
        sprite = Sprite_load("texture::demo");
        Sprite_setTargetRect(sprite, 100, 100, 64, 64);
        Sprite_setVisible(sprite, true);
    });
    _system_event_bus.listen("lux::system::Graphic.loop", function () {
        Sprite_setRotation(sprite, 16, 16, angle);
        Sprite_draw(sprite);
        angle += 0.1;
        if (angle > 360) {
            angle = 0;
        }
    });
};
exports.start = start;
