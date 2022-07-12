"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.Scene_Main = void 0;
var Scene_Base_1 = require("./Scene_Base");
var Scene_Main = /** @class */ (function (_super) {
    __extends(Scene_Main, _super);
    function Scene_Main() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.x = 100;
        _this.x_step = 0;
        return _this;
    }
    Scene_Main.prototype.onMounted = function () {
        var _this = this;
        _super.prototype.onMounted.call(this);
        this.demo.setVisible(true);
        _system_event_bus.listen("lux::system::Input.keydown" /* EVENT.KEYDOWN */, function (key) {
            if (key === 79 /* SCANCODE.RIGHT */) {
                _this.x_step = 1;
            }
            else if (key === 80 /* SCANCODE.LEFT */) {
                _this.x_step = -1;
            }
        });
        _system_event_bus.listen("lux::system::Input.keyup" /* EVENT.KEYUP */, function (key) {
            if (key === 79 /* SCANCODE.RIGHT */ && _this.x_step === 1) {
                _this.x_step = 0;
            }
            else if (key === 80 /* SCANCODE.LEFT */ && _this.x_step === -1) {
                _this.x_step = 0;
            }
        });
    };
    Scene_Main.prototype.onRender = function () {
        _super.prototype.onRender.call(this);
        this.font.drawText(this.demo, "hello world", this.x, 100, 255, 0, 0, 255);
        this.demo.draw();
        this.x += this.x_step;
    };
    Scene_Main.prototype.onUnmounted = function () {
        _super.prototype.onUnmounted.call(this);
    };
    __decorate([
        Scene_Base_1.Scene_Base.Sprite(800, 600, 1 /* SpriteAccess.STREAM */)
    ], Scene_Main.prototype, "demo", void 0);
    __decorate([
        Scene_Base_1.Scene_Base.Font("font::demo", 32)
    ], Scene_Main.prototype, "font", void 0);
    Scene_Main = __decorate([
        Scene_Base_1.Scene_Base.Scene("main")
    ], Scene_Main);
    return Scene_Main;
}(Scene_Base_1.Scene_Base));
exports.Scene_Main = Scene_Main;
