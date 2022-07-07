"use strict";
exports.__esModule = true;
exports.start = void 0;
var start = function () {
    _system_event_bus.listen("lux::system::Application.ready", function () {
        console.log("app ready");
    });
    _system_event_bus.listen("lux::system::Graphic.loop", function () {
        console.log("graphic loop");
    });
};
exports.start = start;
