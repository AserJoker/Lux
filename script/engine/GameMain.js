"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.GameMain = void 0;
var scene_1 = require("./scene");
var GameMain = /** @class */ (function () {
    function GameMain() {
        var _this = this;
        _system_event_bus.listen("lux::system::Application.ready" /* EVENT.READY */, function () { return _this.onReady(); });
        _system_event_bus.listen("lux::system::Graphic.loop" /* EVENT.UPDATE */, function () { return _this.onUpdate(); });
        this._scene = new scene_1.Scene_Main();
    }
    GameMain.get = function () {
        if (!GameMain._theGameMain) {
            GameMain._theGameMain = new GameMain();
        }
        return GameMain._theGameMain;
    };
    GameMain.prototype.loadScene = function (scene) {
        this._scene.onUnmounted();
        this._scene = scene;
        this._scene.onMounted();
    };
    GameMain.prototype.onReady = function () {
        this._scene.onMounted();
    };
    GameMain.prototype.onUpdate = function () {
        Sprite_begin(undefined);
        this._scene.onRender();
        Sprite_end();
    };
    return GameMain;
}());
exports.GameMain = GameMain;
