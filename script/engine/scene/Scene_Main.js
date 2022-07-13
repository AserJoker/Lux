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
var system_1 = require("../system");
var Scene_Base_1 = require("./Scene_Base");
var Scene_Main = /** @class */ (function (_super) {
    __extends(Scene_Main, _super);
    function Scene_Main() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.x = 0;
        _this.y = 0;
        return _this;
    }
    Scene_Main.prototype.onMounted = function () {
        _super.prototype.onMounted.call(this);
        this.$system = system_1.System_Main.get();
        this.$system.$map.loadTile("tile::grass");
    };
    Scene_Main.prototype.onRender = function () {
        _super.prototype.onRender.call(this);
        var _a = this.$system.$camera.trasformToNative(this.x, this.y), x = _a[0], y = _a[1];
        this.$system.$map.draw(x, y, "grass", 0);
        console.log(this.$system.$camera.getPosition().join(','));
    };
    Scene_Main.prototype.onUnmounted = function () {
        _super.prototype.onUnmounted.call(this);
    };
    Scene_Main.prototype.onKeydown = function (key) {
        if (key === 7 /* SCANCODE.D */) {
            this.x += 1;
            this.$system.$camera.move(1, 0);
        }
        if (key === 4 /* SCANCODE.A */) {
            this.x -= 1;
            this.$system.$camera.move(-1, 0);
        }
    };
    __decorate([
        Scene_Base_1.Scene_Base.OnEvent("lux::system::Input.keydown" /* EVENT.KEYDOWN */)
    ], Scene_Main.prototype, "onKeydown", null);
    Scene_Main = __decorate([
        Scene_Base_1.Scene_Base.Scene("main")
    ], Scene_Main);
    return Scene_Main;
}(Scene_Base_1.Scene_Base));
exports.Scene_Main = Scene_Main;
