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
var __spreadArray = (this && this.__spreadArray) || function (to, from, pack) {
    if (pack || arguments.length === 2) for (var i = 0, l = from.length, ar; i < l; i++) {
        if (ar || !(i in from)) {
            if (!ar) ar = Array.prototype.slice.call(from, 0, i);
            ar[i] = from[i];
        }
    }
    return to.concat(ar || Array.prototype.slice.call(from));
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.Scene_Main = void 0;
var Scene_Base_1 = require("./Scene_Base");
var Scene_Main = /** @class */ (function (_super) {
    __extends(Scene_Main, _super);
    function Scene_Main() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Scene_Main.prototype.onMounted = function () {
        _super.prototype.onMounted.call(this);
        this.demo = this.font.createSprite("hello world", 255, 0, 0, 255);
        this.demo.setVisible(true);
    };
    Scene_Main.prototype.onMouseMove = function (x, y) {
        var _a;
        (_a = this.demo).setTargetRect.apply(_a, __spreadArray([x, y], this.demo.getSize(), false));
    };
    Scene_Main.prototype.onRender = function () {
        _super.prototype.onRender.call(this);
        this.demo.draw();
    };
    Scene_Main.prototype.onUnmounted = function () {
        _super.prototype.onUnmounted.call(this);
        if (this.demo) {
            this.demo.dispose();
        }
    };
    __decorate([
        Scene_Base_1.Scene_Base.Font("font::demo", 32)
    ], Scene_Main.prototype, "font", void 0);
    __decorate([
        Scene_Base_1.Scene_Base.OnEvent("lux::system::Input.mousemotion" /* EVENT.MOUSEMOTION */)
    ], Scene_Main.prototype, "onMouseMove", null);
    Scene_Main = __decorate([
        Scene_Base_1.Scene_Base.Scene("main")
    ], Scene_Main);
    return Scene_Main;
}(Scene_Base_1.Scene_Base));
exports.Scene_Main = Scene_Main;
