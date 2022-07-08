"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.start = void 0;
var sp;
var sps;
var direct = false;
var start = function () {
    _system_event_bus.listen("lux::system::Application.ready", function () {
        sps = Sprite_load("texture::demo");
        sps.setTargetRect(32, 32, 32, 32);
        sps.setVisible(true);
        sp = Sprite_create(100, 100, 2 /* SpriteAccess.TARGET */);
        sp.setVisible(true);
        Sprite_setRenderTarget(sp);
        sps.draw();
        Sprite_setRenderTarget(undefined);
    });
    _system_event_bus.listen("lux::system::Graphic.loop", function () {
        sp.draw();
    });
};
exports.start = start;
