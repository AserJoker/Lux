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
exports.Element_Sprite = void 0;
var Element_Base_1 = require("./Element_Base");
var Element_Sprite = /** @class */ (function (_super) {
    __extends(Element_Sprite, _super);
    function Element_Sprite() {
        var _this = _super.call(this) || this;
        _this._sprite = null;
        _this._release = null;
        _this._release = _system_event_bus.listen("lux::system::Application.ready" /* EVENT.READY */, function () {
            _this._sprite = Sprite_load("texture::demo");
        });
        return _this;
    }
    Element_Sprite.prototype.onUnmounted = function () {
        if (this._sprite) {
            this._sprite.dispose();
        }
        if (this._release) {
            this._release();
        }
    };
    Element_Sprite.prototype.onRener = function () {
        if (this._sprite) {
            this._sprite.draw();
        }
    };
    Element_Sprite.prototype.onMounted = function () {
    };
    return Element_Sprite;
}(Element_Base_1.Element_Base));
exports.Element_Sprite = Element_Sprite;
