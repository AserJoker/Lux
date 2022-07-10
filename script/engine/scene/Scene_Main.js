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
Object.defineProperty(exports, "__esModule", { value: true });
exports.Scene_Main = void 0;
var Scene_Base_1 = require("./Scene_Base");
var Scene_Main = /** @class */ (function (_super) {
    __extends(Scene_Main, _super);
    function Scene_Main() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.demo = null;
        _this.font = null;
        _this.lastTime = Date.now();
        return _this;
    }
    Scene_Main.prototype.onMounted = function () {
        this.font = Font_load("font::demo", 32);
        this.demo = this.font.drawText("hello world", 255, 0, 0, 255);
        this.demo.setTargetRect(100, 100, 137, 32);
        this.demo.setVisible(true);
    };
    Scene_Main.prototype.onRender = function () {
        var now = Date.now();
        if (this.demo) {
            this.demo.draw();
        }
        this.lastTime = now;
    };
    Scene_Main.prototype.onUnmounted = function () {
        if (this.demo) {
            this.demo.dispose();
            this.demo = null;
        }
        if (this.font) {
            this.font.dispose();
            this.font = null;
        }
    };
    return Scene_Main;
}(Scene_Base_1.Scene_Base));
exports.Scene_Main = Scene_Main;
